// NetworkManager.cpp
// �������� ����� �����ϴ� Ŭ���� ����

#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "GameFramework/GameModeBase.h"

void UNetworkManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // ���� ���� �ʱ�ȭ
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
    // �̹� ����� ��� ���� ���� ����
    if (IsConnected())
    {
        DisconnectFromServer();
    }

    // ���� ����ý��� ��������
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Socket subsystem not found"));
        return false;
    }

    // ���� �ּ� ���� �� ����
    ServerAddress = SocketSubsystem->CreateInternetAddr();
    bool bIsValid = false;
    ServerAddress->SetIp(*IpAddress, bIsValid);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid IP address: %s"), *IpAddress);
        return false;
    }

    ServerAddress->SetPort(Port);

    // TCP ���� ����
    Socket = MakeShareable(SocketSubsystem->CreateSocket(NAME_Stream, TEXT("GameClient"), false));
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
        return false;
    }

    // ���� �ɼ� ����
    int32 ActualBufferSize = 0;

    // �񵿱� ��� ����
    Socket->SetNonBlocking(true);

    // �ּ� ���� ����
    Socket->SetReuseAddr(true);

    // ���� ũ�� ����
    Socket->SetReceiveBufferSize(1024 * 64, ActualBufferSize);
    Socket->SetSendBufferSize(1024 * 64, ActualBufferSize);

    // TCP_NODELAY ���� (Nagle �˰��� ��Ȱ��ȭ)
    Socket->SetNoDelay(true);

    // ���� ���� �õ�
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

    // ��Ʈ��ũ Ÿ�̸� ����
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            NetworkTimerHandle,
            this,
            &UNetworkManager::OnNetworkTimerTick,
            0.01f, // 100Hz�� ��Ʈ��ũ ������Ʈ
            true
        );

        // Ping Ÿ�̸� ����
        World->GetTimerManager().SetTimer(
            PingTimerHandle,
            this,
            &UNetworkManager::OnPingTimerTick,
            1.0f, // 1�ʸ��� Ping ����
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

    // ��� ���� ������ Ȯ��
    if (!Socket->HasPendingData(PendingDataSize) || PendingDataSize == 0)
    {
        return;
    }

    // �ʿ��� ��� ���� ũ�� ����
    if (PendingDataSize > static_cast<uint32>(ReceiveBuffer.Num()))
    {
        ReceiveBuffer.SetNumUninitialized(PendingDataSize);
    }

    int32 BytesRead = 0;

    // ������ �б�
    if (Socket->Recv(ReceiveBuffer.GetData(), ReceiveBuffer.Num(), BytesRead))
    {
        if (BytesRead > 0)
        {
            // ���� ������ ó��
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
    // ���� ó�� ���ۿ� �� ������ �߰�
    PacketProcessBuffer.Append(Data.GetData(), BytesRead);

    // ��Ŷ ó��
    int32 ProcessedBytes = 0;
    while (ProcessedBytes + sizeof(PacketHeader) <= PacketProcessBuffer.Num())
    {
        // ��Ŷ ��� ��������
        PacketHeader* Header = reinterpret_cast<PacketHeader*>(PacketProcessBuffer.GetData() + ProcessedBytes);

        // ��Ŷ ��ü�� �����ߴ��� Ȯ��
        if (ProcessedBytes + Header->PacketSize > PacketProcessBuffer.Num())
        {
            break;
        }

        // ��Ŷ Ÿ�Կ� ���� ó��
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

        // ó���� ����Ʈ �� ����
        ProcessedBytes += Header->PacketSize;
    }

    // ó���� ������ ����
    if (ProcessedBytes > 0)
    {
        PacketProcessBuffer.RemoveAt(0, ProcessedBytes);
    }
}

void UNetworkManager::HandleClientIdPacket(const ClientIdPacket* Packet)
{
    CurrentPlayerId = Packet->ClientId;
    UE_LOG(LogTemp, Log, TEXT("Received client ID from server: %d"), CurrentPlayerId);

    // OnPlayerJoined ��������Ʈ ȣ�� (�ڽ��� ID)
    OnPlayerJoined.Broadcast(CurrentPlayerId);
}

void UNetworkManager::HandlePositionPacket(const PositionPacket* Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Received position for PlayerId: %d (CurrentId: %d)"), Packet->ClientId, CurrentPlayerId);

    FVector Position(Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
    FRotator Rotation(0.0f, 0.0f, 0.0f); // �������� ��ü ȸ������ ������ �����Ƿ� �ӽ÷� ����

    // Rotation�� ������ �ݿ�
    if (Packet->Header.PacketSize >= sizeof(PositionPacket))
    {
        Rotation = FRotator(0.0f, Packet->Rotation.Yaw, 0.0f);
    }

    FTransform NewTransform(Rotation, Position);

    // ��ġ ������Ʈ ��������Ʈ ȣ��
    OnPlayerPositionUpdated.Broadcast(Packet->ClientId, NewTransform);

    // ���� ���� ��������Ʈ ȣ��
    OnPlayerStateChanged.Broadcast(Packet->ClientId, Packet->State);

    UE_LOG(LogTemp, Warning, TEXT("Position Update: ClientID=%d, Pos=(%f, %f, %f), State=%d"),
        Packet->ClientId, Position.X, Position.Y, Position.Z, static_cast<int>(Packet->State));

}

void UNetworkManager::HandleDisconnectPacket(const DisconnectPacket* Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Player disconnected: %d"), Packet->ClientId);

    // �÷��̾� ���� ��������Ʈ ȣ��
    OnPlayerLeft.Broadcast(Packet->ClientId);
}

void UNetworkManager::HandlePongPacket(const PongPacket* Packet)
{
    LastPongReceivedTime = FPlatformTime::Seconds();
    float PingTime = (LastPongReceivedTime - LastPingSentTime) * 1000.0f; // ms ����

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

    // Movement ������
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.Pitch = Pitch;
    Packet.Yaw = Yaw;
    Packet.Roll = Roll;

    // Event ������
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