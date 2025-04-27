#include "SimpleNetworkManager.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "SimpleNetworkReplicator.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimpleNetwork, Log, All);

USimpleNetworkManager::USimpleNetworkManager()
    : Socket(nullptr)
    , Replicator(nullptr)
    , bConnected(false)
{
}

bool USimpleNetworkManager::ConnectToServer(const FString& ServerAddress, int32 Port)
{
    SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

    Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("SimpleNetworkSocket"), false);
    if (!Socket)
    {
        UE_LOG(LogSimpleNetwork, Error, TEXT("Socket creation failed"));
        return false;
    }

    FIPv4Address IP;
    FIPv4Address::Parse(ServerAddress, IP);

    TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
    Addr->SetIp(IP.Value);
    Addr->SetPort(Port);

    bool bResult = Socket->Connect(*Addr);

    if (bResult)
    {
        bConnected = true;
        UE_LOG(LogSimpleNetwork, Display, TEXT("Connected to server %s:%d"), *ServerAddress, Port);
    }
    else
    {
        UE_LOG(LogSimpleNetwork, Error, TEXT("Failed to connect to server"));
    }

    return bResult;
}

bool USimpleNetworkManager::IsConnected() const
{
	return bConnected;
}

bool USimpleNetworkManager::Disconnect()
{
    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
    bConnected = false;
    return true;
}

void USimpleNetworkManager::TickReceive(float DeltaTime)
{
    if (!bConnected || !Socket)
        return;

    uint32 PendingDataSize = 0;
    if (Socket->HasPendingData(PendingDataSize))
    {
        uint8 RecvBuffer[4096];
        int32 BytesRead = 0;

        if (Socket->Recv(RecvBuffer, sizeof(RecvBuffer), BytesRead))
        {
            HandleIncomingPacket(RecvBuffer, BytesRead);
        }
    }
}

void USimpleNetworkManager::HandleIncomingPacket(const uint8* Data, int32 Size)
{
    if (!Replicator)
    {
        UE_LOG(LogSimpleNetwork, Warning, TEXT("Replicator is not set"));
        return;
    }

    const FPacketHeader* Header = reinterpret_cast<const FPacketHeader*>(Data);

    switch (Header->PacketType)
    {
    case EPacketType::CLIENT_ID:
    {
        const FClientIdPacket* ClientIdPacket = reinterpret_cast<const FClientIdPacket*>(Data);
        //LocalClientId = ClientIdPacket->ClientId;

        Replicator->HandleClientIdPacket(reinterpret_cast<const FClientIdPacket*>(Data));
    }
        break;
    case EPacketType::DISCONNECT:
		Replicator->HandleDisconnectPacket(reinterpret_cast<const FDisconnectPacket*>(Data));
        break;

    case EPacketType::POSITION_UPDATE:
        Replicator->HandlePositionUpdatePacket(reinterpret_cast<const FPositionUpdatePacket*>(Data));
        break;
    default:
        UE_LOG(LogSimpleNetwork, Warning, TEXT("Unknown packet type received: %d"), (int32)Header->PacketType);
        break;
    }
}

bool USimpleNetworkManager::SendRaw(const uint8* Data, int32 Size)
{
    if (!bConnected || !Socket)
        return false;

    int32 BytesSent = 0;
    return Socket->Send(Data, Size, BytesSent);
}

void USimpleNetworkManager::SendPingPacket(const FPingPacket& Packet)
{
    SendRaw(reinterpret_cast<const uint8*>(&Packet), sizeof(Packet));
}

void USimpleNetworkManager::SendInputPacket(const FInputPacket& Packet)
{
    SendRaw(reinterpret_cast<const uint8*>(&Packet), sizeof(Packet));
}

void USimpleNetworkManager::SetReplicator(USimpleNetworkReplicator* InReplicator)
{
    Replicator = InReplicator;
}