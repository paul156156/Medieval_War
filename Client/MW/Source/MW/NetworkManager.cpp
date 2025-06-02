// NetworkManager.cpp
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
    // 이미 연결된 경우 기존 연결 해제
    if (IsConnected())
    {
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

    // 소켓 옵션 설정 (서버와 동일하게)
    int32 ActualBufferSize = 0;

    // 비동기 모드 설정
    Socket->SetNonBlocking(true);

    // 주소 재사용 설정
    Socket->SetReuseAddr(true);

    // 버퍼 크기 설정
    Socket->SetReceiveBufferSize(MaxReceiveBufferSize, ActualBufferSize);
    Socket->SetSendBufferSize(MaxReceiveBufferSize, ActualBufferSize);

    // TCP_NODELAY 설정 (Nagle 알고리즘 비활성화) - 서버와 동일
    Socket->SetNoDelay(true);

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

    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Connected to server: %s:%d"), *IpAddress, Port);
    }

    OnConnectionStatusChanged.Broadcast(true);

    // 네트워크 타이밍 시작
    if (UWorld* World = GetWorld())
    {
        // 네트워크 업데이트 타이머 (100Hz)
        World->GetTimerManager().SetTimer(
            NetworkTimerHandle,
            this,
            &UNetworkManager::OnNetworkTimerTick,
            1.0f / NetworkUpdateRate,
            true
        );

        // Ping 타이머 (1초마다)
        World->GetTimerManager().SetTimer(
            PingTimerHandle,
            this,
            &UNetworkManager::OnPingTimerTick,
            PingInterval,
            true
        );
    }

    return true;
}

void UNetworkManager::DisconnectFromServer()
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(NetworkTimerHandle);
        World->GetTimerManager().ClearTimer(PingTimerHandle);
    }

    if (Socket)
    {
        Socket->Close();
        Socket = nullptr;
    }

    if (bIsConnected)
    {
        bIsConnected = false;
        OnConnectionStatusChanged.Broadcast(false);

        if (bEnableNetworkLogging)
        {
            UE_LOG(LogTemp, Log, TEXT("Server connection closed"));
        }
    }

    CurrentPlayerId = -1;
    CurrentPingTime = 0.0f;
}

void UNetworkManager::OnNetworkTimerTick()
{
    if (!ValidateConnection())
    {
        UE_LOG(LogTemp, Warning, TEXT("Connection lost detected during network timer execution"));
        DisconnectFromServer();
        OnConnectionError.Broadcast();
        return;
    }

    Update();
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
        UE_LOG(LogTemp, Warning, TEXT("Connection timeout detected"));
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
            UE_LOG(LogTemp, Warning, TEXT("Received data size too large: %d bytes"), PendingDataSize);
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
            // 수신 데이터 처리
            ProcessReceivedData(ReceiveBuffer, BytesRead);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to receive data"));
        DisconnectFromServer();
        OnConnectionError.Broadcast();
    }
}

void UNetworkManager::ProcessReceivedData(const TArray<uint8>& Data, int32 BytesRead)
{
    //// === 데이터 수신 디버깅 ===
    //UE_LOG(LogTemp, Warning, TEXT("=== ProcessReceivedData === BytesRead=%d, BufferSize=%d"),
    //    BytesRead, PacketProcessBuffer.Num());

    // 기존 처리 버퍼에 새 데이터 추가
    PacketProcessBuffer.Append(Data.GetData(), BytesRead);

    //UE_LOG(LogTemp, Log, TEXT("After append: BufferSize=%d"), PacketProcessBuffer.Num());

    // 패킷 처리
    int32 ProcessedBytes = 0;
    int32 PacketCount = 0;

    while (ProcessedBytes + sizeof(PacketHeader) <= PacketProcessBuffer.Num())
    {
        PacketCount++;
        //UE_LOG(LogTemp, Warning, TEXT("=== Processing Packet #%d ==="), PacketCount);

        // 패킷 헤더 가져오기
        PacketHeader* Header = reinterpret_cast<PacketHeader*>(PacketProcessBuffer.GetData() + ProcessedBytes);

        //UE_LOG(LogTemp, Warning, TEXT("Packet Header: Type=%d, Size=%d"),
        //    (int32)Header->PacketType, Header->PacketSize);

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
            UE_LOG(LogTemp, Log, TEXT("Incomplete packet, waiting for more data (Need=%d, Have=%d)"),
                Header->PacketSize, PacketProcessBuffer.Num() - ProcessedBytes);
            break;
        }

        //UE_LOG(LogTemp, Warning, TEXT("Complete packet received, processing type %d"), (int32)Header->PacketType);

        // 패킷 타입에 따른 처리
        switch (Header->PacketType)
        {
        case EPacketType::CLIENT_ID:
            UE_LOG(LogTemp, Warning, TEXT("Processing CLIENT_ID packet"));
            if (Header->PacketSize >= sizeof(ClientIdPacket))
            {
                HandleClientIdPacket(reinterpret_cast<ClientIdPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        case EPacketType::PLAYER_UPDATE_INFO:
            UE_LOG(LogTemp, Warning, TEXT(">>> Processing PLAYER_POSITION_INFO packet <<<"));
            if (Header->PacketSize >= sizeof(OutputPacket))
            {
                HandleOutputPacket(reinterpret_cast<OutputPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("PLAYER_POSITION_INFO packet size mismatch: Expected>=%d, Got=%d"),
                    sizeof(OutputPacket), Header->PacketSize);
            }
            break;

        case EPacketType::DISCONNECT:
            UE_LOG(LogTemp, Warning, TEXT("Processing DISCONNECT packet"));
            if (Header->PacketSize >= sizeof(DisconnectPacket))
            {
                HandleDisconnectPacket(reinterpret_cast<DisconnectPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        case EPacketType::PONG:
            UE_LOG(LogTemp, Log, TEXT("Processing PONG packet"));
            if (Header->PacketSize >= sizeof(PongPacket))
            {
                HandlePongPacket(reinterpret_cast<PongPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        default:
            UE_LOG(LogTemp, Error, TEXT(">>> UNKNOWN PACKET TYPE: %d <<<"), static_cast<int32>(Header->PacketType));
            if (bEnableNetworkLogging)
            {
                UE_LOG(LogTemp, Warning, TEXT("Unknown packet type: %d"), static_cast<int32>(Header->PacketType));
            }
            break;
        }

        // 처리된 바이트 수 갱신
        ProcessedBytes += Header->PacketSize;
        //UE_LOG(LogTemp, Log, TEXT("Packet processed, total processed bytes: %d"), ProcessedBytes);
    }

    // 처리된 데이터 제거
    if (ProcessedBytes > 0)
    {
        //UE_LOG(LogTemp, Log, TEXT("Removing %d processed bytes from buffer"), ProcessedBytes);
        PacketProcessBuffer.RemoveAt(0, ProcessedBytes);
    }

    //UE_LOG(LogTemp, Log, TEXT("ProcessReceivedData completed - Processed %d packets, Remaining buffer: %d bytes"),
    //    PacketCount, PacketProcessBuffer.Num());
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
        return false;
    }

    // 패킷 타입 검증
    if (!UPacketHelper::IsValidPacketType(static_cast<uint8>(Header->PacketType)))
    {
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
    CurrentPlayerId = Packet->ClientId;

    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Received client ID from server: %d"), CurrentPlayerId);
    }

    // OnPlayerJoined 델리게이트 호출 (자신의 ID)
    OnPlayerJoined.Broadcast(CurrentPlayerId);
}

void UNetworkManager::HandleOutputPacket(const OutputPacket* Packet)
{
    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, Log, TEXT("Received position for PlayerId: %d (CurrentId: %d)"), Packet->ClientId, CurrentPlayerId);
    }

    // UE 좌표계로 변환
    FVector Position = UPacketHelper::Vec3ToFVector(Packet->Position);
    FRotator Rotation = UPacketHelper::Rot3ToFRotator(Packet->Rotation);
    FVector Velocity = UPacketHelper::Vec3ToFVector(Packet->Velocity);

    FTransform NewTransform(Rotation, Position);

    // 위치 업데이트 델리게이트 호출 (속도 정보 포함)
    OnPlayerUpdated.Broadcast(Packet->ClientId, NewTransform, Velocity, Packet->State, Packet->Action);

    // 상태 변경 델리게이트 호출
    //OnPlayerStateChanged.Broadcast(Packet->ClientId, Packet->State);


    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, Log, TEXT("Position Update: ClientID=%d, Pos=(%f, %f, %f), State=%d, Action=%d"),
            Packet->ClientId, Position.X, Position.Y, Position.Z, static_cast<int>(Packet->State), static_cast<int>(Packet->Action));
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
        UE_LOG(LogTemp, Log, TEXT("Pong received: ClientId=%d, Ping=%.2f ms"), Packet->ClientId, CurrentPingTime);
    }
}

void UNetworkManager::SendPing()
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    PingPacket Packet;
    Packet.Header.PacketType = EPacketType::PING;
    Packet.Header.PacketSize = sizeof(PingPacket);
    Packet.ClientId = CurrentPlayerId;
    Packet.PingTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64()); // 서버와 동일한 uint64 타입

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
        UE_LOG(LogTemp, Log, TEXT("Sent player init info: ClientId=%d, Pos=(%f,%f,%f)"),
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

    // 입력 데이터 (새 서버 구조에 맞춤)
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.RotationPitch = RotationPitch;  // 서버: RotationPitch
    Packet.RotationYaw = RotationYaw;      // 서버: RotationYaw
    Packet.RotationRoll = RotationRoll;    // 서버: RotationRoll

    // 이벤트 데이터
    Packet.bRunPressed = bRunPressed; 
    Packet.bJumpPressed = bJumpPressed;
    Packet.bAttackPressed = bAttackPressed;
    Packet.bDefendPressed = bDefendPressed;

    SendPacket(&Packet, sizeof(Packet));

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, Log, TEXT("Sent input: F=%.2f R=%.2f Y=%.1f Run=%d Jump=%d Attack=%d Defense=%d"),
            ForwardValue, RightValue, RotationYaw, bRunPressed, bJumpPressed, bAttackPressed, bDefendPressed);
    }
}

bool UNetworkManager::SendPacket(const void* Data, int32 Size)
{
    if (!IsConnected() || !Data || Size <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Send failed"));
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

	//UE_LOG(LogTemp, Log, TEXT("Packet sent successfully: %d bytes"), Size);

    return true;
}