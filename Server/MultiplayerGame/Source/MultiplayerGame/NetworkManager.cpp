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
    ReceiveBuffer.SetNumUninitialized(1024);
    PacketProcessBuffer.Reserve(1024);

    UE_LOG(LogTemp, Log, TEXT("NetworkManager initialized"));
}

void UNetworkManager::Deinitialize()
{
    DisconnectFromServer();
    Super::Deinitialize();

    UE_LOG(LogTemp, Log, TEXT("NetworkManager cleaned up"));
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

    // 소켓 옵션 설정
    int32 ActualBufferSize = 0;

    // 비동기 모드 설정
    Socket->SetNonBlocking(true);

    // 주소 재사용 설정
    Socket->SetReuseAddr(true);

    // 버퍼 크기 설정
    Socket->SetReceiveBufferSize(1024 * 64, ActualBufferSize);
    Socket->SetSendBufferSize(1024 * 64, ActualBufferSize);

    // TCP_NODELAY 설정 (Nagle 알고리즘 비활성화)
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

    UE_LOG(LogTemp, Log, TEXT("Connected to server: %s:%d"), *IpAddress, Port);
    OnConnectionStatusChanged.Broadcast(true);

    // 네트워크 타이머 시작
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            NetworkTimerHandle,
            this,
            &UNetworkManager::OnNetworkTimerTick,
            0.01f, // 100Hz로 네트워크 업데이트
            true
        );

        // Ping 타이머 시작
        World->GetTimerManager().SetTimer(
            PingTimerHandle,
            this,
            &UNetworkManager::OnPingTimerTick,
            1.0f, // 1초마다 Ping 전송
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
        UE_LOG(LogTemp, Log, TEXT("Server connection closed"));
    }

    CurrentPlayerId = -1;
}

void UNetworkManager::OnNetworkTimerTick()
{
    if (!IsConnected())
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
        ReceiveBuffer.SetNumUninitialized(PendingDataSize);
    }

    int32 BytesRead = 0;

    // 데이터 읽기
    if (Socket->Recv(ReceiveBuffer.GetData(), ReceiveBuffer.Num(), BytesRead))
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
    // 기존 처리 버퍼에 새 데이터 추가
    PacketProcessBuffer.Append(Data.GetData(), BytesRead);

    // 패킷 처리
    int32 ProcessedBytes = 0;
    while (ProcessedBytes + sizeof(PacketHeader) <= PacketProcessBuffer.Num())
    {
        // 패킷 헤더 가져오기
        PacketHeader* Header = reinterpret_cast<PacketHeader*>(PacketProcessBuffer.GetData() + ProcessedBytes);

        // 패킷 전체가 도착했는지 확인
        if (ProcessedBytes + Header->PacketSize > PacketProcessBuffer.Num())
        {
            break;
        }

        // 패킷 타입에 따라 처리
        switch (Header->PacketType)
        {
        case EPacketType::CLIENT_ID:
            if (Header->PacketSize >= sizeof(ClientIdPacket))
            {
                HandleClientIdPacket(reinterpret_cast<ClientIdPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        case EPacketType::PLAYER_POSITION_INFO:
            if (Header->PacketSize >= sizeof(PositionPacket))
            {
				HandlePositionPacket(reinterpret_cast<PositionPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        case EPacketType::PLAYER_INIT_INFO:
            if (Header->PacketSize >= sizeof(PositionPacket))
            {
                HandlePositionPacket(reinterpret_cast<PositionPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        case EPacketType::DISCONNECT:
            if (Header->PacketSize >= sizeof(DisconnectPacket))
            {
                HandleDisconnectPacket(reinterpret_cast<DisconnectPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        case EPacketType::PONG:
            if (Header->PacketSize >= sizeof(PongPacket))
            {
                HandlePongPacket(reinterpret_cast<PongPacket*>(PacketProcessBuffer.GetData() + ProcessedBytes));
            }
            break;

        default:
            UE_LOG(LogTemp, Warning, TEXT("Unknown packet type: %d"), static_cast<int32>(Header->PacketType));
            break;
        }

        // 처리된 바이트 수 갱신
        ProcessedBytes += Header->PacketSize;
    }

    // 처리된 데이터 제거
    if (ProcessedBytes > 0)
    {
        PacketProcessBuffer.RemoveAt(0, ProcessedBytes);
    }
}

void UNetworkManager::HandleClientIdPacket(const ClientIdPacket* Packet)
{
    CurrentPlayerId = Packet->ClientId;
    UE_LOG(LogTemp, Log, TEXT("Received client ID from server: %d"), CurrentPlayerId);

    // OnPlayerJoined 델리게이트 호출 (자신의 ID)
    OnPlayerJoined.Broadcast(CurrentPlayerId);
}

void UNetworkManager::HandlePositionPacket(const PositionPacket* Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Received position for PlayerId: %d (CurrentId: %d)"), Packet->ClientId, CurrentPlayerId);

    FVector Position(Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
    FRotator Rotation(0.0f, 0.0f, 0.0f); // 서버에서 전체 회전값을 보내지 않으므로 임시로 설정

    // Rotation이 있으면 반영
    if (Packet->Header.PacketSize >= sizeof(PositionPacket))
    {
        Rotation = FRotator(0.0f, Packet->Rotation.Yaw, 0.0f);
    }

    FTransform NewTransform(Rotation, Position);

    // 위치 업데이트 델리게이트 호출
    OnPlayerPositionUpdated.Broadcast(Packet->ClientId, NewTransform);

    // 상태 변경 델리게이트 호출
    OnPlayerStateChanged.Broadcast(Packet->ClientId, Packet->State);

    UE_LOG(LogTemp, Warning, TEXT("Position Update: ClientID=%d, Pos=(%f, %f, %f), State=%d"),
        Packet->ClientId, Position.X, Position.Y, Position.Z, static_cast<int>(Packet->State));

}

void UNetworkManager::HandleDisconnectPacket(const DisconnectPacket* Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Player disconnected: %d"), Packet->ClientId);

    // 플레이어 퇴장 델리게이트 호출
    OnPlayerLeft.Broadcast(Packet->ClientId);
}

void UNetworkManager::HandlePongPacket(const PongPacket* Packet)
{
    LastPongReceivedTime = FPlatformTime::Seconds();
    float PingTime = (LastPongReceivedTime - LastPingSentTime) * 1000.0f; // ms 단위

    UE_LOG(LogTemp, Verbose, TEXT("Pong received: ClientId=%d, Ping=%0.2f ms"), Packet->ClientId, PingTime);
}

void UNetworkManager::SendPing()
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    PingPacket Packet;
    Packet.Header.PacketType = EPacketType::PING;
    Packet.Header.PacketSize = sizeof(PingPacket);
    Packet.ClientId = CurrentPlayerId;
    Packet.PingTime = FPlatformTime::Seconds();

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
}

void UNetworkManager::SendPlayerInput(float ForwardValue, float RightValue, float Pitch, float Yaw, float Roll, bool bRunPressed, bool bCrouchPressed, bool bJumpPressed, bool bAttackPressed)
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    InputPacket Packet;
    Packet.Header.PacketType = EPacketType::PLAYER_INPUT_INFO;
    Packet.Header.PacketSize = sizeof(InputPacket);
    Packet.ClientId = CurrentPlayerId;

    // Movement 데이터
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.Pitch = Pitch;
    Packet.Yaw = Yaw;
    Packet.Roll = Roll;

    // Event 데이터
    Packet.bRunPressed = bRunPressed;
    Packet.bCrouchPressed = bCrouchPressed;
    Packet.bJumpPressed = bJumpPressed;
    Packet.bAttackPressed = bAttackPressed;

    SendPacket(&Packet, sizeof(Packet));
}

//void UNetworkManager::SendPlayerMovement(float ForwardValue, float RightValue, Rot3 Rotation)
//{
//    if (!IsConnected() || CurrentPlayerId < 0) return;
//
//    MovementInfoPacket Packet;
//    Packet.Header.PacketType = EPacketType::PLAYER_MOVEMENT_INFO;
//    Packet.Header.PacketSize = sizeof(MovementInfoPacket);
//    Packet.ClientId = CurrentPlayerId;
//    Packet.ForwardValue = ForwardValue;
//    Packet.RightValue = RightValue;
//	Packet.Rotation = Rotation;
//
//    SendPacket(&Packet, sizeof(Packet));
//}
//
//void UNetworkManager::SendPlayerEvent(bool bRunPressed, bool bCrouchPressed, bool bJumpPressed, bool bAttackPressed)
//{
//    if (!IsConnected() || CurrentPlayerId < 0) return;
//
//    EventInfoPacket Packet;
//    Packet.Header.PacketType = EPacketType::PLAYER_EVENT_INFO;
//    Packet.Header.PacketSize = sizeof(EventInfoPacket);
//    Packet.ClientId = CurrentPlayerId;
//    Packet.bRunPressed = bRunPressed;
//    Packet.bCrouchPressed = bCrouchPressed;
//    Packet.bJumpPressed = bJumpPressed;
//    Packet.bAttackPressed = bAttackPressed;
//
//	SendPacket(&Packet, sizeof(Packet));
//}

bool UNetworkManager::SendPacket(const void* Data, int32 Size)
{
    if (!IsConnected() || !Data || Size <= 0) return false;

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

    return true;
}