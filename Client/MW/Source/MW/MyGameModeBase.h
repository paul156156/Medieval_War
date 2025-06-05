// MyGameModeBase.h - �ܼ�ȭ�� ����
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacketTypes.h"
#include "NetworkManager.h"
#include "MyCharacter.h"
#include "MyGameModeBase.generated.h"

UCLASS()
class MW_API AMyGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyGameModeBase();

    // ===== ��Ʈ��ũ ���� ���� =====
    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();

    // ===== �÷��̾� ���� =====
    UFUNCTION(BlueprintCallable, Category = "Player Management")
    AMyCharacter* GetPlayerCharacter(int32 PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Player Management")
    TArray<AMyCharacter*> GetAllPlayers();

    UFUNCTION(BlueprintCallable, Category = "Player Management")
    int32 GetLocalPlayerId();

    UFUNCTION(BlueprintCallable, Category = "Player Management")
    bool IsLocalPlayer(int32 PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Player Management")
    int32 GetPlayerCount() const { return Players.Num(); }

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // ===== ��Ʈ��ũ �̺�Ʈ �ڵ鷯 =====
    UFUNCTION()
    void OnPlayerJoined(int32 PlayerId);

    UFUNCTION()
    void OnPlayerLeft(int32 PlayerId);

    UFUNCTION()
    void OnPlayerUpdated(int32 PlayerId, FTransform NewTransform, FVector Velocity, EPlayerState State, EPlayerAction Action);

    UFUNCTION()
    void OnConnectionStatusChanged(bool bIsConnected);

    UFUNCTION()
    void OnConnectionError();

    // ===== �÷��̾� ����/���� �Լ� =====
    AMyCharacter* CreatePlayerCharacter(int32 PlayerId);
    void RemovePlayer(int32 PlayerId);
    void RemoveExistingLocalPlayer();

    // ===== ���� ���� �Լ� =====
    FTransform GetSpawnTransform(int32 PlayerId);

    // ===== ��Ʈ��ũ �Ŵ��� =====
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // ===== �÷��̾� ���� =====
    UPROPERTY()
    TMap<int32, AMyCharacter*> Players;

    // ===== �÷��̾� Ŭ���� ���� =====
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Classes")
    TSubclassOf<AMyCharacter> DefaultPlayerClass;

    // ===== ��Ʈ��ũ ���� =====
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network Settings")
    FString DefaultServerIp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network Settings")
    int32 DefaultServerPort;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network Settings")
    bool bAutoConnect;

    // ===== ���� ���� =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    float PlayerSpawnRadius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    bool bUseRandomSpawnRotation = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    FVector DefaultSpawnLocation = FVector(0, 0, 100);

    // ===== ���� ��Ģ ���� =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 MaxPlayers = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    bool bAllowLateJoin = true;

    // ===== ���� ���� =====
    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    bool bGameStarted = false;

    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    float GameStartTime = 0.0f;

    // ===== Ÿ�̸� �ڵ� =====
    FTimerHandle NetworkUpdateTimerHandle;

public:
    // ===== ����� �Լ��� =====
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void PrintAllPlayersInfo();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetDebugModeForAllPlayers(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    FString GetGameModeStatus();

    // ===== ���� �̺�Ʈ (�������Ʈ���� ���� ����) =====
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnGameStarted();

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnGameEnded();

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnPlayerConnected(int32 PlayerId);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnPlayerDisconnected(int32 PlayerId);

private:
    // ===== ���� ���� ���� =====
    bool bIsInitialized = false;
    float LastPlayerUpdateTime = 0.0f;

    // ===== ���� �Լ��� =====
    void InitializeGameMode();
    void CleanupGameMode();
    bool ValidatePlayerSpawn(int32 PlayerId, const FTransform& SpawnTransform);
    void LogPlayerAction(int32 PlayerId, const FString& Action);
};