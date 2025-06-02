// MyGameModeBase.h - 단순화된 구조
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

    // ===== 네트워크 연결 관리 =====
    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();

    // ===== 플레이어 관리 =====
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

    // ===== 네트워크 이벤트 핸들러 =====
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

    // ===== 플레이어 생성/제거 함수 =====
    AMyCharacter* CreatePlayerCharacter(int32 PlayerId);
    void RemovePlayer(int32 PlayerId);
    void RemoveExistingLocalPlayer();

    // ===== 스폰 관련 함수 =====
    FTransform GetSpawnTransform(int32 PlayerId);

    // ===== 네트워크 매니저 =====
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // ===== 플레이어 관리 =====
    UPROPERTY()
    TMap<int32, AMyCharacter*> Players;

    // ===== 플레이어 클래스 설정 =====
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Classes")
    TSubclassOf<AMyCharacter> DefaultPlayerClass;

    // ===== 네트워크 설정 =====
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network Settings")
    FString DefaultServerIp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network Settings")
    int32 DefaultServerPort;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network Settings")
    bool bAutoConnect;

    // ===== 스폰 설정 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    float PlayerSpawnRadius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    bool bUseRandomSpawnRotation = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    FVector DefaultSpawnLocation = FVector(0, 0, 100);

    // ===== 게임 규칙 설정 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 MaxPlayers = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    bool bAllowLateJoin = true;

    // ===== 게임 상태 =====
    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    bool bGameStarted = false;

    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    float GameStartTime = 0.0f;

    // ===== 타이머 핸들 =====
    FTimerHandle NetworkUpdateTimerHandle;

public:
    // ===== 디버그 함수들 =====
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void PrintAllPlayersInfo();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetDebugModeForAllPlayers(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    FString GetGameModeStatus();

    // ===== 게임 이벤트 (블루프린트에서 구현 가능) =====
    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnGameStarted();

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnGameEnded();

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnPlayerConnected(int32 PlayerId);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
    void OnPlayerDisconnected(int32 PlayerId);

private:
    // ===== 내부 상태 변수 =====
    bool bIsInitialized = false;
    float LastPlayerUpdateTime = 0.0f;

    // ===== 헬퍼 함수들 =====
    void InitializeGameMode();
    void CleanupGameMode();
    bool ValidatePlayerSpawn(int32 PlayerId, const FTransform& SpawnTransform);
    void LogPlayerAction(int32 PlayerId, const FString& Action);
};