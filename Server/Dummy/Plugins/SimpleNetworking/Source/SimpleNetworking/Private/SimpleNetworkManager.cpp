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
        UE_LOG(LogSimpleNetwork, Error, TEXT("[SimpleNetworkManager] Socket creation failed"));
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
        UE_LOG(LogSimpleNetwork, Display, TEXT("[SimpleNetworkManager] Connected to server %s:%d"), *ServerAddress, Port);
    }
    else
    {
        UE_LOG(LogSimpleNetwork, Error, TEXT("[SimpleNetworkManager] Failed to connect to server"));
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

    PingElapsedTime += DeltaTime;
    if (PingElapsedTime >= 1.0f)  // 1초마다 Ping 보냄
    {
        FPingPacket PingPacket;
        PingPacket.Header.PacketType = EPacketType::PING;
        PingPacket.Header.PacketSize = sizeof(FPingPacket);
        PingPacket.ClientId = LocalClientId;
        PingPacket.PingTime = FPlatformTime::Seconds();  // 현재 시간 기록

        SendPingPacket(PingPacket);

        PingElapsedTime = 0.0f; // 타이머 리셋
    }


    uint32 PendingDataSize = 0;
    if (Socket->HasPendingData(PendingDataSize))
    {
        //UE_LOG(LogTemp, Warning, TEXT("[NetworkManager] Pending Data Size: %d"), PendingDataSize);

        uint8 RecvBuffer[4096];
        int32 BytesRead = 0;

        if (Socket->Recv(RecvBuffer, sizeof(RecvBuffer), BytesRead))
        {
            //UE_LOG(LogTemp, Warning, TEXT("[NetworkManager] Recv Success - Bytes Read: %d"), BytesRead);
            HandleIncomingPacket(RecvBuffer, BytesRead);
        }
        //else
        //    UE_LOG(LogTemp, Error, TEXT("[NetworkManager] Recv Failed"));
    }
}

void USimpleNetworkManager::HandleIncomingPacket(const uint8* Data, int32 Size)
{
    if (!Replicator)
    {
        UE_LOG(LogSimpleNetwork, Warning, TEXT("[SimpleNetworkManager] Replicator is not set"));
        return;
    }

    int32 Offset = 0;

    while (Offset < Size)
    {
        // 남은 데이터가 최소 헤더 크기보다 작으면 잘못된 패킷
        if (Size - Offset < sizeof(FPacketHeader))
        {
            UE_LOG(LogSimpleNetwork, Warning, TEXT("[SimpleNetworkManager] 데이터 부족 - 헤더조차 읽을 수 없음"));
            break;
        }

        const FPacketHeader* Header = reinterpret_cast<const FPacketHeader*>(Data + Offset);

        // 패킷 전체 크기 검사
        if (Size - Offset < Header->PacketSize)
        {
            UE_LOG(LogSimpleNetwork, Warning, TEXT("[SimpleNetworkManager] 데이터 부족 - 패킷 전체 읽기 실패 (PacketSize=%d, 남은=%d)"), Header->PacketSize, Size - Offset);
            break;
        }

        switch (Header->PacketType)
        {
        case EPacketType::CLIENT_ID:
        {
            const FClientIdPacket* ClientIdPacket = reinterpret_cast<const FClientIdPacket*>(Data + Offset);
            Replicator->HandleClientIdPacket(ClientIdPacket);
            LocalClientId = ClientIdPacket->ClientId;
            UE_LOG(LogSimpleNetwork, Display, TEXT("[SimpleNetworkManager] Client ID assigned: %d"), ClientIdPacket->ClientId);
        }
        break;
        case EPacketType::DISCONNECT:
        {
            const FDisconnectPacket* DisconnectPacket = reinterpret_cast<const FDisconnectPacket*>(Data + Offset);
            Replicator->HandleDisconnectPacket(DisconnectPacket);
            UE_LOG(LogSimpleNetwork, Display, TEXT("[SimpleNetworkManager] Player disconnected - Client ID: %d"), DisconnectPacket->ClientId);
        }
        break;
        case EPacketType::PONG:
        {
            const FPongPacket* PongPacket = reinterpret_cast<const FPongPacket*>(Data + Offset);
            float RoundTripTime = FPlatformTime::Seconds() - PongPacket->PingTime;
            UE_LOG(LogSimpleNetwork, Display, TEXT("[SimpleNetworkManager] Pong received, RTT: %f seconds - Client ID: %d"), RoundTripTime, PongPacket->ClientId);
        }
        break;
        case EPacketType::PLAYER_INIT_INFO:
        {
            const FPositionPacket* InitPacket = reinterpret_cast<const FPositionPacket*>(Data + Offset);
            Replicator->HandleInitialPositionPacket(InitPacket);
            UE_LOG(LogSimpleNetwork, Display, TEXT("[SimpleNetworkManager] Player Initial Position Received"));
        }
        break;
        case EPacketType::PLAYER_POSITION_INFO:
        {
            const FPositionPacket* PositionPacket = reinterpret_cast<const FPositionPacket*>(Data + Offset);
            Replicator->HandlePositionPacket(PositionPacket);
            UE_LOG(LogSimpleNetwork, Display, TEXT("[SimpleNetworkManager] Player Position Update"));
        }
        break;
        default:
        {
            UE_LOG(LogSimpleNetwork, Warning, TEXT("[SimpleNetworkManager] Unknown packet type received: %d"), (int32)Header->PacketType);
        }
        break;
        }

        Offset += Header->PacketSize;
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