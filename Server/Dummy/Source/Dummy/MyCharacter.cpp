// MyCharacter.cpp
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // ������Ʈ ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ĳ���� �����Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // ������ �� ����
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // ī�޶� ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // �ʱ� ���� ����
    CurrentState = EPlayerState::IDLE;
    CurrentForwardValue = 0.0f;
    CurrentRightValue = 0.0f;
    bIsAttacking = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input ����
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // �� �����Ӹ��� ���� ������Ʈ
    UpdateCharacterState();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Enhanced Input ���ε� ����
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // �̵� �׼� ���ε�
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::StopMoving);
        // �ü� �׼� ���ε�
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        // ���� �׼� ���ε�
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJumping);
        // ���� �׼� ���ε�
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
    }
}

void AMyCharacter::UpdateCharacterState()
{
    // ���� ���� ����
    EPlayerState PreviousState = CurrentState;

    // �� ���� ���
    if (bIsAttacking)
    {
        CurrentState = EPlayerState::ATTACKING;
    }
    else if (GetCharacterMovement()->IsFalling())
    {
        CurrentState = EPlayerState::JUMPING;
    }
    else if (GetVelocity().Size() > 10.0f)
    {
        CurrentState = EPlayerState::WALKING;
    }
    else
    {
        CurrentState = EPlayerState::IDLE;
    }

    // ���°� ����Ǿ����� �̺�Ʈ �߻�
    if (PreviousState != CurrentState)
    {
        OnCharacterStateChanged.Broadcast(CurrentState, GetActorLocation(), GetActorRotation(), GetVelocity());
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // ��/�� �̵�
        if (MovementVector.Y != 0.0f)
        {
            CurrentForwardValue = MovementVector.Y;
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);

            const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
            AddMovementInput(Direction, MovementVector.Y);
        }
        else
        {
            CurrentForwardValue = 0.0f;
        }

        // ��/�� �̵�
        if (MovementVector.X != 0.0f)
        {
            CurrentRightValue = MovementVector.X;
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);

            const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
            AddMovementInput(Direction, MovementVector.X);
        }
        else
        {
            CurrentRightValue = 0.0f;
        }
    }
}

void AMyCharacter::StopMoving(const FInputActionValue& Value)
{
    // Ű�� ���� ��������� 0 ������ ����
	CurrentForwardValue = 0.0f;
	CurrentRightValue = 0.0f;

    // ���� ������Ʈ
	UpdateCharacterState();
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void AMyCharacter::Jump()
{
    Super::Jump();

    // ���� �� ��� ���� ������Ʈ
    UpdateCharacterState();
}

void AMyCharacter::StopJumping()
{
    Super::StopJumping();

    // ���� �ߴ� �� ��� ���� ������Ʈ
    UpdateCharacterState();
}

void AMyCharacter::Attack()
{
    if (bIsAttacking)
        return; // �̹� ���� ���̸� ����

    bIsAttacking = true;

    // ��� ���� ������Ʈ
    UpdateCharacterState();

    // �ִϸ��̼� ���
    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            float MontageLength = AnimInstance->Montage_Play(AttackMontage, 1.0f);

            // ��Ÿ�� ����� ������ bIsAttacking�� false�� ����
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    bIsAttacking = false;
                    UpdateCharacterState(); // ���� ���� �� ���� ������Ʈ
                }, MontageLength, false);
        }
    }
    else
    {
        // ��Ÿ�ְ� ������ ������ ���� ����
        bIsAttacking = false;
        UpdateCharacterState();
    }
}