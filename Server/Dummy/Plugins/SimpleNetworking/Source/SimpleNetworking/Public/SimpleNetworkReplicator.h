#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NetworkTypes.h"
#include "SimpleNetworkReplicator.generated.h"

// 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnClientIdAssigned,
    int32, ClientId
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnPlayerDisconnected,
    int32, ClientId
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(
    FOnMyInitialPositionReceived,
    int32, ClientId,
    FVector, Position,
	FRotator, Rotation,
    FVector, Velocity,
    EPlayerState, State
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(
    FOnPlayerPositionUpdated,
    int32, ClientId,
    FVector, NewPosition,
	FRotator, NewRotation,
    FVector, NewVelocity,
    EPlayerState, State,
    float, Timestamp
);

UCLASS()
class SIMPLENETWORKING_API USimpleNetworkReplicator : public UObject
{
    GENERATED_BODY()

public:
    USimpleNetworkReplicator();

    void HandleClientIdPacket(const FClientIdPacket* Packet);

	void HandleDisconnectPacket(const FDisconnectPacket* Packet);

	void HandleInitialPositionPacket(const FPositionPacket* Packet);

    void HandlePositionPacket(const FPositionPacket* Packet);

    void InitializeLocalClientId(int32 InClientId);


    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnClientIdAssigned OnClientIdAssigned;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPlayerDisconnected OnPlayerDisconnected;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPlayerPositionUpdated OnPlayerPositionUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnMyInitialPositionReceived OnMyInitialPositionReceived;

private:
    int32 LocalClientId;
};
