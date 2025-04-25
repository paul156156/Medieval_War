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

    // 현재 위치와 목표 위치 간의 거리 계산
    float Distance = FVector::Dist(GetActorLocation(), TargetPosition);

    // 거리가 멀면 보간 가속
    if (Distance > 300.0f)
    {
        // 더 빠른 보간
        PosAlpha = FMath::Clamp(PositionInterpolationTime / 0.05f, 0.0f, 1.0f);
    }

    //FVector NewPos = FMath::Lerp(GetActorLocation(), TargetPosition, PosAlpha);
    //FRotator NewRot = FMath::Lerp(GetActorRotation(), TargetRotation, RotAlpha);

    // 새 위치와 회전 계산 및 적용
    FVector OldLocation = GetActorLocation();
    FVector NewPos = FMath::Lerp(OldLocation, TargetPosition, PosAlpha);
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
        //OnAnimationStateChanged(NewState);

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
            if (AttackMontage)
            {
                UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
                if (AnimInstance)
                {
                    AnimInstance->Montage_Play(AttackMontage, 1.0f);
                }
            }
        }
    }

}

void AOtherCharacter::UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation, const FVector& NewVelocity)
{
    TargetPosition = NewPosition;
    TargetRotation = NewRotation;
    PositionInterpolationTime = 0.0f;
    RotationInterpolationTime = 0.0f;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->Velocity = NewVelocity;
    }

            UE_LOG(LogTemp, Display, TEXT("[UpdateTransform] %s - Pos: (%.1f, %.1f, %.1f), Vel: (%.1f, %.1f, %.1f)"),
            *GetName(),                     // 캐릭터 이름 (혹은 ID 변수 있으면 그걸로!)
            NewPosition.X, NewPosition.Y, NewPosition.Z,
            NewVelocity.X, NewVelocity.Y, NewVelocity.Z
        );
}