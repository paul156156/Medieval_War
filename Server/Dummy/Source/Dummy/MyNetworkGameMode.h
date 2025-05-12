// MyNetworkGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
#include "SimpleNetworking/Public/SimpleNetworkReplicator.h"
#include "MyNetworkGameMode.generated.h"

class USimpleNetworkManager;
class UsimpleNetworkReplicator;
class AMyCharacter;
class AOtherCharacter;

UCLASS()
class DUMMY_API AMyNetworkGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyNetworkGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    USimpleNetworkManager* NetworkManager;

    UPROPERTY()
    class USimpleNetworkReplicator* NetworkReplicator;
    
    UPROPERTY()
    AMyCharacter* DeferredCharacter;

    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    TSubclassOf<AOtherCharacter> OtherPlayerCharacterClass;

    UPROPERTY()
    TMap<int32, AOtherCharacter*> OtherPlayers;

    int32 LocalClientId;

    UPROPERTY(EditAnywhere, Category = "Networking")
    FString ServerIP = TEXT("127.0.0.1");

    UPROPERTY(EditAnywhere, Category = "Networking")
    int32 ServerPort = 9000;

    UPROPERTY(EditAnywhere, Category = "Networking")
    bool bAutoConnect = true;

    FTimerHandle TickReceiveHandle;

    USimpleNetworkManager* GetNetworkManager() const { return NetworkManager; }

protected:
    UFUNCTION()
    void ConnectToServer();

    UFUNCTION()
    void DisconnectFromServer();


    UFUNCTION()
    void HandleClientIdAssigned(int32 ClientId);

    UFUNCTION()
	void HandlePlayerDisconnected(int32 ClientId);

    UFUNCTION()
    void HandlePlayerPositionUpdated(int32 ClientId, FVector Position, FRotator Rotation, FVector Velocity, EPlayerState State, float Timestamp);

    UFUNCTION()
	void HandleInitialPositionReceived(int32 ClientId, FVector Position, FRotator Rotation, FVector Velocity, EPlayerState State);

    AOtherCharacter* SpawnOtherPlayerCharacter(int32 ClientId, const FVector& SpawnPosition, const FRotator& SpawnRotation, const FVector& SpawnVelocity);
};