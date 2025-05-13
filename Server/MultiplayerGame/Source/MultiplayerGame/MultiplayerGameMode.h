// MultiplayerGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacketTypes.h"
#include "MultiplayerGameMode.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AMultiplayerGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMultiplayerGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();

    UFUNCTION(BlueprintCallable, Category = "Game")
    class ACharacter* SpawnPlayerCharacter(int32 PlayerId, bool bIsLocalPlayer);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void DestroyPlayerCharacter(int32 PlayerId);

    UFUNCTION(BlueprintPure, Category = "Game")
    class ACharacter* GetLocalPlayerCharacter() const;

    UFUNCTION()
    void OnConnectionStatusChanged(bool bIsConnected);

    UFUNCTION()
    void OnPlayerJoined(int32 PlayerId);

    UFUNCTION()
    void OnPlayerLeft(int32 PlayerId);

    UFUNCTION()
    void OnPlayerPositionUpdated(int32 PlayerId, FTransform NewTransform);

    UFUNCTION()
    void OnPlayerStateChanged(int32 PlayerId, EPlayerState NewState);

    UFUNCTION()
    void OnConnectionError();

protected:
    void UpdatePlayerInput();

private:
    UPROPERTY()
    class UNetworkManager* NetworkManager;

    UPROPERTY()
    TMap<int32, class ACharacter*> PlayerCharacters;

    // 캐릭터 클래스 분기
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<class ACharacter> MyPlayerCharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<class ACharacter> OtherPlayerCharacterClass;

    // 네트워크 설정
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    FString DefaultServerIp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    int32 DefaultServerPort;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    bool bAutoConnect;

    FTimerHandle InputUpdateTimerHandle;

    float LastForwardInput;
    float LastRightInput;
    float LastYawRotation;
    bool bLastJumpPressed;
    bool bLastAttackPressed;
};
