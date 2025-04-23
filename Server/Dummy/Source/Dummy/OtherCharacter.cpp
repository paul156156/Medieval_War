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

    //// WALKING ������ �� ��� velocity ������Ʈ
    //if (CurrentState == EPlayerState::WALKING ||
    //    (CurrentState == EPlayerState::ATTACKING && GetCharacterMovement()->Velocity.SizeSquared() > 0))
    //{
    //    if (GetCharacterMovement())
    //    {
    //        FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();

    //        // �Ÿ��� ����� �����ٸ� �ӵ� ����
    //        if (Distance < 100.0f)
    //        {
    //            float SpeedFactor = FMath::Clamp(Distance / 100.0f, 0.0f, 1.0f);
    //            GetCharacterMovement()->Velocity = Direction * 500.0f * SpeedFactor;

    //            // �ſ� ��������� IDLE ���·� ��ȯ
    //            if (Distance < 10.0f && CurrentState == EPlayerState::WALKING)
    //            {
    //                GetCharacterMovement()->Velocity = FVector::ZeroVector;

    //                // ���� ���� �ƴϸ� IDLE�� ����
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

    //// JUMPING ������ ��� Z �ӵ��� �����ϰ� XY ������ ����
    //else if (CurrentState == EPlayerState::JUMPING && GetCharacterMovement())
    //{
    //    FVector CurrentVelocity = GetCharacterMovement()->Velocity;
    //    FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();

    //    // XY ������ ���⸸ ���� (Z �ӵ��� ���� ������ ó��)
    //    FVector HorizontalDirection = FVector(Direction.X, Direction.Y, 0).GetSafeNormal();

    //    if (!HorizontalDirection.IsNearlyZero())
    //    {
    //        // Z �ӵ��� �����ϰ� XY �ӵ��� ������Ʈ
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

    //    // �������Ʈ���� ó���� �̺�Ʈ ȣ��
    //    OnAnimationStateChanged(NewState);

    //    // ����� �α�
    //    UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

    //    // �ִϸ��̼� ���¿� ���� �߰� ó��
    //    if (NewState == EPlayerState::JUMPING)
    //    {
    //        // ���� ���¿����� ĳ������ ���� �Լ� ȣ��
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

    // ���� ���� �ÿ��� �ִϸ��̼� ������Ʈ
    //if (CurrentState != NewState)
    //{
    //    CurrentState = NewState;

    //    // �������Ʈ �̺�Ʈ ȣ��
    //    //OnAnimationStateChanged(NewState);

    //    // �α�
    //    UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

    //    // �ִϸ��̼� ���¿� ���� �߰� ó��
    //    if (NewState == EPlayerState::JUMPING)
    //    {
    //        // ����
    //        Jump();
    //    }
    //    else if (NewState == EPlayerState::ATTACKING)
    //    {
    //        // ���� �ִϸ��̼� ���
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
    //        // �ȱ� ���¿����� ĳ���� �����Ʈ�� �ӵ� ����
    //        if (GetCharacterMovement())
    //        {
    //            // �̵� ���� ����
    //            FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();
    //            GetCharacterMovement()->Velocity = Direction * 500.0f;
    //        }
    //    }
    //    else if (NewState == EPlayerState::IDLE)
    //    {
    //        // ���� ����
    //        if (GetCharacterMovement())
    //        {
    //            GetCharacterMovement()->Velocity = FVector::ZeroVector;
    //        }
    //    }
    //}

    // ���� ���� ����
    EPlayerState PreviousState = CurrentState;

    // �׻� ���� ���� ������Ʈ
    CurrentState = NewState;

    // ����� �α�
    UE_LOG(LogTemp, Display, TEXT("AnimationState Changed to: %s"), *PlayerStateToString(CurrentState));

    // ���º� ó�� (switch �� ������� �ߺ� ���µ� ����)
    switch (NewState)
    {
    case EPlayerState::IDLE:
        // ���� ���� - velocity�� 0���� ����
        if (GetCharacterMovement())
        {
            GetCharacterMovement()->Velocity = FVector::ZeroVector;
        }
        break;

    case EPlayerState::WALKING:
        // �ȱ� ���� - ������ velocity ����
        if (GetCharacterMovement())
        {
            FVector Direction = (TargetPosition - GetActorLocation()).GetSafeNormal();
            if (!Direction.IsNearlyZero())
            {
                GetCharacterMovement()->Velocity = Direction * 500.0f;
                GetCharacterMovement()->MaxWalkSpeed = 500.0f;

                // ���⿡ ���� ĳ���� ȸ�� (�ε巴��)
                FRotator NewRotation = Direction.Rotation();
                NewRotation.Pitch = 0.0f; // ��ġ�� ����
                TargetRotation = NewRotation; // �ε巯�� ȸ���� ���� Ÿ�� ȸ�� ����
            }
        }
        break;

    case EPlayerState::JUMPING:
        // ���� ���� - ���� �Լ� ȣ���ϵ� velocity ����
        // ����: ĳ���Ͱ� ���� ���̸� velocity�� ����� �� ������ ���
        Jump();
        break;

    case EPlayerState::ATTACKING:
        // ���� ���� - �ִϸ��̼� ��Ÿ�� ���
        if (AttackMontage)
        {
            UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
            if (AnimInstance)
            {
                AnimInstance->Montage_Play(AttackMontage, 1.0f);
            }
        }

        // �߿�: ���� �߿��� ���� ������ velocity�� ���� (�����ϸ鼭 �̵� ����)
        if (PreviousState == EPlayerState::WALKING && GetCharacterMovement())
        {
            // ������ �̵� ���̾��ٸ� �̵� velocity ����
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

    //// ���� ��ġ�� �� ��ǥ ��ġ ���� �Ÿ� ���
    //float Distance = FVector::Dist(GetActorLocation(), NewPosition);

    //// �Ÿ��� ����� �ָ� WALKING ���·� ���� (��, �̹� JUMPING�̳� ATTACKING�� �ƴ� ��쿡��)
    //if (Distance > 50.0f && CurrentState != EPlayerState::JUMPING && CurrentState != EPlayerState::ATTACKING)
    //{
    //    // WALKING���� ���� ����
    //    if (CurrentState != EPlayerState::WALKING)
    //    {
    //        UpdateAnimationState(EPlayerState::WALKING);
    //    }
    //    else
    //    {
    //        // �̹� �ȴ� ���̸� velocity�� ������Ʈ
    //        if (GetCharacterMovement())
    //        {
    //            FVector Direction = (NewPosition - GetActorLocation()).GetSafeNormal();
    //            GetCharacterMovement()->Velocity = Direction * 500.0f;
    //        }
    //    }
    //}
    //// �Ÿ��� �ſ� ������, ���� WALKING ���¸� IDLE�� ����
    //else if (Distance < 10.0f && CurrentState == EPlayerState::WALKING)
    //{
    //    UpdateAnimationState(EPlayerState::IDLE);
    //}

    //// �Ÿ��� �ſ� �ָ� ��� �̵� (�ڷ���Ʈ)
    //if (Distance > 1000.0f)
    //{
    //    SetActorLocation(NewPosition);
    //    GetCharacterMovement()->Velocity = FVector::ZeroVector; // �ڷ���Ʈ �� ����

    //    // �ڷ���Ʈ �� ���� ������Ʈ (Idle)
    //    UpdateAnimationState(EPlayerState::IDLE);
    //}
}