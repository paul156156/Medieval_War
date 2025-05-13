// MultiplayerCharacterAnimInstance.cpp
// 플레이어 캐릭터의 애니메이션 인스턴스 클래스 구현

#include "MultiplayerCharacterAnimInstance.h"
#include "MultiplayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMultiplayerCharacterAnimInstance::UMultiplayerCharacterAnimInstance()
{
    OwnerCharacter = nullptr;
    MovementComponent = nullptr;
    bIsInAir = false;
    bIsAccelerating = false;
    GroundSpeed = 0.0f;
    MovementDirection = 0.0f;
    CurrentPlayerState = EPlayerState::IDLE;
    LastStateChangeTime = 0.0f;
}

void UMultiplayerCharacterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    // 소유 캐릭터 참조 가져오기
    AActor* OwningActor = GetOwningActor();
    if (OwningActor)
    {
        OwnerCharacter = Cast<AMultiplayerCharacter>(OwningActor);

        if (OwnerCharacter)
        {
            MovementComponent = OwnerCharacter->GetCharacterMovement();
        }
    }
}

void UMultiplayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!OwnerCharacter || !MovementComponent)
    {
        // 캐릭터나 무브먼트 컴포넌트가 없으면 초기화
        NativeInitializeAnimation();

        if (!OwnerCharacter || !MovementComponent)
        {
            return;
        }
    }

    // 애니메이션 변수 업데이트
    bIsInAir = MovementComponent->IsFalling();
    bIsAccelerating = MovementComponent->GetCurrentAcceleration().Size() > 0.0f;

    // 지면 속도 계산
    FVector Velocity = OwnerCharacter->GetVelocity();
    Velocity.Z = 0.0f;
    GroundSpeed = Velocity.Size();

    // 이동 방향 계산
    if (GroundSpeed > 0.0f)
    {
        const FRotator ActorRotation = OwnerCharacter->GetActorRotation();
        const FRotator VelocityRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
        MovementDirection = UKismetMathLibrary::NormalizedDeltaRotator(VelocityRotation, ActorRotation).Yaw;
    }
    else
    {
        MovementDirection = 0.0f;
    }

    // 플레이어 상태 업데이트
    CurrentPlayerState = OwnerCharacter->GetCurrentState();
    LastStateChangeTime = OwnerCharacter->GetLastStateChangeTime();
}

void UMultiplayerCharacterAnimInstance::SetPlayerState(EPlayerState NewState)
{
    if (OwnerCharacter)
    {
        CurrentPlayerState = NewState;
    }
}