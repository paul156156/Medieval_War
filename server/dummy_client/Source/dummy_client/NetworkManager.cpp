#include "NetworkManager.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "IPAddress.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

UNetworkManager::UNetworkManager()
    : Socket(nullptr)
    , bIsConnected(false)
{
    // ������
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
        return false;
    }

    // ���� ����
    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("Default"), true);
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket"));
        return false;
    }

    // ���� ��������Ʈ ����
    FIPv4Address ServerIP;
    FIPv4Address::Parse(IPAddress, ServerIP);
    ServerEndpoint = FIPv4Endpoint(ServerIP, Port);

    // ���� ����
    if (!Socket->Connect(*ServerEndpoint.ToInternetAddr()))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to server %s:%d"), *IPAddress, Port);
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
        UE_LOG(LogTemp, Display, TEXT("Disconnected from server"));
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

    // ��Ŷ ����
    int32 BytesSent = 0;
    Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FMovePacket), BytesSent);
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

    // ��Ŷ ����
    int32 BytesSent = 0;
    Socket->Send(reinterpret_cast<uint8*>(&Packet), sizeof(FJumpPacket), BytesSent);
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
        Socket->Recv(RecvBuffer, FMath::Min(PendingDataSize, (uint32)sizeof(RecvBuffer)), BytesRead);

        if (BytesRead >= sizeof(FPacketHeader))
        {
            // ��Ŷ ��� ����
            FPacketHeader* Header = reinterpret_cast<FPacketHeader*>(RecvBuffer);

            // ��Ŷ Ÿ�Կ� ���� ó��
            switch (Header->PacketType)
            {
            case EPacketType::POSITION_UPDATE:
                if (BytesRead >= sizeof(FPositionUpdatePacket))
                {
                    HandlePositionUpdatePacket(reinterpret_cast<FPositionUpdatePacket*>(RecvBuffer));
                }
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Unknown packet type received: %d"), (int32)Header->PacketType);
                break;
            }
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

    // ��������Ʈ ȣ��
    OnPositionUpdate.Broadcast(NewPosition);

    // ����� �α�
    UE_LOG(LogTemp, Verbose, TEXT("Position Update: X=%.2f Y=%.2f Z=%.2f"),
        Packet->Position.X, Packet->Position.Y, Packet->Position.Z);
}

bool UNetworkManager::IsConnected() const
{
    return Socket != nullptr && bIsConnected;
}