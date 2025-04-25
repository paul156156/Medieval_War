// OtherCharacter.cpp
#include "OtherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AOtherCharacter::AOtherCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // �⺻ ���� ����
    CurrentState = EPlayerState::IDLE;

    // AI ��Ʈ�ѷ� ��Ȱ��ȭ
    AutoPossessAI = EAutoPossessAI::Disabled;

    // ������Ʈ ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ĳ���� �����Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AOtherCharacter::BeginPlay()
{
    Super::BeginPlay();

    // ����� �α�
    UE_LOG(LogTemp, Display, TEXT("OtherCharacter spawned at %s"), *GetActorLocation().ToString());
}

void AOtherCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ��ġ�� ȸ�� ����
    PositionInterpolationTime += DeltaTime;
    RotationInterpolationTime += DeltaTime;

    float PosAlpha = FMath::Clamp(PositionInterpolationTime / 0.1f, 0.0f, 1.0f);
    float RotAlpha = FMath::Clamp(RotationInterpolationTime / 0.1f, 0.0f, 1.0f);

    // ���� ��ġ�� ��ǥ ��ġ ���� �Ÿ� ���
    float Distance = FVector::Dist(GetActorLocation(), TargetPosition);

    // �Ÿ��� �ָ� ���� ����
    if (Distance > 300.0f)
    {
        // �� ���� ����
        PosAlpha = FMath::Clamp(PositionInterpolationTime / 0.05f, 0.0f, 1.0f);
    }

    //FVector NewPos = FMath::Lerp(GetActorLocation(), TargetPosition, PosAlpha);
    //FRotator NewRot = FMath::Lerp(GetActorRotation(), TargetRotation, RotAlpha);

    // �� ��ġ�� ȸ�� ��� �� ����
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

        // �������Ʈ���� ó���� �̺�Ʈ ȣ��
        //OnAnimationStateChanged(NewState);

        // ����� �α�
        UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

        // �ִϸ��̼� ���¿� ���� �߰� ó��
        if (NewState == EPlayerState::JUMPING)
        {
            // ���� ���¿����� ĳ������ ���� �Լ� ȣ��
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
            *GetName(),                     // ĳ���� �̸� (Ȥ�� ID ���� ������ �װɷ�!)
            NewPosition.X, NewPosition.Y, NewPosition.Z,
            NewVelocity.X, NewVelocity.Y, NewVelocity.Z
        );
}