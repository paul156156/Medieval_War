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

    // 컴포넌트 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 500.f;
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

    if (Controller)
    {
        FRotator ControlRot = Controller->GetControlRotation();
        CurrentControlRotationYaw = ControlRot.Yaw;
		CurrentControlRotationPitch = ControlRot.Pitch;
    }

    // 인스턴스별 타이머를 사용
    LogTimer += DeltaTime;
    if (LogTimer >= 5.0f)  // 1초마다 로그
    {
        LogTimer = 0.0f;
        UE_LOG(LogTemp, Display, TEXT("[My Character] ClientId %d, Position: X=%.1f, Y=%.1f, Z=%.1f"),
            NetworkManager->GetLocalClientId(), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

        //FVector LocalPos = GetActorLocation();
        //FRotator LocalRot = GetActorRotation();

        //float PosDelta = FVector::Dist(LocalPos, LastServerPosition);
        //float RotDelta = FMath::Abs(LocalRot.Yaw - LastServerRotation.Yaw); // 또는 Pitch, Roll도 포함

        //UE_LOG(LogTemp, Display,
        //    TEXT("[My Character] ClientId %d\n  Local Pos:  (%.1f, %.1f, %.1f)\n  Server Pos: (%.1f, %.1f, %.1f)\n  ΔPos: %.2f\n  Local Yaw: %.1f | Server Yaw: %.1f | ΔYaw: %.2f"),
        //    NetworkManager->GetLocalClientId(),
        //    LocalPos.X, LocalPos.Y, LocalPos.Z,
        //    LastServerPosition.X, LastServerPosition.Y, LastServerPosition.Z,
        //    PosDelta,
        //    LocalRot.Yaw, LastServerRotation.Yaw, RotDelta);
    }

    if (NetworkManager && NetworkManager->IsConnected())
    {
        bool bInputChanged =
            (CurrentForwardValue != PrevForwardValue) ||
            (CurrentRightValue != PrevRightValue) ||
			(CurrentControlRotationYaw != PrevControlRotationYaw) ||
			(CurrentControlRotationPitch != PrevControlRotationPitch) ||
            bJumpPressed ||
            bAttackPressed;

        if (bInputChanged)
        {
            FInputPacket Packet;
            Packet.Header.PacketSize = sizeof(FInputPacket);
            Packet.Header.PacketType = EPacketType::PLAYER_INPUT_INFO;
            Packet.ClientId = NetworkManager->GetLocalClientId();
            Packet.ForwardValue = CurrentForwardValue;
            Packet.RightValue = CurrentRightValue;
            Packet.ControlRotationYaw = CurrentControlRotationYaw;
            Packet.ControlRotationPitch = CurrentControlRotationPitch;
            Packet.bJumpPressed = bJumpPressed;
            Packet.bAttackPressed = bAttackPressed;

            NetworkManager->SendInputPacket(Packet);

            //UE_LOG(LogTemp, Display, TEXT("Packet Input Value - Forward: % .2f, Right: % .2f, Yaw: % .2f, Jump: %d, Attack: %d"),
            // CurrentForwardValue, CurrentRightValue, CurrentControlRotationYaw,
            // bJumpPressed ? 1 : 0, bAttackPressed ? 1 : 0);

            PrevForwardValue = CurrentForwardValue;
            PrevRightValue = CurrentRightValue;
			PrevControlRotationYaw = CurrentControlRotationYaw;
			PrevControlRotationPitch = CurrentControlRotationPitch;
            bJumpPressed = false;
            bAttackPressed = false;
        }
    }
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
        //EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
        EnhancedInputComponent->BindAction(LeftAttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::OnLeftMousePressed);
        EnhancedInputComponent->BindAction(LeftAttackAction, ETriggerEvent::Completed, this, &AMyCharacter::OnLeftMouseReleased);
        EnhancedInputComponent->BindAction(RightAttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::OnRightMousePressed);
        EnhancedInputComponent->BindAction(RightAttackAction, ETriggerEvent::Completed, this, &AMyCharacter::OnRightMouseReleased);

    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator ControlRotation = Controller->GetControlRotation();

        const FRotator YawRotation(0, ControlRotation.Yaw, 0);

        CurrentControlRotationYaw = ControlRotation.Yaw;
        CurrentControlRotationPitch = ControlRotation.Pitch;

        if (MovementVector.Y != 0.0f)
        {
            CurrentForwardValue = MovementVector.Y;
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

    // 서버에 멈춤 입력 전송
    if (NetworkManager && NetworkManager->IsConnected())
    {
        FInputPacket Packet;
        Packet.Header.PacketSize = sizeof(FInputPacket);
        Packet.Header.PacketType = EPacketType::PLAYER_INPUT_INFO;
        Packet.ClientId = NetworkManager->GetLocalClientId();
        Packet.ForwardValue = 0.0f;
        Packet.RightValue = 0.0f;
        Packet.ControlRotationYaw = CurrentControlRotationYaw;
        Packet.ControlRotationPitch = CurrentControlRotationPitch;
        Packet.bJumpPressed = false;
        Packet.bAttackPressed = false;

        NetworkManager->SendInputPacket(Packet);

        PrevForwardValue = 0.0f;
        PrevRightValue = 0.0f;
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);

        // 현재 바라보는 방향 저장
        FRotator ControlRotation = Controller->GetControlRotation();
        CurrentControlRotationYaw = ControlRotation.Yaw;
		CurrentControlRotationPitch = ControlRotation.Pitch;
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

void AMyCharacter::TryAttack()
{
    if (bIsAttacking) return;

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance) return;

    UAnimMontage* SelectedMontage = nullptr;

    if (bLeftMousePressed && bRightMousePressed)
    {
        SelectedMontage = AttackMontage_3;
    }
    else if (bLeftMousePressed)
    {
        SelectedMontage = AttackMontage_1;
    }
    else if (bRightMousePressed)
    {
        SelectedMontage = AttackMontage_2;
    }

    if (SelectedMontage)
    {
        bIsAttacking = true;
        float MontageLength = AnimInstance->Montage_Play(SelectedMontage, 1.0f);
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
            {
                bIsAttacking = false;
            }, MontageLength, false);
    }
}

void AMyCharacter::OnLeftMousePressed()
{
    bLeftMousePressed = true;
    TryAttack();
}

void AMyCharacter::OnLeftMouseReleased()
{
    bLeftMousePressed = false;
}

void AMyCharacter::OnRightMousePressed()
{
    bRightMousePressed = true;
    TryAttack();
}

void AMyCharacter::OnRightMouseReleased()
{
    bRightMousePressed = false;
}

//void AMyCharacter::Attack()
//{
//    if (bIsAttacking)
//        return;
//
//    bAttackPressed = true;
//
//    if (AttackMontage_1)
//    {
//        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//        if (AnimInstance)
//        {
//            float MontageLength = AnimInstance->Montage_Play(AttackMontage_1, 1.0f);
//
//            FTimerHandle TimerHandle;
//            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
//                {
//                    bIsAttacking = false;
//                }, MontageLength, false);
//        }
//    }
//	else if (AttackMontage_2)
//	{
//		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//		if (AnimInstance)
//		{
//			float MontageLength = AnimInstance->Montage_Play(AttackMontage_2, 1.0f);
//			FTimerHandle TimerHandle;
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
//				{
//					bIsAttacking = false;
//				}, MontageLength, false);
//		}
//	}
//	else if (AttackMontage_1 && AttackMontage_2)
//	{
//		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//		if (AnimInstance)
//		{
//			float MontageLength = AnimInstance->Montage_Play(AttackMontage_3, 1.0f);
//			FTimerHandle TimerHandle;
//			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
//				{
//					bIsAttacking = false;
//				}, MontageLength, false);
//		}
//	}
//    else
//    {
//        bIsAttacking = false;
//    }
//}
