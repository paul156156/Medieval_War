// MyGameModeBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacketTypes.h"
#include "NetworkManager.h"
#include "MyCharacter.h"
#include "OtherCharacter.h"
#include "MyGameModeBase.generated.h"

UCLASS()
class MW_API AMyGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyGameModeBase();

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();

    // 네트워크 플레이어 관리
    UFUNCTION(BlueprintCallable, Category = "Network")
    AMyCharacter* GetPlayerCharacter(int32 PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Network")
    TArray<AMyCharacter*> GetAllPlayers();

    UFUNCTION(BlueprintCallable, Category = "Network")
    int32 GetLocalPlayerId();

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool IsLocalPlayer(int32 PlayerId);

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // 네트워크 이벤트 처리
    UFUNCTION()
    void OnPlayerJoined(int32 PlayerId);

    UFUNCTION()
    void OnPlayerLeft(int32 PlayerId);

    UFUNCTION()
    void OnPlayerPositionUpdated(int32 PlayerId, FTransform NewTransform, FVector Velocity);

    UFUNCTION()
    void OnPlayerStateChanged(int32 PlayerId, EPlayerState NewState);

    UFUNCTION()
    void OnConnectionStatusChanged(bool bIsConnected);

    UFUNCTION()
    void OnConnectionError();

    // 네트워크 매니저 참조
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // 생성된 네트워크 플레이어들
    UPROPERTY()
    TMap<int32, AMyCharacter*> Players;

    // 로컬 플레이어 참조
    UPROPERTY()
    AMyCharacter* LocalPlayer;

    // 플레이어 캐릭터 클래스들
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
    TSubclassOf<AMyCharacter> LocalPlayerClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
    TSubclassOf<AOtherCharacter> RemotePlayerClass;  // 원격 플레이어용 클래스

    //// 스폰 위치들
    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    //TArray<FTransform> SpawnPoints;

    // 네트워크 설정들
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    FString DefaultServerIp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    int32 DefaultServerPort;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    bool bAutoConnect;

    // 입력 업데이트용 타이머
    FTimerHandle InputUpdateTimerHandle;

    // 이전 입력값 저장용 변수들
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
    float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;
	bool bPreviousDefensePressed = false;

private:
    // 플레이어 생성
    AMyCharacter* CreateLocalPlayer(int32 PlayerId);
    AOtherCharacter* CreateRemotePlayer(int32 PlayerId);

    //플레이어 제거
    void RemovePlayer(int32 PlayerId);

    // 로컬 플레이어 설정
    void SetupLocalPlayer();

    // 스폰 위치 가져오기
    FTransform GetSpawnTransform(int32 PlayerId);

    //// 기본 스폰 위치 설정
    //void SetupDefaultSpawnPoints();

    //// 입력 업데이트 함수 선언 추가
    //void UpdatePlayerInput();
};