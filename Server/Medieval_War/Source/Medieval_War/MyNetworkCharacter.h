#pragma once

#include "CoreMinimal.h"
#include "SimpleNetworking/Public/SimpleNetworkCharacter.h"
#include "MyNetworkCharacter.generated.h"

/**
 * ��Ʈ��ũ ����� �߰��� ĳ���� Ŭ����
 */
class UNetworkPlayerComponent;

UCLASS()
class MEDIEVAL_WAR_API AMyNetworkCharacter : public ASimpleNetworkCharacter
{
    GENERATED_BODY()

public:
    // ������
    AMyNetworkCharacter();

    // �⺻ �޼��� �������̵�
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaTime) override;

    // ��Ʈ��ũ ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Networking")
    class UNetworkPlayerComponent* NetworkComponent;

    // ���� ����
    UFUNCTION(BlueprintCallable, Category = "Networking")
    bool ConnectToServer();

    // ���� ���� ����
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // ��Ʈ��ũ �̺�Ʈ �Լ� �������̵�
    virtual void OnNetworkConnected() override;
    virtual void OnNetworkDisconnected() override;

	// ��ġ ���� �Լ�
	void SendPositionToServer();

    // ������ ���� ����
    bool LastJumpState;
};