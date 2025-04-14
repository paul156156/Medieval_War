#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dummy_clientGameMode.generated.h"

class UNetworkManager;
class UUserWidget;

UCLASS(minimalapi)
class Adummy_clientGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    Adummy_clientGameMode();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // ��Ʈ��ũ �Ŵ��� ������
    UFUNCTION(BlueprintCallable, Category = "Networking")
    UNetworkManager* GetNetworkManager() const;

    // ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void ConnectToServer();

    // ���� ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // ���� ���� ���� �̺�Ʈ
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnected();

    // ���� ���� ���� �̺�Ʈ
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnectionFailed();

    // ���� ���� ���� �̺�Ʈ
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerDisconnected();

protected:
    // ��Ʈ��ũ �Ŵ��� �ν��Ͻ�
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // ���� IP �ּ�
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    FString ServerIP;

    // ���� ��Ʈ
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    int32 ServerPort;

    // �ڵ� ���� ����
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    bool bAutoConnect;

    // ���� ���� �� �ڵ� �翬�� ����
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    bool bAutoReconnect;

    // �翬�� ���� (��)
    UPROPERTY(EditDefaultsOnly, Category = "Networking", meta = (EditCondition = "bAutoReconnect"))
    float ReconnectInterval;

    // ���� ���� UI ���� Ŭ����
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ConnectionStatusWidgetClass;

    // ���� ���� UI ���� �ν��Ͻ�
    UPROPERTY()
    UUserWidget* ConnectionStatusWidget;
};