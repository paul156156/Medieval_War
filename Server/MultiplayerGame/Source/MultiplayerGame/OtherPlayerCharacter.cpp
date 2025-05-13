// OtherPlayerCharacter.cpp
#include "OtherPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"

AOtherPlayerCharacter::AOtherPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AOtherPlayerCharacter::UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState)
{
    // Ÿ�� ��ġ �� ȸ�� ������Ʈ
    TargetLocation = NewTransform.GetLocation();
    TargetRotation = NewTransform.GetRotation().Rotator();

    // ù ��ġ ������Ʈ�� ��� ��� �ݿ�
    if (!bInitialPositionSet)
    {
        SetActorLocation(TargetLocation);
        SetActorRotation(TargetRotation);
        bInitialPositionSet = true;
    }

    // ���� ������Ʈ
    CurrentState = NewState;

    // �ִϸ��̼� ���� ó��
    if (NewState == EPlayerState::ATTACKING)
    {
        if (AttackMontage)
        {
            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
            if (AnimInstance)
            {
                AnimInstance->Montage_Play(AttackMontage);
            }
        }
    }
    else if (NewState == EPlayerState::JUMPING)
    {
        GetCharacterMovement()->SetMovementMode(MOVE_Falling);
    }
    else if (NewState == EPlayerState::WALKING)
    {
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
    }
}

void AOtherPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaSeconds, InterpSpeed);
    SetActorLocation(NewLocation);

    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, InterpSpeed);
    SetActorRotation(NewRotation);
}