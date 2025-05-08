// OtherCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
#include "OtherCharacter.generated.h"

UCLASS()
class DUMMY_API AOtherCharacter : public ACharacter
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
    void UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation, const FVector& NewVelocity);

    // ���� ����
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EPlayerState CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;

private:
    // ������ ���� ����
    FVector TargetPosition;
	FRotator TargetRotation;
    FVector ReplicatedVelocity = { 0,0,0 };

    bool bInterpEnabled = false;
    float PositionInterpolationTime;
};