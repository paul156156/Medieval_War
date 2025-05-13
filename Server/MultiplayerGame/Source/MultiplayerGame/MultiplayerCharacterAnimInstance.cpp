// MultiplayerCharacterAnimInstance.cpp
// �÷��̾� ĳ������ �ִϸ��̼� �ν��Ͻ� Ŭ���� ����

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

    // ���� ĳ���� ���� ��������
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
        // ĳ���ͳ� �����Ʈ ������Ʈ�� ������ �ʱ�ȭ
        NativeInitializeAnimation();

        if (!OwnerCharacter || !MovementComponent)
        {
            return;
        }
    }

    // �ִϸ��̼� ���� ������Ʈ
    bIsInAir = MovementComponent->IsFalling();
    bIsAccelerating = MovementComponent->GetCurrentAcceleration().Size() > 0.0f;

    // ���� �ӵ� ���
    FVector Velocity = OwnerCharacter->GetVelocity();
    Velocity.Z = 0.0f;
    GroundSpeed = Velocity.Size();

    // �̵� ���� ���
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

    // �÷��̾� ���� ������Ʈ
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