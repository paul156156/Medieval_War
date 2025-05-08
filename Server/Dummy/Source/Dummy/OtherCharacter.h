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

    // 상태 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void UpdateAnimationState(EPlayerState NewState);

    // 위치 및 회전 업데이트
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation, const FVector& NewVelocity);

    // 현재 상태
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EPlayerState CurrentState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;

private:
    // 보간을 위한 변수
    FVector TargetPosition;
	FRotator TargetRotation;
    FVector ReplicatedVelocity = { 0,0,0 };

    bool bInterpEnabled = false;
    float PositionInterpolationTime;
};