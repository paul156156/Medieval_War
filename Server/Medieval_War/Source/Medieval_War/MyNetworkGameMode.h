// MyNetworkGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
#include "MyNetworkGameMode.generated.h"

class USimpleNetworkManager;
class AMyCharacter;
class AOtherCharacter;

UCLASS()
class MEDIEVAL_WAR_API AMyNetworkGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyNetworkGameMode();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // �÷��̾� ���� ���� ó��
    UFUNCTION()
    void OnCharacterStateChanged(EPlayerState NewState, const FVector& Position, const FRotator& Rotation);

    // ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void ConnectToServer();

    // ���� ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // ��Ʈ��ũ �̺�Ʈ (�������Ʈ���� �������̵� ����)
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnected();

    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerDisconnected();

    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnectionFailed();

protected:
    // ��Ʈ��ũ �Ŵ���
    UPROPERTY()
    USimpleNetworkManager* NetworkManager;

    // ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    FString ServerIP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    int32 ServerPort;

    // �ڵ� ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    bool bAutoConnect;

    // �ٸ� �÷��̾� ĳ���� Ŭ����
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    TSubclassOf<AOtherCharacter> OtherPlayerCharacterClass;

    // ���� Ŭ���̾�Ʈ ID
    int32 LocalClientId;

    // �ٸ� �÷��̾� ĳ���� ��
    //TMap<int32, AOtherCharacter*> OtherPlayers;

    // ��Ʈ��ũ �̺�Ʈ �ڵ鷯
    UFUNCTION()
    void OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, EPlayerState State);

    UFUNCTION()
    void OnClientIdReceived(int32 ClientId);

    UFUNCTION()
    void OnConnectionStatusChanged(bool IsConnected);

    // �ٸ� �÷��̾� ����/���� �Լ�
    //AOtherCharacter* SpawnOtherPlayerCharacter(int32 ClientId, const FVector& Position);
    //void RemoveOtherPlayerCharacter(int32 ClientId);
    //void RemoveAllOtherPlayers();
};