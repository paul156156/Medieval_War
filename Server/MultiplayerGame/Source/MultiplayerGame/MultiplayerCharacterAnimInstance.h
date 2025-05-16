// MultiplayerCharacterAnimInstance.h
// 플레이어 캐릭터의 애니메이션 인스턴스 클래스

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PacketTypes.h"
#include "MultiplayerCharacterAnimInstance.generated.h"

/**
 * 플레이어 캐릭터를 위한 애니메이션 인스턴스
 */
UCLASS()
class MULTIPLAYERGAME_API UMultiplayerCharacterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UMultiplayerCharacterAnimInstance();

    // 애니메이션 초기화
    virtual void NativeInitializeAnimation() override;

    // 매 프레임 애니메이션 업데이트
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    // 플레이어 상태 설정
    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetPlayerState(EPlayerState NewState);

private:
    // 소유 캐릭터
    UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
    class AMultiplayerCharacter* OwnerCharacter;

    // 캐릭터 무브먼트 컴포넌트
    UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
    class UCharacterMovementComponent* MovementComponent;

    // 애니메이션 변수들
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