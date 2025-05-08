#include "OtherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AOtherCharacter::AOtherCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    CurrentState = EPlayerState::IDLE;
    AutoPossessAI = EAutoPossessAI::Disabled;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AOtherCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("OtherCharacter spawned at %s"), *GetActorLocation().ToString());
}

void AOtherCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bInterpEnabled)
        return;

    const float InterpSpeed = 5.0f; // 보간 속도

    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetPosition, DeltaTime, InterpSpeed);
    SetActorLocation(NewLocation);

    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
    SetActorRotation(NewRotation);

    // Velocity는 GetCharacterMovement()->Velocity로 이미 적용 중
}

void AOtherCharacter::UpdateAnimationState(EPlayerState NewState)
{
    if (CurrentState != NewState)
    {
        CurrentState = NewState;

        UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));
        
        if (NewState == EPlayerState::JUMPING)
        {
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
    bInterpEnabled = true;

    ReplicatedVelocity = NewVelocity;


    //UE_LOG(LogTemp, Display,
    //    TEXT("[UpdateTransform] %s - Pos: (%.1f, %.1f, %.1f), Rot: (Yaw=%.1f, Pitch=%.1f, Roll=%.1f), Vel: (%.1f, %.1f, %.1f)"),
    //    *GetName(),
    //    NewPosition.X, NewPosition.Y, NewPosition.Z,
    //    NewRotation.Yaw, NewRotation.Pitch, NewRotation.Roll,
    //    NewVelocity.X, NewVelocity.Y, NewVelocity.Z);
}
