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
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->JumpZVelocity = 300.f;
    GetCharacterMovement()->AirControl = 0.35f;

    CurrentState = EPlayerState::IDLE;
}

void AMyPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (!bIsRemoteControlled)
    {
        NotifySpawn();

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
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (!bIsRemoteControlled)
    {
        if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
        {
            if (MoveAction)
            {
                Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::Move);
                Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyPlayerCharacter::Move);
            }
            if (RunAction)
            {
                Input->BindAction(RunAction, ETriggerEvent::Started, this, &AMyPlayerCharacter::StartRun);
                Input->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyPlayerCharacter::StopRun);
            }
            if (CrouchAction)
            {
                Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMyPlayerCharacter::StartCrouch);
                Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMyPlayerCharacter::StopCrouch);
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
}

void AMyPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsRemoteControlled)
    {
        InterpolateRemoteMovement(DeltaTime);
    }
    else
    {
        SendInputToServer();
    }
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

void AMyPlayerCharacter::StartRun(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
    bRunPressed = true;
}

void AMyPlayerCharacter::StopRun(const FInputActionValue& Value)
{
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    bRunPressed = false;
}

void AMyPlayerCharacter::StartCrouch(const FInputActionValue& Value)
{
    Crouch();
    bCrouchPressed = true;
}

void AMyPlayerCharacter::StopCrouch(const FInputActionValue& Value)
{
    UnCrouch();
    bCrouchPressed = false;
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
    bIsAttackPressed = true;

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
        ControlRotationRoll = Controller->GetControlRotation().Roll;
    }
}

void AMyPlayerCharacter::NotifySpawn()
{
    FVector Pos = GetActorLocation();
    FRotator Rot = GetActorRotation();

    UNetworkManager* Network = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (Network && Network->IsConnected())
    {
		Vec3 Position = Vec3(Pos.X, Pos.Y, Pos.Z);
		Rot3 Rotation = Rot3(Rot.Pitch, Rot.Yaw, Rot.Roll);

        Network->SendPlayerInitInfo(Position, Rotation);
    }
}

void AMyPlayerCharacter::SendInputToServer()
{
    UNetworkManager* Network = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (Network && Network->IsConnected())
    {
        Network->SendPlayerInput(ForwardInput, RightInput, ControlRotationPitch, ControlRotationYaw, ControlRotationRoll, bRunPressed, bCrouchPressed, bJumpPressed, bAttackPressed);
        //Network->SendPlayerMovement(ForwardInput, RightInput, Rotation);
        //Network->SendPlayerEvent(bRunPressed, bCrouchPressed, bJumpPressed, bAttackPressed);
    }
}

void AMyPlayerCharacter::UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState)
{
    TargetLocation = NewTransform.GetLocation();
    TargetRotation = NewTransform.GetRotation().Rotator();
    CurrentState = NewState;

    if (!bInitialPositionSet)
    {
        SetActorLocation(TargetLocation);
        SetActorRotation(TargetRotation);
        bInitialPositionSet = true;
    }

    if (NewState == EPlayerState::ATTACKING && AttackMontage)
    {
        if (UAnimInstance* Anim = GetMesh()->GetAnimInstance())
        {
            Anim->Montage_Play(AttackMontage);
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

void AMyPlayerCharacter::InterpolateRemoteMovement(float DeltaTime)
{
    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
    SetActorLocation(NewLocation);

    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
    SetActorRotation(NewRotation);
}
