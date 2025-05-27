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

    // ���� �ɼ� ���� (������ �����ϰ�)
    int32 ActualBufferSize = 0;

    // �񵿱� ��� ����
    Socket->SetNonBlocking(true);

    // �ּ� ���� ����
    Socket->SetReuseAddr(true);

    // ���� ũ�� ����
    Socket->SetReceiveBufferSize(MaxReceiveBufferSize, ActualBufferSize);
    Socket->SetSendBufferSize(MaxReceiveBufferSize, ActualBufferSize);

    // TCP_NODELAY ���� (Nagle �˰��� ��Ȱ��ȭ) - ������ ����
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

    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Connected to server: %s:%d"), *IpAddress, Port);
    }

    OnConnectionStatusChanged.Broadcast(true);

    // ��Ʈ��ũ Ÿ�̹� ����
    if (UWorld* World = GetWorld())
    {
        // ��Ʈ��ũ ������Ʈ Ÿ�̸� (100Hz)
        World->GetTimerManager().SetTimer(
            NetworkTimerHandle,
            this,
            &UNetworkManager::OnNetworkTimerTick,
            1.0f / NetworkUpdateRate,
            true
        );

        // Ping Ÿ�̸� (1�ʸ���)
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

    // ���� Ÿ�Ӿƿ� �˻�
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

    // ��� ���� ������ Ȯ��
    if (!Socket->HasPendingData(PendingDataSize) || PendingDataSize == 0)
    {
        return;
    }

    // �ʿ��� ��� ���� ũ�� ����
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

    // ������ �б�
    if (Socket->Recv(ReceiveBuffer.GetData(), FMath::Min(static_cast<int32>(PendingDataSize), ReceiveBuffer.Num()), BytesRead))
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

        // ��Ŷ ��� ����
        if (!ValidatePacketHeader(Header, PacketProcessBuffer.Num() - ProcessedBytes))
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid packet header detected, clearing buffer"));
            PacketProcessBuffer.Empty();
            break;
        }

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
            if (bEnableNetworkLogging)
            {
                UE_LOG(LogTemp, Warning, TEXT("Unknown packet type: %d"), static_cast<int32>(Header->PacketType));
            }
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

bool UNetworkManager::ValidatePacketHeader(const PacketHeader* Header, int32 AvailableBytes)
{
    if (!Header)
    {
        return false;
    }

    // ��Ŷ ũ�� ����
    if (Header->PacketSize < sizeof(PacketHeader) || Header->PacketSize > MaxReceiveBufferSize)
    {
        return false;
    }

    // ��Ŷ Ÿ�� ����
    if (!UPacketHelper::IsValidPacketType(static_cast<uint8>(Header->PacketType)))
    {
        return false;
    }

    // ��� ������ ����Ʈ �� ����
    if (Header->PacketSize > AvailableBytes)
    {
        return false; // ���� ������ ���ŵ��� ����
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

    // OnPlayerJoined ��������Ʈ ȣ�� (�ڽ��� ID)
    OnPlayerJoined.Broadcast(CurrentPlayerId);
}

void UNetworkManager::HandlePositionPacket(const PositionPacket* Packet)
{
    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Received position for PlayerId: %d (CurrentId: %d)"), Packet->ClientId, CurrentPlayerId);
    }

    // UE ��ǥ��� ��ȯ
    FVector Position = UPacketHelper::Vec3ToFVector(Packet->Position);
    FRotator Rotation = UPacketHelper::Rot3ToFRotator(Packet->Rotation);
    FVector Velocity = UPacketHelper::Vec3ToFVector(Packet->Velocity);

    FTransform NewTransform(Rotation, Position);

    // ��ġ ������Ʈ ��������Ʈ ȣ�� (�ӵ� ���� ����)
    OnPlayerPositionUpdated.Broadcast(Packet->ClientId, NewTransform, Velocity);

    // ���� ���� ��������Ʈ ȣ��
    OnPlayerStateChanged.Broadcast(Packet->ClientId, Packet->State);

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Position Update: ClientID=%d, Pos=(%f, %f, %f), State=%d"),
            Packet->ClientId, Position.X, Position.Y, Position.Z, static_cast<int>(Packet->State));
    }
}

void UNetworkManager::HandleDisconnectPacket(const DisconnectPacket* Packet)
{
    if (bEnableNetworkLogging)
    {
        UE_LOG(LogTemp, Log, TEXT("Player disconnected: %d"), Packet->ClientId);
    }

    // �÷��̾� ���� ��������Ʈ ȣ��
    OnPlayerLeft.Broadcast(Packet->ClientId);
}

void UNetworkManager::HandlePongPacket(const PongPacket* Packet)
{
    uint64 CurrentTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());
    LastPongReceivedTime = CurrentTime;

    // �� �ð� ��� (ms ����)
    if (LastPingSentTime > 0)
    {
        CurrentPingTime = static_cast<float>(CurrentTime - LastPingSentTime);
    }

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Pong received: ClientId=%d, Ping=%.2f ms"), Packet->ClientId, CurrentPingTime);
    }
}

void UNetworkManager::SendPing()
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    PingPacket Packet;
    Packet.Header.PacketType = EPacketType::PING;
    Packet.Header.PacketSize = sizeof(PingPacket);
    Packet.ClientId = CurrentPlayerId;
    Packet.PingTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64()); // ������ ������ uint64 Ÿ��

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
        UE_LOG(LogTemp, Verbose, TEXT("Sent player init info: ClientId=%d, Pos=(%f,%f,%f)"),
            CurrentPlayerId, Position.X, Position.Y, Position.Z);
    }
}

void UNetworkManager::SendPlayerInput(float ForwardValue, float RightValue,
    float RotationPitch, float RotationYaw, float RotationRoll,
    bool bRunPressed, bool bJumpPressed, bool bAttackPressed)
{
    if (!IsConnected() || CurrentPlayerId < 0) return;

    InputPacket Packet;
    Packet.Header.PacketType = EPacketType::PLAYER_INPUT_INFO;
    Packet.Header.PacketSize = sizeof(InputPacket);
    Packet.ClientId = CurrentPlayerId;

    // �Է� ������ (�� ���� ������ ����)
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.RotationPitch = RotationPitch;  // ����: RotationPitch
    Packet.RotationYaw = RotationYaw;      // ����: RotationYaw
    Packet.RotationRoll = RotationRoll;    // ����: RotationRoll

    // �̺�Ʈ ������
    Packet.bJumpPressed = bJumpPressed;
    Packet.bAttackPressed = bAttackPressed;
    Packet.bRunPressed = bRunPressed;

    SendPacket(&Packet, sizeof(Packet));

    if (bLogPacketDetails)
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Sent input: F=%.2f R=%.2f Y=%.1f Run=%d Jump=%d Attack=%d"),
            ForwardValue, RightValue, RotationYaw, bRunPressed, bJumpPressed, bAttackPressed);
    }
}

bool UNetworkManager::SendPacket(const void* Data, int32 Size)
{
    if (!IsConnected() || !Data || Size <= 0)
    {
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

    return true;
}