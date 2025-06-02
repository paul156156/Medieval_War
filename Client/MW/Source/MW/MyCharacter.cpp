// MyCharacter.cpp - ���� �÷��̾� �������� ����
#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // ��� �÷��̾�� ī�޶� ������Ʈ�� ���� (���߿� ��Ȱ��ȭ�� �� ����)
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bDoCollisionTest = true;
    SpringArm->bInheritPitch = true;
    SpringArm->bInheritYaw = true;
    SpringArm->bInheritRoll = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // ĳ���� �̵� ����
    GetCharacterMovement()->bOrientRotationToMovement = bAlwaysFaceMovementDirection;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, MovementRotationRate, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->GravityScale = 1.0f;

    // ��Ʈ�ѷ� ȸ�� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = !bAlwaysFaceMovementDirection;
    bUseControllerRotationRoll = false;

    // �ʱ� ���� ����
    CurrentState = EPlayerState::IDLE;
    CurrentAction = EPlayerAction::NONE;

    // �⺻���� ���� �÷��̾�� ���� (GameMode���� ������ �� ����)
    bIsLocalPlayer = true;
    bIsRemoteControlled = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input ������ SetupPlayerInputComponent���� ó��
    UE_LOG(LogTemp, Log, TEXT("Player spawned: %s (ID: %d, Local: %s)"),
        *GetName(), PlayerId, bIsLocalPlayer ? TEXT("Yes") : TEXT("No"));
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // ���� �÷��̾ �Է� ���ε� + Enhanced Input ����
    if (bIsLocalPlayer)
    {
        // Enhanced Input ����
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

        // �Է� �׼� ���ε�
        if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
        {
            if (MoveAction)
            {
                Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
                Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::Move);
            }

            if (RunAction)
            {
                Input->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartRun);
                Input->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
            }

            if (JumpAction)
            {
                Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::StartJump);
                Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);
            }

            if (AttackAction)
            {
                Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
            }

            if (DefendAction)
            {
                Input->BindAction(DefendAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartDefend);
                Input->BindAction(DefendAction, ETriggerEvent::Completed, this, &AMyCharacter::StopDefend);
            }

            if (LookAction)
            {
                Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
            }
        }
        UE_LOG(LogTemp, Log, TEXT("Input component set up for local player %d"), PlayerId);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Skipping input setup for remote player %d"), PlayerId);
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ���� �÷��̾ �Է��� ������ ����
    if (bIsLocalPlayer)
    {
        SendInputToServer();
    }

    // ��� �÷��̾�� ���� ��ġ�� ���� (���� �÷��̾ ���� ����)
    InterpolateToServerPosition(DeltaTime);

    // ����� ���� ǥ��
    if (bShowDebugInfo)
    {
        DisplayDebugInfo();
    }
}

void AMyCharacter::SetIsLocalPlayer(bool bLocal)
{
    bIsLocalPlayer = bLocal;
    bIsRemoteControlled = !bLocal;

    if (!bIsLocalPlayer)
    {
        // ���� �÷��̾� ����
        DisableCameraAndInput();

        // ���� �ӵ� ���� (���� �÷��̾��)
        InterpSpeed = 12.0f;
        VelocityInterpSpeed = 8.0f;

        // ����� ���� ǥ��
        bShowDebugInfo = true;
    }
    else
    {
        // ���� �÷��̾� ����
        EnableCameraAndInput();

        // ���� �ӵ� (���� �÷��̾��)
        InterpSpeed = 10.0f;
        VelocityInterpSpeed = 10.0f;

        // ����� ���� ǥ��
        bShowDebugInfo = true;
    }

    UE_LOG(LogTemp, Log, TEXT("Player %d set as %s player"),
        PlayerId, bIsLocalPlayer ? TEXT("Local") : TEXT("Remote"));
}

void AMyCharacter::SetIsRemoteControlled(bool bRemote)
{
    bIsRemoteControlled = bRemote;
    bIsLocalPlayer = !bRemote;

    if (bIsRemoteControlled)
    {
        DisableCameraAndInput();
    }
    else
    {
        EnableCameraAndInput();
    }
}

void AMyCharacter::DisableCameraAndInput()
{
    // ī�޶� ��Ȱ��ȭ
    if (FollowCamera)
    {
        FollowCamera->SetActive(false);
    }

    if (SpringArm)
    {
        SpringArm->SetActive(false);
    }

    // ��Ʈ�ѷ� ȸ�� ��Ȱ��ȭ
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    UE_LOG(LogTemp, Log, TEXT("Camera and input disabled for remote player %d"), PlayerId);
}

void AMyCharacter::EnableCameraAndInput()
{
    // ī�޶� Ȱ��ȭ
    if (FollowCamera)
    {
        FollowCamera->SetActive(true);
    }

    if (SpringArm)
    {
        SpringArm->SetActive(true);
    }

    // ��Ʈ�ѷ� ȸ�� ���� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = !bAlwaysFaceMovementDirection;
    bUseControllerRotationRoll = false;

    UE_LOG(LogTemp, Log, TEXT("Camera and input enabled for local player %d"), PlayerId);
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    // ���� �÷��̾ ó��
    if (!bIsLocalPlayer) return;

    FVector2D Movement = Value.Get<FVector2D>();

    if (Controller)
    {
        FRotator Rotation = Controller->GetControlRotation();

        // �Է°��� ���� (���� ���ۿ�)
        ForwardInput = Movement.Y;
        RightInput = Movement.X;
        PitchInput = Rotation.Pitch;
        YawInput = Rotation.Yaw;
        RollInput = Rotation.Roll;
    }
}

void AMyCharacter::StartRun(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bRunPressed = true;
}

void AMyCharacter::StopRun(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bRunPressed = false;
}

void AMyCharacter::StartJump(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bJumpPressed = true;

    // ���ÿ��� ��� ���� ���� (�������� ����)
    Jump();
}

void AMyCharacter::StopJump(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bJumpPressed = false;
    StopJumping();
}

void AMyCharacter::Attack(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bAttackPressed = true;

    // ���ÿ��� ��� �ִϸ��̼� ��� (�������� ����)
    if (AttackMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Play(AttackMontage);
        }
    }
}

void AMyCharacter::StartDefend(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bDefendPressed = true;

    if (DefendMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Play(DefendMontage);
        }
    }
}

void AMyCharacter::StopDefend(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    bDefendPressed = false;

    if (DefendMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Stop(0.2f, DefendMontage);
        }
    }
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    FVector2D LookAxis = Value.Get<FVector2D>();

    // ���콺 �Է����� ī�޶� ȸ��
    AddControllerYawInput(LookAxis.X);
    AddControllerPitchInput(LookAxis.Y);

    // ȸ���� ������Ʈ (���� ���ۿ�)
    if (Controller)
    {
        FRotator ControlRotation = Controller->GetControlRotation();
        PitchInput = ControlRotation.Pitch;
        YawInput = ControlRotation.Yaw;
        RollInput = ControlRotation.Roll;
    }
}

void AMyCharacter::NotifySpawn()
{
    UE_LOG(LogTemp, Log, TEXT("NotifySpawn called for %s"), *GetName());

    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (NetworkManager && NetworkManager->IsConnected())
    {
        FVector Position = GetActorLocation();
        FRotator Rotation = GetActorRotation();

        // ������ Vec3/Rot3 ����ü�� ��ȯ
        Vec3 ServerPosition(Position.X, Position.Y, Position.Z);
        Rot3 ServerRotation(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

        NetworkManager->SendPlayerInitInfo(ServerPosition, ServerRotation);
    }
}

void AMyCharacter::SendInputToServer()
{
    // ���� �÷��̾ �Է� ����
    if (!bIsLocalPlayer) return;

    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (!NetworkManager || !NetworkManager->IsConnected())
    {
        return;
    }

    // �Է� ���� �� ���� (60Hz)
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastInputSendTime < (1.0f / InputSendRate))
    {
        return;
    }

    // �Է��� ����Ǿ��ų� �ֱ������� ����
    if (HasInputChanged() || (CurrentTime - LastInputSendTime > 0.5f))
    {
        NetworkManager->SendPlayerInput(
            ForwardInput, RightInput,
            PitchInput, YawInput, RollInput,
            bRunPressed, bJumpPressed, bAttackPressed, bDefendPressed
        );

        LastInputSendTime = CurrentTime;

        // ���� �Է°� ����
        PreviousForwardInput = ForwardInput;
        PreviousRightInput = RightInput;
        PreviousPitchInput = PitchInput;
        PreviousYawInput = YawInput;
        bPreviousRunPressed = bRunPressed;
        bPreviousJumpPressed = bJumpPressed;
        bPreviousAttackPressed = bAttackPressed;
        bPreviousDefendPressed = bDefendPressed;
    }
}

void AMyCharacter::UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction)
{
    //�������� ���� ���� �ִ� �����ͷ� ��ǥ ���� (���� �÷��̾�� ����)
    TargetLocation = NewTransform.GetLocation();
    //TargetRotation = NewTransform.GetRotation().Rotator();

    // ===== ȸ�� ������Ʈ ���� - Yaw�� ��� =====
    FRotator ServerRotation = NewTransform.GetRotation().Rotator();

    // ĳ���� ȸ���� Yaw�� ��� (Pitch, Roll ����)
    TargetRotation = FRotator(
        0.0f,                    // Pitch = 0
        ServerRotation.Yaw,      // Yaw�� ���
        0.0f                     // Roll = 0
    );

    TargetVelocity = NetworkVelocity;

    // �ʱ� ��ġ ���� (�ڷ���Ʈ)
    //if (!bInitialPositionSet)
    //{
    //    SetActorLocation(TargetLocation);
    //    SetActorRotation(TargetRotation);
    //    GetCharacterMovement()->Velocity = TargetVelocity;
    //    bInitialPositionSet = true;

    //    UE_LOG(LogTemp, Log, TEXT("Local player %d initial position set: (%.1f, %.1f, %.1f)"),
    //        PlayerId, TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
    //}

    // ���� ������Ʈ
    EPlayerState PreviousState = CurrentState;
    CurrentState = NewState;

    // ���º� ó�� (�������� ������ ���¿� ����)
    switch (CurrentState)
    {
    case EPlayerState::WALKING:
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        break;
    case EPlayerState::RUNNING:
        GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        break;
    case EPlayerState::JUMPING:
        GetCharacterMovement()->SetMovementMode(MOVE_Falling);
        break;
    case EPlayerState::IDLE:
    default:
        GetCharacterMovement()->MaxWalkSpeed = 0.0f;
        GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        break;
    }

    // �׼� ó��
    EPlayerAction PreviousAction = CurrentAction;
    CurrentAction = NewAction;

    if (PreviousAction != CurrentAction)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

        switch (CurrentAction)
        {
        case EPlayerAction::ATTACK:
            // ATTACK ������ �� �׻� ���� �ִϸ��̼��� ����ǵ��� ����
            if (AttackMontage)
            {
                // �̹� ���� �ִϸ��̼��� ������� �ƴ϶�� ���
                if (!AnimInstance->Montage_IsPlaying(AttackMontage))
                {
                    AnimInstance->Montage_Play(AttackMontage);
                    UE_LOG(LogTemp, Log, TEXT("Remote player %d: Starting ATTACK animation"), PlayerId);
                }
            }
            break;

        case EPlayerAction::DEFEND:
            // DEFEND ������ �� �׻� ��� �ִϸ��̼��� ����ǵ��� ����
            if (DefendMontage)
            {
                if (!AnimInstance->Montage_IsPlaying(DefendMontage))
                {
                    AnimInstance->Montage_Play(DefendMontage);
                    UE_LOG(LogTemp, Log, TEXT("Remote player %d: Starting DEFEND animation"), PlayerId);
                }
            }
            break;

        case EPlayerAction::NONE:
        default:
            break;
        }
    }
}

void AMyCharacter::InterpolateToServerPosition(float DeltaTime)
{
    if (TargetLocation.IsZero()) return;

    // ��ġ ���� (���� �÷��̾�� ������ ���)
    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
    SetActorLocation(NewLocation);

    // ===== ȸ�� ���� ���� - Yaw�� ��� =====
    FRotator CurrentRotation = GetActorRotation();

    // �������� ���� ȸ������ ���͸� (Yaw�� ���)
    FRotator FilteredTargetRotation = FRotator(
        0.0f,                    // Pitch = 0 (�յ� ����� ����)
        TargetRotation.Yaw,      // Yaw�� ��� (�¿� ȸ��)
        0.0f                     // Roll = 0 (�¿� ����� ����)
    );

    // Yaw ���� ���� (�ִ� ��η� ȸ��)
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, FilteredTargetRotation, DeltaTime, InterpSpeed);
    SetActorRotation(NewRotation);

    // �ӵ� ���� (�ε巯�� �ִϸ��̼��� ����)
    //FVector CurrentVelocity = GetVelocity();
    //FVector NewVelocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, DeltaTime, VelocityInterpSpeed);
    //GetCharacterMovement()->Velocity = NewVelocity;
    GetCharacterMovement()->Velocity = TargetVelocity;

    //UE_LOG(LogTemp, Warning, TEXT("[InterpToServerPosition] Velocity: %s | Speed: %.2f"),
    //    *TargetVelocity.ToString(), TargetVelocity.Size());
    //UE_LOG(LogTemp, Warning, TEXT("[InterpToServerPosition] Velocity: %s | Speed: %.2f"),
    //    *TargetVelocity.ToString(), TargetVelocity.Size());
}

bool AMyCharacter::HasInputChanged() const
{
    const float Threshold = 0.01f;
	const float roatonThreshold = 0.1f; // ȸ�� �Է� ��ȭ ���� �Ӱ谪

    return (FMath::Abs(ForwardInput - PreviousForwardInput) > Threshold ||
        FMath::Abs(RightInput - PreviousRightInput) > Threshold ||
        FMath::Abs(PitchInput - PreviousPitchInput) > roatonThreshold ||
        FMath::Abs(YawInput - PreviousYawInput) > roatonThreshold ||
        FMath::Abs(RollInput - PreviousRollInput) > roatonThreshold ||
        bRunPressed != bPreviousRunPressed ||
        bJumpPressed != bPreviousJumpPressed ||
        bAttackPressed != bPreviousAttackPressed ||
        bDefendPressed != bPreviousDefendPressed);
}

void AMyCharacter::DisplayDebugInfo()
{
    if (bShowDebugInfo) return;

    FVector Location = GetActorLocation();
    FVector Velocity = GetVelocity();
    FRotator Rotation = GetActorRotation();

    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    int32 MyId = NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;

    // ���� ���ڿ� ��ȯ
    FString StateString = GetStateString(CurrentState);
	FString ActionString = GetActionString(CurrentAction);

    // ��Ʈ��ũ ���� ����
    FString NetworkStatus = TEXT("Disconnected");
    float Ping = 0.0f;

    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkStatus = TEXT("Connected");
        Ping = NetworkManager->GetPingTime();
    }

    // �Է� ���� ����
    FString MoveInfo = FString::Printf(TEXT("Input: F=%.2f R=%.2f"), ForwardInput, RightInput);

    // ��ư ���� ����
    TArray<FString> ActiveButtons;
    if (bRunPressed) ActiveButtons.Add(TEXT("RUN"));
    if (bJumpPressed) ActiveButtons.Add(TEXT("JUMP"));
    if (bAttackPressed) ActiveButtons.Add(TEXT("ATTACK"));
    if (bDefendPressed) ActiveButtons.Add(TEXT("DEFEND"));

    FString ButtonString = ActiveButtons.Num() > 0 ?
        FString::Printf(TEXT("Actions: %s"), *FString::Join(ActiveButtons, TEXT("|"))) :
        TEXT("Actions: None");

    // �ӵ� �м�
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
    float SpeedPercentage = MaxSpeed > 0 ? (Speed2D / MaxSpeed) * 100.0f : 0.0f;

    // ���� ����� �ؽ�Ʈ ����
    FString DebugText = FString::Printf(
        TEXT("=== LOCAL PLAYER [ID:%d] ===\n")
        TEXT("Network: %s | Ping: %.0fms\n")
        TEXT("State: %s\n")
		TEXT("Action: %s\n")
        TEXT("Position: (%.1f, %.1f, %.1f)\n")
        TEXT("Target: (%.1f, %.1f, %.1f)\n")
        TEXT("Distance to Target: %.1f units\n")
        TEXT("Speed: %.1f/%.0f (%.0f%%)\n")
        TEXT("Vertical: %.1f\n")
        TEXT("%s\n")
        TEXT("%s\n")
        TEXT("Rotation: P=%.1f Y=%.1f R=%.1f\n")
        TEXT("Camera: P=%.1f Y=%.1f"),
        MyId, *NetworkStatus, Ping,
        *StateString,
		*ActionString,
        Location.X, Location.Y, Location.Z,
        TargetLocation.X, TargetLocation.Y, TargetLocation.Z,
        TargetLocation.IsZero() ? 0.0f : FVector::Dist(Location, TargetLocation),
        Speed2D, MaxSpeed, SpeedPercentage,
        Velocity.Z,
        *MoveInfo,
        *ButtonString,
        Rotation.Pitch, Rotation.Yaw, Rotation.Roll,
        PitchInput, YawInput
    );

    // ����� ǥ�� ��ġ �� ����
    FVector TextLocation = Location + FVector(0, 0, 150);
    FColor TextColor = GetDebugColor();

    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, TextColor, 0.0f, true);

    // �̵� ���� �ð�ȭ
    DrawMovementVectors(Location, Velocity);

    // ��ǥ ��ġ �ð�ȭ (���� �÷��̾�� ����)
    if (!TargetLocation.IsZero() && !bShowDebugInfo)
    {
        // ��ǥ ��ġ ǥ�� (�Ķ� ��ü)
        DrawDebugSphere(GetWorld(), TargetLocation, 20.0f, 8, FColor::Blue, false, 0.0f, 0, 2.0f);

        // ����-��ǥ ��ġ ���ἱ
        float TargetDistance = FVector::Dist(Location, TargetLocation);
        if (TargetDistance > 5.0f)
        {
            FColor LineColor = TargetDistance > 50.0f ? FColor::Red : FColor::Green;
            DrawDebugLine(GetWorld(), Location, TargetLocation, LineColor, false, 0.0f, 0, 2.0f);
        }
    }
}

// ���� �Լ���
FString AMyCharacter::GetStateString(EPlayerState State) const
{
    switch (State)
    {
    case EPlayerState::IDLE: return TEXT("IDLE");
    case EPlayerState::WALKING: return TEXT("WALKING");
    case EPlayerState::RUNNING: return TEXT("RUNNING");
    case EPlayerState::JUMPING: return TEXT("JUMPING");
    case EPlayerState::DEAD: return TEXT("DEAD");
    default: return TEXT("UNKNOWN");
    }
}

FString AMyCharacter::GetActionString(EPlayerAction Action) const
{
    switch (Action)
    {
    case EPlayerAction::NONE: return TEXT("NONE");
    case EPlayerAction::ATTACK: return TEXT("ATTACK");
    case EPlayerAction::DEFEND: return TEXT("DEFEND");
    default: return TEXT("UNKNOWN");
    }
}

FString AMyCharacter::GetPlayerTypeString() const
{
    return TEXT("Local");  // �׻� ���� �÷��̾�
}

FColor AMyCharacter::GetDebugColor() const
{
    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();

    if (NetworkManager && NetworkManager->IsConnected())
        return FColor::Cyan;    // ����� ���� �÷��̾�: û�ϻ�
    else
        return FColor::Red;     // ���� ����: ������
}

void AMyCharacter::DrawMovementVectors(const FVector& Location, const FVector& Velocity) const
{
    if (!bShowDebugInfo) return;

    // �ӵ� ���� (�ʷ� ȭ��ǥ)
    if (!Velocity.IsZero())
    {
        FVector VelocityEnd = Location + (Velocity.GetSafeNormal() * 100.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, VelocityEnd, 20.0f, FColor::Green, false, 0.0f, 0, 3.0f);
    }

    // �Է� ���� ���� (�Ķ� ȭ��ǥ)
    if (FMath::Abs(ForwardInput) > 0.01f || FMath::Abs(RightInput) > 0.01f)
    {
        FVector InputDirection = FVector(ForwardInput, RightInput, 0).GetSafeNormal();
        FVector InputEnd = Location + (InputDirection * 80.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, InputEnd, 15.0f, FColor::Blue, false, 0.0f, 0, 2.0f);
    }
}