// MultiplayerCharacterAnimInstance.h
// �÷��̾� ĳ������ �ִϸ��̼� �ν��Ͻ� Ŭ����

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PacketTypes.h"
#include "MultiplayerCharacterAnimInstance.generated.h"

/**
 * �÷��̾� ĳ���͸� ���� �ִϸ��̼� �ν��Ͻ�
 */
UCLASS()
class MULTIPLAYERGAME_API UMultiplayerCharacterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UMultiplayerCharacterAnimInstance();

    // �ִϸ��̼� �ʱ�ȭ
    virtual void NativeInitializeAnimation() override;

    // �� ������ �ִϸ��̼� ������Ʈ
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    // �÷��̾� ���� ����
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetPlayerState(EPlayerState NewState);

private:
    // ���� ĳ����
    UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
    class AMultiplayerCharacter* OwnerCharacter;

    // ĳ���� �����Ʈ ������Ʈ
    UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
    class UCharacterMovementComponent* MovementComponent;

    // �ִϸ��̼� ������
    UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    bool bIsInAir;

    UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    bool bIsAccelerating;

    UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float GroundSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float MovementDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    EPlayerState CurrentPlayerState;

    UPROPERTY(BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float LastStateChangeTime;
};