// OtherCharacter.cpp
#include "OtherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AOtherCharacter::AOtherCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // 기본 상태 설정
    CurrentState = EPlayerState::IDLE;

    // AI 컨트롤러 비활성화
    AutoPossessAI = EAutoPossessAI::Disabled;

    // 컴포넌트 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 캐릭터 무브먼트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AOtherCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 디버그 로그
    UE_LOG(LogTemp, Display, TEXT("OtherCharacter spawned at %s"), *GetActorLocation().ToString());
}

void AOtherCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 위치와 회전 보간
    PositionInterpolationTime += DeltaTime;
    RotationInterpolationTime += DeltaTime;

    float PosAlpha = FMath::Clamp(PositionInterpolationTime / 0.1f, 0.0f, 1.0f);
    float RotAlpha = FMath::Clamp(RotationInterpolationTime / 0.1f, 0.0f, 1.0f);

    FVector NewPos = FMath::Lerp(GetActorLocation(), TargetPosition, PosAlpha);
    FRotator NewRot = FMath::Lerp(GetActorRotation(), TargetRotation, RotAlpha);

    SetActorLocation(NewPos);
    SetActorRotation(NewRot);
}

void AOtherCharacter::UpdateAnimationState(EPlayerState NewState)
{
    if (CurrentState != NewState)
    {
        CurrentState = NewState;

        // 블루프린트에서 처리할 이벤트 호출
        OnAnimationStateChanged(NewState);

        // 디버그 로그
        UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

        // 애니메이션 상태에 따른 추가 처리
        if (NewState == EPlayerState::JUMPING)
        {
            // 점프 상태에서는 캐릭터의 점프 함수 호출
            Jump();
        }
        else if (NewState == EPlayerState::ATTACKING)
        {
            // 공격 상태는 블루프린트에서 처리하도록 설계
        }
    }
}

void AOtherCharacter::UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation)
{
    TargetPosition = NewPosition;
    TargetRotation = NewRotation;
    PositionInterpolationTime = 0.0f;
    RotationInterpolationTime = 0.0f;
}