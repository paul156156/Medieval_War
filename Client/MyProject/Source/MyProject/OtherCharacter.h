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

    // 상태 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void UpdateAnimationState(EPlayerState NewState);

    // 위치 및 회전 업데이트
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation);

    // 현재 상태
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EPlayerState CurrentState;

    // 애니메이션 상태 변경 이벤트 (블루프린트에서 처리)
    UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
    void OnAnimationStateChanged(EPlayerState NewState);

private:
    // 보간을 위한 변수
    FVector TargetPosition;
    FRotator TargetRotation;
    float PositionInterpolationTime;
    float RotationInterpolationTime;
};