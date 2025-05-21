// MyPlayerCharacter.cpp
#include "MyPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NetworkManager.h"
#include "Animation/AnimInstance.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm);
    FollowCamera->bUsePawnControlRotation = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.35f;

    ForwardInput = 0.f;
    RightInput = 0.f;
    ControlRotationYaw = 0.f;
    bAttackPressed = false;
    bJumpPressed = false;
	bIsAttacked = false;
	bIsCrouched = false;
}

void AMyPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                if (DefaultMappingContext)
                {
                    Subsystem->AddMappingContext(DefaultMappingContext, 0);
                }
            }
        }
    }
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
            Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyPlayerCharacter::Move);
        }
        if (JumpAction)
        {
            Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyPlayerCharacter::StartJump);
            Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerCharacter::StopJump);
        }
        if (AttackAction)
        {
            Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyPlayerCharacter::Attack);
        }
        if (LookAction)
        {
            Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Look);
        }
    }
}

void AMyPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    SendInputToServer();
}

void AMyPlayerCharacter::UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState)
{
    UE_LOG(LogTemp, Warning, TEXT("[MyPlayerCharacter] UpdateFromNetwork called on local player. Should not happen."));
}

void AMyPlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D Movement = Value.Get<FVector2D>();
    FRotator YawRot(0, Controller->GetControlRotation().Yaw, 0);
    FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
    FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

    AddMovementInput(Forward, Movement.Y);
    AddMovementInput(Right, Movement.X);

    ForwardInput = Movement.Y;
    RightInput = Movement.X;
    ControlRotationYaw = YawRot.Yaw;
}

void AMyPlayerCharacter::StartJump(const FInputActionValue& Value)
{
    Jump();
    bJumpPressed = true;
}

void AMyPlayerCharacter::StopJump(const FInputActionValue& Value)
{
    StopJumping();
    bJumpPressed = false;
}

void AMyPlayerCharacter::Attack(const FInputActionValue& Value)
{
    bAttackPressed = true;
	bIsAttacked = true; // 공격 상태로 설정
    UE_LOG(LogTemp, Log, TEXT("[MyPlayerCharacter] Attack Triggered"));

    if (AttackMontage)
    {
        if (UAnimInstance* Anim = GetMesh()->GetAnimInstance())
        {
            Anim->Montage_Play(AttackMontage);
        }
    }

    GetWorld()->GetTimerManager().SetTimer(AttackResetHandle, [this]() {
        bAttackPressed = false;
        }, AttackMontageDuration, false);
}

void AMyPlayerCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();
    AddControllerYawInput(LookAxis.X);
    AddControllerPitchInput(LookAxis.Y);

    if (Controller)
    {
        ControlRotationPitch = Controller->GetControlRotation().Pitch;
        ControlRotationYaw = Controller->GetControlRotation().Yaw;
    }
}

void AMyPlayerCharacter::SendInputToServer()
{
    UNetworkManager* Network = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (Network && Network->IsConnected())
    {
        Network->SendPlayerInput(ForwardInput, RightInput, ControlRotationPitch,  ControlRotationYaw, ControlRotationRoll, bJumpPressed, bAttackPressed, bCrouchPressed);
    }
}