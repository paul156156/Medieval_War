#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "dummy_clientCharacter.generated.h"

class UNetworkManager;

UCLASS(config = Game)
class Adummy_clientCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    Adummy_clientCharacter();

protected:
    /** ī�޶� �� ������Ʈ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* CameraBoom;

    /** �ȷο� ī�޶� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FollowCamera;

    /** ��Ʈ��ũ �Ŵ��� ���۷��� */
    UPROPERTY()
    UNetworkManager* NetworkManager;

    /** ��Ʈ��ũ ������Ʈ Ȱ��ȭ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Networking)
    bool bEnableNetworkUpdates;

    /** ������ ��ġ ���� �ð� */
    float LastPositionSentTime;

    /** ��ġ ���� ���� (��) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Networking)
    float PositionUpdateInterval;

    /** �ٸ� �÷��̾� ��ġ ���� ó�� */
    UFUNCTION()
    void OnPositionUpdateReceived(const FVector& NewPosition);

    ///// �⺻ �Է� ���� �Լ� /////
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);
    void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
    void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
    /** ���̽��Ϸ���Ʈ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** ���̽����/�ٿ��Ʈ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;

protected:
    // ĳ���� �ʱ�ȭ
    virtual void BeginPlay() override;

    // �� ������ ȣ��
    virtual void Tick(float DeltaTime) override;

    // ��Ʈ��ũ �Ŵ��� �ʱ�ȭ
    void InitializeNetworkManager();

    // ������ ��ġ ����
    void SendPositionToServer();

public:
    // ���� �̺�Ʈ (�������̵�)
    virtual void Jump() override;
    virtual void StopJumping() override;

    // �ٸ� �÷��̾� ĳ���� ���� (�����κ��� ���� ��ġ ������)
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void SpawnOtherPlayerCharacter(const FVector& Position);
};