// OtherCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
#include "OtherCharacter.generated.h"

UCLASS()
class MEDIEVAL_WAR_API AOtherCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AOtherCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ���� ������Ʈ �Լ�
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void UpdateAnimationState(EPlayerState NewState);

    // ��ġ �� ȸ�� ������Ʈ
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation);

    // ���� ����
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EPlayerState CurrentState;

    // �ִϸ��̼� ���� ���� �̺�Ʈ (�������Ʈ���� ó��)
    UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
    void OnAnimationStateChanged(EPlayerState NewState);

private:
    // ������ ���� ����
    FVector TargetPosition;
    FRotator TargetRotation;
    float PositionInterpolationTime;
    float RotationInterpolationTime;
};