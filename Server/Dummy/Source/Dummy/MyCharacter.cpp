// MyCharacter.cpp
#include "MyCharacter.h"
#include "MyNetworkGameMode.h"
#include "SimpleNetworkManager.h"
#include "Kismet/GameplayStatics.h"
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

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    CurrentState = EPlayerState::IDLE;
    CurrentForwardValue = 0.0f;
    CurrentRightValue = 0.0f;
    bIsAttacking = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    AMyNetworkGameMode* GameMode = Cast<AMyNetworkGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        NetworkManager = GameMode->GetNetworkManager();
    }

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

    if (NetworkManager && NetworkManager->IsConnected())
    {
        FInputPacket Packet;
        Packet.Header.PacketSize = sizeof(FInputPacket);
        Packet.Header.PacketType = EPacketType::INPUT;
        Packet.ClientId = 0; // ������ �����ϰų� �ڵ� ó��
        Packet.ForwardValue = CurrentForwardValue;
        Packet.RightValue = CurrentRightValue;
        Packet.ControlRotationYaw = CurrentControlRotationYaw;
        Packet.bJumpPressed = bJumpPressed;
        Packet.bAttackPressed = bAttackPressed;

        NetworkManager->SendInputPacket(Packet);
    }

    // �� ������ ���� �� ����/���� �÷��� �ʱ�ȭ
    bJumpPressed = false;
    bAttackPressed = false;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::StopMoving);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJumping);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
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
    CurrentForwardValue = 0.0f;
    CurrentRightValue = 0.0f;
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);

        // ���� �ٶ󺸴� ���� ����
        FRotator ControlRotation = Controller->GetControlRotation();
        CurrentControlRotationYaw = ControlRotation.Yaw;
    }
}

void AMyCharacter::Jump()
{
    Super::Jump();
    bJumpPressed = true;
}

void AMyCharacter::StopJumping()
{
    Super::StopJumping();
    bJumpPressed = false;
}

void AMyCharacter::Attack()
{
    if (bIsAttacking)
        return;

    bAttackPressed = true;

    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            float MontageLength = AnimInstance->Montage_Play(AttackMontage, 1.0f);

            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    bIsAttacking = false;
                }, MontageLength, false);
        }
    }
    else
    {
        bIsAttacking = false;
    }
}
