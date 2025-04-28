#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NetworkTypes.h"
#include "SimpleNetworkManager.generated.h"

class USimpleNetworkReplicator;

UCLASS()
class SIMPLENETWORKING_API USimpleNetworkManager : public UObject
{
    GENERATED_BODY()

public:
    USimpleNetworkManager();

    bool ConnectToServer(const FString& ServerAddress, int32 Port);
    bool IsConnected() const;
	bool Disconnect();
    void SendPingPacket(const FPingPacket& Packet);
    void SendInputPacket(const FInputPacket& Packet);
    void TickReceive(float DeltaTime);

    void SetReplicator(USimpleNetworkReplicator* InReplicator);

    int32 GetLocalClientId() const { return LocalClientId; }

private:
    FSocket* Socket;
    ISocketSubsystem* SocketSubsystem;
    USimpleNetworkReplicator* Replicator;
    bool bConnected;
	int32 LocalClientId = -1;

    float PingElapsedTime = 0.0f;

    void HandleIncomingPacket(const uint8* Data, int32 Size);
    bool SendRaw(const uint8* Data, int32 Size);
};
