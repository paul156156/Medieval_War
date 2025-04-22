#include "NetworkManager.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "IPAddress.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UNetworkManager::UNetworkManager()
    : Socket(nullptr)
    , bIsConnected(false)
    , LastErrorCode(0)
    , LocalClientId(-1)
{
    // ���� ���� �ʱ�ȭ
    FMemory::Memzero(RecvBuffer, sizeof(RecvBuffer));
}

UNetworkManager::~UNetworkManager()
{
    // �Ҹ��ڿ��� ���� ����
    DisconnectFromServer();
}

bool UNetworkManager::ConnectToServer(const FString& IPAddress, int32 Port)
{
    // �̹� ����Ǿ� ������ ���� ����
    if (Socket)
    {
        DisconnectFromServer();
    }

    // ���� ����ý��� ��������
    ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Socket Subsystem not found"));
        LastErrorCode = 1;
        return false;
    }

    // ���� ����
    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("Default TCP Socket"), true);
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
        LastErrorCode = 2;
        return false;
    }

    // ���� ��������Ʈ ����
    FIPv4Address ServerIP;
    FIPv4Address::Parse(IPAddress, ServerIP);
    ServerEndpoint = FIPv4Endpoint(ServerIP, Port);

    // ���� ����
    if (!Socket->Connect(*ServerEndpoint.ToInternetAddr()))
    {
        LastErrorCode = SocketSubsystem->GetLastErrorCode();
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to server %s:%d (Error: %d)"),
            *IPAddress, Port, LastErrorCode);
        SocketSubsystem->DestroySocket(Socket);
        Socket = nullptr;
        return false;
    }

    // ����ŷ ��� ����
    Socket->SetNonBlocking(true);

    // ���� ����
    bIsConnected = true;
    UE_LOG(LogTemp, Display, TEXT("Connected to server %s:%d"), *IPAddress, Port);

    // ��Ŷ ���� Ÿ�̸� ����
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            PacketReceiverTimerHandle,
            FTimerDelegate::CreateUObject(this, &UNetworkManager::ProcessIncomingPackets),
            0.01f, // 10ms �������� ��Ŷ ���� Ȯ��
            true
        );
    }

    // ���� ���� ���� �̺�Ʈ �߻�
    OnConnectionStatusChanged.Broadcast(true);

    return true;
}

void UNetworkManager::DisconnectFromServer()
{
    if (Socket)
    {
        // Ÿ�̸� ����
        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().ClearTimer(PacketReceiverTimerHandle);
        }

        // ���� �ݱ�
        ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        if (SocketSubsystem)
        {
            Socket->Close();
            SocketSubsystem->DestroySocket(Socket);
            Socket = nullptr;
        }

        bIsConnected = false;
        LocalClientId = -1;  // Ŭ���̾�Ʈ ID �ʱ�ȭ

        UE_LOG(LogTemp, Display, TEXT("Disconnected from server"));

        // ���� ���� ���� �̺�Ʈ �߻� (�̹� ȣ����� �ʾҴٸ�)
        OnConnectionStatusChanged.Broadcast(false);
    }
}

void UNetworkManager::SendMovePacket(float ForwardValue, float RightValue, const FVector& Position, const FRotator& Rotation)
{
    if (!IsConnected())
    {
        return;
    }

    // �̵� ��Ŷ ����
    FMovePacket Packet;
    Packet.Header.PacketType = EPacketType::MOVE;
    Packet.Header.PacketSize = sizeof(FMovePacket);
    Packet.ForwardValue = ForwardValue;
    Packet.RightValue = RightValue;
    Packet.Position.X = Position.X;
    Packet.Position.Y = Position.Y;
    Packet.Position.Z = Position.Z;
    Packet.Rotation.Pitch = Rotation.Pitch;
    Packet.Rotation.Yaw = Rotation.Yaw;
    Packet.Rotation.Roll = Rotation.Roll;

    // �ӵ� ���� �߰�
    FVector Velocity = FVector::ZeroVector;

    // ĳ���Ϳ��� �ӵ� ��������
    ACharacter* Character = Cast<ACharacter>(GetOuter());
    if (Character)
    {
        Velocity = Character->GetVelocity();
    }

    Packet.Velocity.X = Velocity.X;
    Packet.Velocity.Y = Velocity.Y;
    Packet.Velocity.Z = Velocity.Z;

    // ��Ŷ ����
    int32 BytesSent = 0;
    bool bSuccess = Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FMovePacket), BytesSent);

    // ���� ���� �� ���� ���� üũ
    if (!bSuccess || BytesSent != sizeof(FMovePacket))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to send Move packet! Sent %d of %d bytes"),
            BytesSent, sizeof(FMovePacket));
        CheckConnectionStatus();
    }
    else
    {
        // ����� �α� (Verbose ����)
        UE_LOG(LogTemp, Verbose, TEXT("Sent Move Packet: Forward=%.2f, Right=%.2f, Pos=(%.2f,%.2f,%.2f), Vel=(%.2f,%.2f,%.2f)"),
            ForwardValue, RightValue, Position.X, Position.Y, Position.Z, Velocity.X, Velocity.Y, Velocity.Z);
    }
}

void UNetworkManager::SendJumpPacket(bool IsJumping, const FVector& Position)
{
    if (!IsConnected())
    {
        return;
    }

    // ���� ��Ŷ ����
    FJumpPacket Packet;
    Packet.Header.PacketType = EPacketType::JUMP;
    Packet.Header.PacketSize = sizeof(FJumpPacket);
    Packet.IsJumping = IsJumping;
    Packet.Position.X = Position.X;
    Packet.Position.Y = Position.Y;
    Packet.Position.Z = Position.Z;

    // �ӵ� ���� �߰�
    FVector Velocity = FVector::ZeroVector;

    // ĳ���Ϳ��� �ӵ� ��������
    ACharacter* Character = Cast<ACharacter>(GetOuter());
    if (Character)
    {
        Velocity = Character->GetVelocity();
    }

    Packet.Velocity.X = Velocity.X;
    Packet.Velocity.Y = Velocity.Y;
    Packet.Velocity.Z = Velocity.Z;

    // ��Ŷ ����
    int32 BytesSent = 0;
    bool bSuccess = Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FJumpPacket), BytesSent);

    // ���� ���� �� ���� ���� üũ
    if (!bSuccess || BytesSent != sizeof(FJumpPacket))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to send Jump packet! Sent %d of %d bytes"),
            BytesSent, sizeof(FJumpPacket));
        CheckConnectionStatus();
    }
    else
    {
        // ����� �α� (Verbose ����)
        UE_LOG(LogTemp, Verbose, TEXT("Sent Jump Packet: Jumping=%s, Pos=(%.2f,%.2f,%.2f), Vel=(%.2f,%.2f,%.2f)"),
            IsJumping ? TEXT("true") : TEXT("false"), Position.X, Position.Y, Position.Z, Velocity.X, Velocity.Y, Velocity.Z);
    }
}

void UNetworkManager::ProcessIncomingPackets()
{
    if (!IsConnected())
    {
        return;
    }

    uint32 PendingDataSize = 0;

    // ���� ��� ������ ũ�� Ȯ��
    if (Socket->HasPendingData(PendingDataSize) && PendingDataSize > 0)
    {
        // ������ ����
        int32 BytesRead = 0;
        bool bSuccess = Socket->Recv(RecvBuffer, FMath::Min(PendingDataSize, (uint32)sizeof(RecvBuffer)), BytesRead);

        if (!bSuccess)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to receive data from server"));
            CheckConnectionStatus();
            return;
        }

        if (BytesRead >= sizeof(FPacketHeader))
        {
            // ��Ŷ ��� ����
            FPacketHeader* Header = reinterpret_cast<FPacketHeader*>(RecvBuffer);

            // ��Ŷ ���� ����� �α�
            UE_LOG(LogTemp, Display, TEXT("Received packet - Type: %d, Size: %d, BytesRead: %d"),
                (int32)Header->PacketType, Header->PacketSize, BytesRead);

            // ��Ŷ Ÿ�Կ� ���� ó��
            switch (Header->PacketType)
            {
            case EPacketType::POSITION_UPDATE:
                if (BytesRead >= sizeof(FPositionUpdatePacket))
                {
                    FPositionUpdatePacket* Packet = reinterpret_cast<FPositionUpdatePacket*>(RecvBuffer);
                    UE_LOG(LogTemp, Display, TEXT("Position Update Packet - Client ID: %d, Pos: (%.1f, %.1f, %.1f), Vel: (%.1f, %.1f, %.1f)"),
                        Packet->ClientId, Packet->Position.X, Packet->Position.Y, Packet->Position.Z,
                        Packet->Velocity.X, Packet->Velocity.Y, Packet->Velocity.Z);
                    HandlePositionUpdatePacket(Packet);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Incomplete position update packet received"));
                }
                break;
            case EPacketType::CLIENT_ID:
                if (BytesRead >= sizeof(FClientIdPacket))
                {
                    FClientIdPacket* Packet = reinterpret_cast<FClientIdPacket*>(RecvBuffer);
                    UE_LOG(LogTemp, Display, TEXT("Client ID Packet - Client ID: %d"), Packet->ClientId);
                    HandleClientIdPacket(Packet);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Incomplete client ID packet received"));
                }
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Unknown packet type received: %d"), (int32)Header->PacketType);
                break;
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Received incomplete packet header, size: %d"), BytesRead);
        }
    }
}

void UNetworkManager::HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet)
{
    if (!Packet)
    {
        return;
    }

    // ��ġ ���� ����
    FVector NewPosition(Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
    FRotator NewRotation(Packet->Rotation.Pitch, Packet->Rotation.Yaw, Packet->Rotation.Roll);
    FVector NewVelocity(Packet->Velocity.X, Packet->Velocity.Y, Packet->Velocity.Z);  // �ӵ� ���� ����
    bool bIsJumping = Packet->IsJumping;
    int32 ClientId = Packet->ClientId;

    // ���� �÷��̾��� ������Ʈ�� ���� (�������� �����ص�)
    if (ClientId == LocalClientId)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Ignored position update for local player (ID: %d)"), ClientId);
        return;
    }

    // ���� ��������Ʈ ȣ�� (���Ž� ������ ���� ����)
    OnPositionUpdate.Broadcast(NewPosition);
    OnRotationUpdate.Broadcast(NewRotation);
    OnJumpStateUpdate.Broadcast(bIsJumping);

    // ���� �÷��̾� ������Ʈ ��������Ʈ ȣ�� (���ο� ���, �ӵ� ���� ����)
    OnPlayerUpdate.Broadcast(ClientId, NewPosition, NewRotation, NewVelocity, bIsJumping);

    // ����� �α�
    UE_LOG(LogTemp, Verbose, TEXT("Position Update from client %d: Pos=(%.1f,%.1f,%.1f), Vel=(%.1f,%.1f,%.1f), Jumping=%s"),
        ClientId, NewPosition.X, NewPosition.Y, NewPosition.Z,
        NewVelocity.X, NewVelocity.Y, NewVelocity.Z,
        bIsJumping ? TEXT("true") : TEXT("false"));
}

void UNetworkManager::HandleClientIdPacket(const FClientIdPacket* Packet)
{
    if (!Packet)
    {
        return;
    }

    // Ŭ���̾�Ʈ ID ����
    LocalClientId = Packet->ClientId;

    // Ŭ���̾�Ʈ ID ���� �̺�Ʈ �߻�
    OnClientIdReceived.Broadcast(LocalClientId);

    UE_LOG(LogTemp, Display, TEXT("Received client ID: %d"), LocalClientId);
}

bool UNetworkManager::IsConnected() const
{
    return Socket != nullptr && bIsConnected;
}

void UNetworkManager::CheckConnectionStatus()
{
    if (!Socket)
    {
        bIsConnected = false;
        return;
    }

    // ���� ���� ���� Ȯ��
    bool bConnectionLost = false;

    // ������ ���� �׽�Ʈ (0����Ʈ ����)
    int32 BytesSent = 0;
    if (!Socket->Send(nullptr, 0, BytesSent))
    {
        ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        if (SocketSubsystem)
        {
            LastErrorCode = SocketSubsystem->GetLastErrorCode();
            if (LastErrorCode != 0)
            {
                bConnectionLost = true;
            }
        }
    }

    if (bConnectionLost)
    {
        UE_LOG(LogTemp, Warning, TEXT("Connection to server lost (Error: %d)"), LastErrorCode);
        bIsConnected = false;
        OnConnectionStatusChanged.Broadcast(false);

        // ���� ���� ó��
        DisconnectFromServer();
    }
}