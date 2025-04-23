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

    //// WALKING 상태일 때 계속 velocity 업데이트
    //if (CurrentState == EPlayerState::WALKING ||
    //    (CurrentState == EPlayerState::ATTACKING && GetCharacterMovement()->Velocity.SizeSquared() > 0))
    //{
    //    if (GetCharacterMovement())
    //    {
    //        FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();

    //        // 거리가 충분히 가깝다면 속도 감소
    //        if (Distance < 100.0f)
    //        {
    //            float SpeedFactor = FMath::Clamp(Distance / 100.0f, 0.0f, 1.0f);
    //            GetCharacterMovement()->Velocity = Direction * 500.0f * SpeedFactor;

    //            // 매우 가까워지면 IDLE 상태로 전환
    //            if (Distance < 10.0f && CurrentState == EPlayerState::WALKING)
    //            {
    //                GetCharacterMovement()->Velocity = FVector::ZeroVector;

    //                // 공격 중이 아니면 IDLE로 변경
    //                if (CurrentState != EPlayerState::ATTACKING)
    //                {
    //                    CurrentState = EPlayerState::IDLE;
    //                }
    //            }
    //        }
    //        else
    //        {
    //            GetCharacterMovement()->Velocity = Direction * 500.0f;
    //        }
    //    }
    //}

    //// JUMPING 상태인 경우 Z 속도만 변경하고 XY 방향은 유지
    //else if (CurrentState == EPlayerState::JUMPING && GetCharacterMovement())
    //{
    //    FVector CurrentVelocity = GetCharacterMovement()->Velocity;
    //    FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();

    //    // XY 평면상의 방향만 설정 (Z 속도는 점프 로직이 처리)
    //    FVector HorizontalDirection = FVector(Direction.X, Direction.Y, 0).GetSafeNormal();

    //    if (!HorizontalDirection.IsNearlyZero())
    //    {
    //        // Z 속도는 유지하고 XY 속도만 업데이트
    //        FVector NewVelocity = HorizontalDirection * 500.0f;
    //        NewVelocity.Z = CurrentVelocity.Z;
    //        GetCharacterMovement()->Velocity = NewVelocity;
    //    }
    //}
}

void AOtherCharacter::UpdateAnimationState(EPlayerState NewState)
{
    //if (CurrentState != NewState)
    //{
    //    CurrentState = NewState;

    //    // 블루프린트에서 처리할 이벤트 호출
    //    OnAnimationStateChanged(NewState);

    //    // 디버그 로그
    //    UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

    //    // 애니메이션 상태에 따른 추가 처리
    //    if (NewState == EPlayerState::JUMPING)
    //    {
    //        // 점프 상태에서는 캐릭터의 점프 함수 호출
    //        Jump();
    //    }
    //    else if (NewState == EPlayerState::ATTACKING)
    //    {
    //        if (AttackMontage)
    //        {
    //            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    //            if (AnimInstance)
    //            {
    //                AnimInstance->Montage_Play(AttackMontage, 1.0f);
    //            }
    //        }
    //    }
    //}

    // 상태 변경 시에만 애니메이션 업데이트
    //if (CurrentState != NewState)
    //{
    //    CurrentState = NewState;

    //    // 블루프린트 이벤트 호출
    //    //OnAnimationStateChanged(NewState);

    //    // 로그
    //    UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

    //    // 애니메이션 상태에 따른 추가 처리
    //    if (NewState == EPlayerState::JUMPING)
    //    {
    //        // 점프
    //        Jump();
    //    }
    //    else if (NewState == EPlayerState::ATTACKING)
    //    {
    //        // 공격 애니메이션 재생
    //        if (AttackMontage)
    //        {
    //            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    //            if (AnimInstance)
    //            {
    //                AnimInstance->Montage_Play(AttackMontage, 1.0f);
    //            }
    //        }
    //    }
    //    else if (NewState == EPlayerState::WALKING)
    //    {
    //        // 걷기 상태에서는 캐릭터 무브먼트에 속도 적용
    //        if (GetCharacterMovement())
    //        {
    //            // 이동 방향 설정
    //            FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();
    //            GetCharacterMovement()->Velocity = Direction * 500.0f;
    //        }
    //    }
    //    else if (NewState == EPlayerState::IDLE)
    //    {
    //        // 정지 상태
    //        if (GetCharacterMovement())
    //        {
    //            GetCharacterMovement()->Velocity = FVector::ZeroVector;
    //        }
    //    }
    //}

    // 이전 상태 저장
    EPlayerState PreviousState = CurrentState;

    // 항상 현재 상태 업데이트
    CurrentState = NewState;

    // 디버그 로그
    UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

    // 상태별 처리 (switch 문 사용으로 중복 상태도 가능)
    switch (NewState)
    {
    case EPlayerState::IDLE:
        // 정지 상태 - velocity를 0으로 설정
        if (GetCharacterMovement())
        {
            GetCharacterMovement()->Velocity = FVector::ZeroVector;
        }
        break;

    case EPlayerState::WALKING:
        // 걷기 상태 - 적절한 velocity 설정
        if (GetCharacterMovement())
        {
            FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();
            if (!Direction.IsNearlyZero())
            {
                GetCharacterMovement()->Velocity = Direction * 500.0f;
                GetCharacterMovement()->MaxWalkSpeed = 500.0f;

                // 방향에 맞춰 캐릭터 회전 (부드럽게)
                FRotator NewRotation = Direction.Rotation();
                NewRotation.Pitch = 0.0f; // 피치는 유지
                TargetRotation = NewRotation; // 부드러운 회전을 위해 타겟 회전 설정
            }
        }
        break;

    case EPlayerState::JUMPING:
        // 점프 상태 - 점프 함수 호출하되 velocity 유지
        // 주의: 캐릭터가 점프 중이면 velocity가 변경될 수 있음을 고려
        Jump();
        break;

    case EPlayerState::ATTACKING:
        // 공격 상태 - 애니메이션 몽타주 재생
        if (AttackMontage)
        {
            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
            if (AnimInstance)
            {
                AnimInstance->Montage_Play(AttackMontage, 1.0f);
            }
        }

        // 중요: 공격 중에도 이전 상태의 velocity를 유지 (공격하면서 이동 가능)
        if (PreviousState == EPlayerState::WALKING && GetCharacterMovement())
        {
            // 이전에 이동 중이었다면 이동 velocity 유지
            FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();
            if (!Direction.IsNearlyZero())
            {
                GetCharacterMovement()->Velocity = Direction * 500.0f;
            }
        }
        break;
    }
}

void AOtherCharacter::UpdateTransform(const FVector& NewPosition, const FRotator& NewRotation)
{
    TargetPosition = NewPosition;
    TargetRotation = NewRotation;
    PositionInterpolationTime = 0.0f;
    RotationInterpolationTime = 0.0f;

    //// 현재 위치와 새 목표 위치 간의 거리 계산
    //float Distance = FVector::Dist(GetActorLocation(), NewPosition);

    //// 거리가 충분히 멀면 WALKING 상태로 변경 (단, 이미 JUMPING이나 ATTACKING이 아닌 경우에만)
    //if (Distance > 50.0f && CurrentState != EPlayerState::JUMPING && CurrentState != EPlayerState::ATTACKING)
    //{
    //    // WALKING으로 상태 변경
    //    if (CurrentState != EPlayerState::WALKING)
    //    {
    //        UpdateAnimationState(EPlayerState::WALKING);
    //    }
    //    else
    //    {
    //        // 이미 걷는 중이면 velocity만 업데이트
    //        if (GetCharacterMovement())
    //        {
    //            FVector Direction = (NewPosition - GetActorLocation()).GetSafeNormal();
    //            GetCharacterMovement()->Velocity = Direction * 500.0f;
    //        }
    //    }
    //}
    //// 거리가 매우 가깝고, 현재 WALKING 상태면 IDLE로 변경
    //else if (Distance < 10.0f && CurrentState == EPlayerState::WALKING)
    //{
    //    UpdateAnimationState(EPlayerState::IDLE);
    //}

    //// 거리가 매우 멀면 즉시 이동 (텔레포트)
    //if (Distance > 1000.0f)
    //{
    //    SetActorLocation(NewPosition);
    //    GetCharacterMovement()->Velocity = FVector::ZeroVector; // 텔레포트 후 정지

    //    // 텔레포트 후 상태 업데이트 (Idle)
    //    UpdateAnimationState(EPlayerState::IDLE);
    //}
}