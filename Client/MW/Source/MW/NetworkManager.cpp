// NetworkManager.cpp - 개선된 버전
// 서버와의 통신을 관리하는 클래스 구현

#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "GameFramework/GameModeBase.h"

void UNetworkManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // 수신 버퍼 초기화
    ReceiveBuffer.SetNumUninitialized(MaxReceiveBufferSize);
    PacketProcessBuffer.Reserve(MaxReceiveBufferSize);

    // 통계 초기화
    ResetNetworkStats();

    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("NetworkManager initialized with buffer size: %d"), MaxReceiveBufferSize);
    }
}

void UNetworkManager::Deinitialize()
{
    DisconnectFromServer();
    Super::Deinitialize();

    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("NetworkManager cleaned up"));
    }
}

bool UNetworkManager::ConnectToServer(const FString& IpAddress, int32 Port)
{
    // 재연결 상태 추적
    LastConnectedServerIP = IpAddress;
    LastConnectedServerPort = Port;
    LastConnectionAttemptTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

    // 이미 연결된 경우 기존 연결 해제
    if (IsConnected())
    {
        if (bEnableConnectionLogging)
        {
            UE_LOG(LogTemp, Log, TEXT("Disconnecting existing connection before reconnecting"));
        }
        DisconnectFromServer();
    }

    // 소켓 서브시스템 가져오기
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Socket subsystem not found"));
        return false;
    }

    // 서버 주소 생성 및 설정
    ServerAddress = SocketSubsystem->CreateInternetAddr();
    bool bIsValid = false;
    ServerAddress->SetIp(*IpAddress, bIsValid);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid IP address: %s"), *IpAddress);
        return false;
    }

    ServerAddress->SetPort(Port);

    // TCP 소켓 생성
    Socket = MakeShareable(SocketSubsystem->CreateSocket(NAME_Stream, TEXT("GameClient"), false));
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
        return false;
    }

    // 소켓 옵션 설정
    ConfigureSocket();

    // 서버 연결 시도
    bIsConnected = Socket->Connect(*ServerAddress);

    if (!bIsConnected)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to server: %s:%d"), *IpAddress, Port);
        Socket->Close();
        Socket = nullptr;
        OnConnectionStatusChanged.Broadcast(false);
        OnConnectionError.Broadcast();
        return false;
    }

    if (bEnableConnectionLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Successfully connected to server: %s:%d"), *IpAddress, Port);
    }

    // 연결 성공 처리
    bIsReconnecting = false;
    ReconnectAttempts = 0;
    OnConnectionStatusChanged.Broadcast(true);

    // 네트워크 타이밍 시작
    StartNetworkTimers();

    return true;
}

void UNetworkManager::ConfigureSocket()
{
    if (!Socket) return;

    int32 ActualBufferSize = 0;

    // 비동기 모드 설정
    Socket->SetNonBlocking(true);

    // 주소 재사용 설정
    Socket->SetReuseAddr(true);

    // 버퍼 크기 설정
    Socket->SetReceiveBufferSize(MaxReceiveBufferSize, ActualBufferSize);
    Socket->SetSendBufferSize(MaxReceiveBufferSize, ActualBufferSize);

    // TCP_NODELAY 설정 (Nagle 알고리즘 비활성화)
    Socket->SetNoDelay(true);

    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Socket configured: ReceiveBuffer=%d, SendBuffer=%d"),
            ActualBufferSize, ActualBufferSize);
    }
}

void UNetworkManager::StartNetworkTimers()
{
    if (UWorld* World = GetWorld())
    {
        // 네트워크 업데이트 타이머
        World->GetTimerManager().SetTimer(
            NetworkTimerHandle,
            this,
            &UNetworkManager::OnNetworkTimerTick,
            1.0f / NetworkUpdateRate,
            true
        );

        // Ping 타이머
        World->GetTimerManager().SetTimer(
            PingTimerHandle,
            this,
            &UNetworkManager::OnPingTimerTick,
            PingInterval,
            true
        );

        if (bEnableNetworkLogging)
        {
            UE_LOG(LogTemp, Log, TEXT("Network timers started: Update=%.1fHz, Ping=%.1fs"),
                NetworkUpdateRate, PingInterval);
        }
    }
}

void UNetworkManager::DisconnectFromServer()
{
    // 타이머 정리
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(NetworkTimerHandle);
        World->GetTimerManager().ClearTimer(PingTimerHandle);
    }

    // 소켓 정리
    if (Socket)
    {
        Socket->Close();
        Socket = nullptr;
    }

    // 상태 초기화
    if (bIsConnected)
    {
        bIsConnected = false;
        OnConnectionStatusChanged.Broadcast(false);

        if (bEnableConnectionLogging)
        {
            UE_LOG(LogTemp, Log, TEXT("Server connection closed"));
        }
    }

    CurrentPlayerId = -1;
    CurrentPingTime = 0.0f;
    LastPingSentTime = 0;
    LastPongReceivedTime = 0;

    // 버퍼 정리
    PacketProcessBuffer.Empty();
}

void UNetworkManager::OnNetworkTimerTick()
{
    if (!ValidateConnection())
    {
        if (bEnableConnectionLogging)
        {
            UE_LOG(LogTemp, Warning, TEXT("Connection lost detected during network timer execution"));
        }
        DisconnectFromServer();
        OnConnectionError.Broadcast();
        return;
    }

    Update();

    // 네트워크 통계 로깅
    if (bLogNetworkStats && GetWorld())
    {
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastStatsResetTime > 10.0f) // 10초마다
        {
            UE_LOG(LogTemp, Log, TEXT("Network Stats - Received: %d, Sent: %d, Ping: %.1fms"),
                PacketsReceived, PacketsSent, CurrentPingTime);
            // 통계 리셋하지 않고 누적으로 유지
        }
    }
}

void UNetworkManager::OnPingTimerTick()
{
    if (IsConnected())
    {
        SendPing();
    }
}

bool UNetworkManager::ValidateConnection()
{
    if (!IsConnected())
    {
        return false;
    }

    // 연결 타임아웃 검사
    uint64 CurrentTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());
    if (LastPongReceivedTime > 0 && (CurrentTime - LastPongReceivedTime) > (ConnectionTimeout * 1000))
    {
        UE_LOG(LogTemp, Warning, TEXT("Connection timeout detected (%.1fs since last pong)"),
            (CurrentTime - LastPongReceivedTime) / 1000.0f);
        return false;
    }

    return true;
}

void UNetworkManager::Update()
{
    if (!IsConnected()) return;

    uint32 PendingDataSize = 0;

    // 대기 중인 데이터 확인
    if (!Socket->HasPendingData(PendingDataSize) || PendingDataSize == 0)
    {
        return;
    }

    // 필요한 경우 버퍼 크기 조정
    if (PendingDataSize > static_cast<uint32>(ReceiveBuffer.Num()))
    {
        if (PendingDataSize <= MaxReceiveBufferSize)
        {
            ReceiveBuffer.SetNumUninitialized(PendingDataSize);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Received data size too large: %d bytes (max: %d)"),
                PendingDataSize, MaxReceiveBufferSize);
            ReceiveBuffer.SetNumUninitialized(MaxReceiveBufferSize);
            PendingDataSize = MaxReceiveBufferSize;
        }
    }

    int32 BytesRead = 0;

    // 데이터 읽기
    if (Socket->Recv(ReceiveBuffer.GetData(), FMath::Min(static_cast<int32>(PendingDataSize), ReceiveBuffer.Num()), BytesRead))
    {
        if (BytesRead > 0)
        {
            ProcessReceivedData(ReceiveBuffer, BytesRead);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to receive data from server"));
        DisconnectFromServer();
        OnConnectionError.Broadcast();
    }
}

void UNetworkManager::ProcessReceivedData(const TArray<uint8>& Data, int32 BytesRead)
{
    // 기존 처리 버퍼에 새 데이터 추가
    PacketProcessBuffer.Append(Data.GetData(), BytesRead);

    // 패킷 처리
    int32 ProcessedBytes = 0;
    int32 PacketCount = 0;

    while (ProcessedBytes + sizeof(PacketHeader) <= PacketProcessBuffer.Num())
    {
        PacketCount++;

        // 패킷 헤더 가져오기
        PacketHeader* Header = reinterpret_cast<PacketHeader*>(PacketProcessBuffer.GetData() + ProcessedBytes);

        // 패킷 헤더 검증
        if (!ValidatePacketHeader(Header, PacketProcessBuffer.Num() - ProcessedBytes))
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid packet header detected, clearing buffer"));
            PacketProcessBuffer.Empty();
            break;
        }

        // 패킷 전체가 도착했는지 확인
        if (ProcessedBytes + Header->PacketSize > PacketProcessBuffer.Num())
        {
            if (bLogPacketDetails)
            {
                UE_LOG(LogTemp, VeryVerbose, TEXT("Incomplete packet, waiting for more data (Need=%d, Have=%d)"),
                    Header->PacketSize, PacketProcessBuffer.Num() - ProcessedBytes);
            }
            break;
        }

        // 패킷 타입에 따른 처리
        ProcessPacketByType(Header, ProcessedBytes);

        // 처리된 바이트 수 갱신
        ProcessedBytes += Header->PacketSize;
        PacketsReceived++;
    }

    // 처리된 데이터 제거
    if (ProcessedBytes > 0)
    {
        PacketProcessBuffer.RemoveAt(0, ProcessedBytes);
    }

    if (bLogPacketDetails && PacketCount > 0)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Processed %d packets, %d bytes remaining in buffer"),
            PacketCount, PacketProcessBuffer.Num());
    }
}

void UNetworkManager::ProcessPacketByType(PacketHeader* Header, int32 ProcessedBytes)
{
    switch (Header->PacketType)
    {
    case EPacketType::CLIENT_ID:
        if (bLogPacketDetails)
        {
            UE_LOG(LogTemp, Log, TEXT("Processing CLIENT_ID packet"));
        }
        if (Header->PacketSize >= sizeof(ClientIdPacket))
        {
            HandleClientIdPacket(reinterpret_cast<ClientIdPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
        }
        break;

    case EPacketType::PLAYER_UPDATE_INFO:
        if (bLogPacketDetails)
        {
            UE_LOG(LogTemp, VeryVerbose, TEXT("Processing PLAYER_UPDATE_INFO packet"));
        }
        if (Header->PacketSize >= sizeof(OutputPacket))
        {
            HandleOutputPacket(reinterpret_cast<OutputPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("PLAYER_UPDATE_INFO packet size mismatch: Expected>=%d, Got=%d"),
                sizeof(OutputPacket), Header->PacketSize);
        }
        break;

    case EPacketType::DISCONNECT:
        if (bLogPacketDetails)
        {
            UE_LOG(LogTemp, Log, TEXT("Processing DISCONNECT packet"));
        }
        if (Header->PacketSize >= sizeof(DisconnectPacket))
        {
            HandleDisconnectPacket(reinterpret_cast<DisconnectPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
        }
        break;

    case EPacketType::PONG:
        if (bLogPacketDetails)
        {
            UE_LOG(LogTemp, VeryVerbose, TEXT("Processing PONG packet"));
        }
        if (Header->PacketSize >= sizeof(PongPacket))
        {
            HandlePongPacket(reinterpret_cast<PongPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
        }
        break;

    default:
        UE_LOG(LogTemp, Error, TEXT("Unknown packet type: %d"), static_cast<int32>(Header->PacketType));
        break;
    }
}

bool UNetworkManager::ValidatePacketHeader(const PacketHeader* Header, int32 AvailableBytes)
{
    if (!Header)
    {
        return false;
    }

    // 패킷 크기 검증
    if (Header->PacketSize < sizeof(PacketHeader) || Header->PacketSize > MaxReceiveBufferSize)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid packet size: %d (min: %d, max: %d)"),
            Header->PacketSize, sizeof(PacketHeader), MaxReceiveBufferSize);
        return false;
    }

    // 패킷 타입 검증
    if (!UPacketHelper::IsValidPacketType(static_cast<uint8>(Header->PacketType)))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid packet type: %d"), static_cast<int32>(Header->PacketType));
        return false;
    }

    // 사용 가능한 바이트 수 검증
    if (Header->PacketSize > AvailableBytes)
    {
        return false; // 아직 완전히 수신되지 않음
    }

    return true;
}

void UNetworkManager::HandleClientIdPacket(const ClientIdPacket* Packet)
{
    UE_LOG(LogTemp, Error, TEXT("=== CLIENT_ID PACKET RECEIVED ==="));
    UE_LOG(LogTemp, Error, TEXT("Received client ID from server: %d"), Packet->ClientId);
    UE_LOG(LogTemp, Error, TEXT("Current PlayerId: %d"), CurrentPlayerId);

    // 첫 번째 CLIENT_ID 패킷만 자신의 ID로 설정
    if (CurrentPlayerId == -1)
    {
        CurrentPlayerId = Packet->ClientId;
        UE_LOG(LogTemp, Error, TEXT("Setting MY player ID to: %d"), CurrentPlayerId);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Ignoring additional CLIENT_ID (already have ID: %d), but broadcasting join for: %d"),
            CurrentPlayerId, Packet->ClientId);
    }

    // OnPlayerJoined 델리게이트는 모든 ID에 대해 호출 (자신 포함, 다른 플레이어 포함)
    OnPlayerJoined.Broadcast(Packet->ClientId);

    UE_LOG(LogTemp, Error, TEXT("OnPlayerJoined broadcasted for ID: %d"), Packet->ClientId);
}

void UNetworkManager::HandleOutputPacket(const OutputPacket* Packet)
{
    // 새 플레이어인지 확인
    if (!KnownPlayerIds.Contains(Packet->ClientId))
    {
        UE_LOG(LogTemp, Error, TEXT("New player detected from OUTPUT packet: %d"), Packet->ClientId);
        KnownPlayerIds.Add(Packet->ClientId);

        // 새 플레이어 JOIN 이벤트 발생
        OnPlayerJoined.Broadcast(Packet->ClientId);

        // 약간의 지연 후 위치 업데이트 (플레이어 생성 대기)
        FTimerHandle DelayHandle;
        GetWorld()->GetTimerManager().SetTimer(DelayHandle, [this, PacketData = *Packet]()
            {
                FVector Position = UPacketHelper::Vec3ToFVector(PacketData.Position);
                FRotator Rotation = UPacketHelper::Rot3ToFRotator(PacketData.Rotation);
                FVector Velocity = UPacketHelper::Vec3ToFVector(PacketData.Velocity);
                FTransform NewTransform(Rotation, Position);

                OnPlayerUpdated.Broadcast(PacketData.ClientId, NewTransform, Velocity, PacketData.State, PacketData.Action);
            }, 0.1f, false);

        return; // 첫 번째 패킷은 JOIN 처리만
    }

    // 기존 플레이어의 위치 업데이트
    FVector Position = UPacketHelper::Vec3ToFVector(Packet->Position);
    FRotator Rotation = UPacketHelper::Rot3ToFRotator(Packet->Rotation);
    FVector Velocity = UPacketHelper::Vec3ToFVector(Packet->Velocity);
    FTransform NewTransform(Rotation, Position);

    OnPlayerUpdated.Broadcast(Packet->ClientId, NewTransform, Velocity, Packet->State, Packet->Action);

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Position Update: ClientID=%d, Pos=(%.1f,%.1f,%.1f)"),
            Packet->ClientId, Position.X, Position.Y, Position.Z);
    }
}

void UNetworkManager::HandleDisconnectPacket(const DisconnectPacket* Packet)
{
    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Player disconnected: %d"), Packet->ClientId);
    }

    // 플레이어 퇴장 델리게이트 호출
    OnPlayerLeft.Broadcast(Packet->ClientId);
}

void UNetworkManager::HandlePongPacket(const PongPacket* Packet)
{
    uint64 CurrentTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());
    LastPongReceivedTime = CurrentTime;

    // 핑 시간 계산 (ms 단위)
    if (LastPingSentTime > 0)
    {
        CurrentPingTime = static_cast<float>(CurrentTime - LastPingSentTime);
    }

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Pong received: ClientId=%d, Ping=%.2f ms"),
            Packet->ClientId, CurrentPingTime);
    }
}

void UNetworkManager::SendPing()
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    PingPacket Packet;
    Packet.Header.PacketType = EPacketType::PING;
    Packet.Header.PacketSize = sizeof(PingPacket);
    Packet.ClientId = CurrentPlayerId;
    Packet.PingTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());

    LastPingSentTime = Packet.PingTime;

    SendPacket(&Packet, sizeof(Packet));
}

void UNetworkManager::SendPlayerInitInfo(Vec3 Position, Rot3 Rotation)
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    InitPacket Packet;
    Packet.Header.PacketType = EPacketType::PLAYER_INIT_INFO;
    Packet.Header.PacketSize = sizeof(InitPacket);
    Packet.ClientId = CurrentPlayerId;
    Packet.Position = Position;
    Packet.Rotation = Rotation;

    SendPacket(&Packet, sizeof(Packet));

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, Log, TEXT("Sent player init info: ClientId=%d, Pos=(%.1f,%.1f,%.1f)"),
            CurrentPlayerId, Position.X, Position.Y, Position.Z);
    }
}

void UNetworkManager::SendPlayerInput(float ForwardValue, float RightValue,
    float RotationPitch, float RotationYaw, float RotationRoll,
    bool bRunPressed, bool bJumpPressed, bool bAttackPressed, bool bDefendPressed)
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    InputPacket Packet;
    Packet.Header.PacketType = EPacketType::PLAYER_INPUT_INFO;
    Packet.Header.PacketSize = sizeof(InputPacket);
    Packet.ClientId = CurrentPlayerId;

    // 입력 데이터
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.RotationPitch = RotationPitch;
    Packet.RotationYaw = RotationYaw;
    Packet.RotationRoll = RotationRoll;

    // 이벤트 데이터
    Packet.bRunPressed = bRunPressed;
    Packet.bJumpPressed = bJumpPressed;
    Packet.bAttackPressed = bAttackPressed;
    Packet.bDefendPressed = bDefendPressed;

    SendPacket(&Packet, sizeof(Packet));

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Sent input: F=%.2f R=%.2f Y=%.1f Run=%d Jump=%d Attack=%d Defense=%d"),
            ForwardValue, RightValue, RotationYaw, bRunPressed, bJumpPressed, bAttackPressed, bDefendPressed);
    }
}

void UNetworkManager::SendCharacterSelection(int32 CharacterModelId, const FString& CharacterName)
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    // 향후 확장용 - 캐릭터 선택 패킷 전송
    // CharacterSelectionPacket이 정의되면 여기서 구현

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, Log, TEXT("Character selection sent: Model=%d, Name=%s"),
            CharacterModelId, *CharacterName);
    }
}

bool UNetworkManager::SendPacket(const void* Data, int32 Size)
{
    if (!IsConnected() || !Data || Size <= 0)
    {
        if (bEnableNetworkLogging)
        {
            UE_LOG(LogTemp, Error, TEXT("Send failed - Invalid parameters or not connected"));
        }
        return false;
    }

    int32 BytesSent = 0;

    if (!Socket->Send(static_cast<const uint8*>(Data), Size, BytesSent))
    {
        UE_LOG(LogTemp, Error, TEXT("Packet transmission failed"));
        return false;
    }

    if (BytesSent != Size)
    {
        UE_LOG(LogTemp, Warning, TEXT("Only partial data sent: %d/%d bytes"), BytesSent, Size);
        return false;
    }

    // 통계 업데이트
    PacketsSent++;

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Packet sent successfully: %d bytes"), Size);
    }

    return true;
}

void UNetworkManager::ResetNetworkStats()
{
    PacketsReceived = 0;
    PacketsSent = 0;
    LastStatsResetTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

    if (bLogNetworkStats)
    {
        UE_LOG(LogTemp, Log, TEXT("Network statistics reset"));
    }
}

// ===== 향후 확장을 위한 헬퍼 함수들 =====
//void UNetworkManager::ProcessPacketByType(PacketHeader* Header, int32 ProcessedBytes)
//{
//    switch (Header->PacketType)
//    {
//    case EPacketType::CLIENT_ID:
//        if (bLogPacketDetails)
//        {
//            UE_LOG(LogTemp, Log, TEXT("Processing CLIENT_ID packet"));
//        }
//        if (Header->PacketSize >= sizeof(ClientIdPacket))
//        {
//            HandleClientIdPacket(reinterpret_cast<ClientIdPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
//        }
//        break;
//
//    case EPacketType::PLAYER_UPDATE_INFO:
//        if (bLogPacketDetails)
//        {
//            UE_LOG(LogTemp, VeryVerbose, TEXT("Processing PLAYER_UPDATE_INFO packet"));
//        }
//        if (Header->PacketSize >= sizeof(OutputPacket))
//        {
//            HandleOutputPacket(reinterpret_cast<OutputPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
//        }
//        else
//        {
//            UE_LOG(LogTemp, Error, TEXT("PLAYER_UPDATE_INFO packet size mismatch: Expected>=%d, Got=%d"),
//                sizeof(OutputPacket), Header->PacketSize);
//        }
//        break;
//
//    case EPacketType::DISCONNECT:
//        if (bLogPacketDetails)
//        {
//            UE_LOG(LogTemp, Log, TEXT("Processing DISCONNECT packet"));
//        }
//        if (Header->PacketSize >= sizeof(DisconnectPacket))
//        {
//            HandleDisconnectPacket(reinterpret_cast<DisconnectPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
//        }
//        break;
//
//    case EPacketType::PONG:
//        if (bLogPacketDetails)
//        {
//            UE_LOG(LogTemp, VeryVerbose, TEXT("Processing PONG packet"));
//        }
//        if (Header->PacketSize >= sizeof(PongPacket))
//        {
//            HandlePongPacket(reinterpret_cast<PongPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
//        }
//        break;
//
//    default:
//        UE_LOG(LogTemp, Error, TEXT("Unknown packet type: %d"), static_cast<int32>(Header->PacketType));
//        break;
//    }
//}