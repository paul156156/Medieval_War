// MyGameModeBase.h
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

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();

    // ��Ʈ��ũ �÷��̾� ����
    UFUNCTION(BlueprintCallable, Category = "Network")
    AMyCharacter* GetPlayerCharacter(int32 PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Network")
    TArray<AMyCharacter*> GetAllNetworkPlayers();

    UFUNCTION(BlueprintCallable, Category = "Network")
    int32 GetLocalPlayerId();

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool IsLocalPlayer(int32 PlayerId);

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // ��Ʈ��ũ �̺�Ʈ ó��
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    FString DefaultServerIp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    int32 DefaultServerPort;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    bool bAutoConnect;

    // �Է� ������Ʈ�� Ÿ�̸�
    FTimerHandle InputUpdateTimerHandle;

    // ���� �Է°� ����� ������ (MyCharacter.h�� ������� ����)
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
    float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;

    // ��Ʈ��ũ �Ŵ��� ����
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // ������ ��Ʈ��ũ �÷��̾��
    UPROPERTY()
    TMap<int32, AMyCharacter*> NetworkPlayers;

    // ���� �÷��̾� ����
    UPROPERTY()
    AMyCharacter* LocalPlayer;

    // �÷��̾� ĳ���� Ŭ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player")
    TSubclassOf<AMyCharacter> NetworkPlayerClass;

    // ���� ��ġ��
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
    TArray<FTransform> SpawnPoints;

private:
    // ��Ʈ��ũ �÷��̾� ����
    AMyCharacter* CreateNetworkPlayer(int32 PlayerId);

    // ��Ʈ��ũ �÷��̾� ����
    void RemoveNetworkPlayer(int32 PlayerId);

    // ���� �÷��̾� ����
    void SetupLocalPlayer();

    // ���� ��ġ ��������
    FTransform GetSpawnTransform(int32 PlayerId);

    // �⺻ ���� ��ġ ����
    void SetupDefaultSpawnPoints();

    // �Է� ������Ʈ �Լ� ���� �߰�
    void UpdatePlayerInput();
};