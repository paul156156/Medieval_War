// MyCharacter.cpp
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

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // �������� ������Ʈ ����
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = true;

    // ī�޶� ������Ʈ ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // ĳ���� �̵� ���� (������ ������ ������ ����)
    GetCharacterMovement()->bOrientRotationToMovement = bAlwaysFaceMovementDirection;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, MovementRotationRate, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->GravityScale = 1.0f;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = !bAlwaysFaceMovementDirection;  // �̵� ������ ������ ���� ���� ��Ʈ�ѷ� ȸ�� ���
    bUseControllerRotationRoll = false;

    // �������� ���� (�� �ڿ������� ī�޶� ������ ����)
    SpringArm->bDoCollisionTest = true;
    SpringArm->bInheritPitch = true;
    SpringArm->bInheritYaw = true;
    SpringArm->bInheritRoll = false;

    // �ʱ� ���� ����
    CurrentState = EPlayerState::IDLE;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // ���� �÷��̾ �Է� ���� �� ���� �˸�
    if (!bIsRemoteControlled)
    {
        NotifySpawn();

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
    }
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // ���� ����Ǵ� ĳ���ʹ� �Է��� ���� ����
    if (bIsRemoteControlled)
    {
        return;
    }

    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // �̵� �Է�
        if (MoveAction)
        {
            Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
            Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::Move);
        }

        // �޸��� �Է�
        if (RunAction)
        {
            Input->BindAction(RunAction, ETriggerEvent::Started, this, &AMyCharacter::StartRun);
            Input->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
        }

        // ���� �Է�
        if (JumpAction)
        {
            Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::StartJump);
            Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);
        }

        // ���� �Է�
        if (AttackAction)
        {
            Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
        }

        // ���콺 �� �Է�
        if (LookAction)
        {
            Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        }
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ���� ĳ���ʹ� ���� ó��
    if (bIsRemoteControlled)
    {
        InterpolateRemoteMovement(DeltaTime);
    }
    // ���� �÷��̾�� �Է��� ������ ����
    else
    {
        SendInputToServer();
    }

    // ����� ���� ǥ��
    if (bShowDebugInfo)
    {
        DisplayDebugInfo();
    }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    FVector2D Movement = Value.Get<FVector2D>();

    if (Controller)
    {
        FRotator Rotation = Controller->GetControlRotation();

        // �Է°� ���� (���� ���ۿ�)
        ForwardInput = Movement.Y;
        RightInput = Movement.X;
        PitchInput = Rotation.Pitch;
        YawInput = Rotation.Yaw;
        RollInput = Rotation.Roll;

        // ���� ������ ó�� (��� �������� ����)
        if (!Movement.IsZero())
        {
            // ī�޶� ���� �̵� ���� ���
            const FVector ForwardDirection = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::X);
            const FVector RightDirection = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::Y);

            // �̵� �Է� ����
            AddMovementInput(ForwardDirection, Movement.Y);
            AddMovementInput(RightDirection, Movement.X);

            // bAlwaysFaceMovementDirection�� false�� ���� ���� ȸ��
            if (!bAlwaysFaceMovementDirection)
            {
                // ���� ��ǥ�迡�� �̵� ���� ���
                FVector WorldMovementDirection = (ForwardDirection * Movement.Y) + (RightDirection * Movement.X);
                WorldMovementDirection.Normalize();

                if (!WorldMovementDirection.IsZero())
                {
                    FRotator NewTargetRotation = WorldMovementDirection.Rotation();
                    SetActorRotation(FMath::RInterpTo(GetActorRotation(), NewTargetRotation, GetWorld()->GetDeltaSeconds(), MovementRotationRate / 100.0f));
                }
            }
        }
    }
}

void AMyCharacter::StartRun(const FInputActionValue& Value)
{
    // ���� ������ ���� (500 * 2 = 1000)
    GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
    bRunPressed = true;
}

void AMyCharacter::StopRun(const FInputActionValue& Value)
{
    // ���� �⺻ �ӵ��� ����
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    bRunPressed = false;
}

void AMyCharacter::StartJump(const FInputActionValue& Value)
{
    Jump();
    bJumpPressed = true;
}

void AMyCharacter::StopJump(const FInputActionValue& Value)
{
    StopJumping();
    bJumpPressed = false;
}

void AMyCharacter::Attack(const FInputActionValue& Value)
{
    bAttackPressed = true;

    // ���� �ִϸ��̼� ���
    if (AttackMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Play(AttackMontage);
        }
    }

    // ���� ���� ���� Ÿ�̹�
    GetWorld()->GetTimerManager().SetTimer(AttackResetHandle, [this]()
        {
            bAttackPressed = false;
        }, AttackMontageDuration, false);
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
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
    if (HasInputChanged() || (CurrentTime - LastInputSendTime > 0.1f))
    {
        // �� ���� InputPacket ������ ���� ����
        NetworkManager->SendPlayerInput(
            ForwardInput, RightInput,
            PitchInput, YawInput, RollInput,
            bRunPressed, bJumpPressed, bAttackPressed
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
    }
}

void AMyCharacter::UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState)
{
    // ��ǥ ��ġ �� ȸ�� ����
    TargetLocation = NewTransform.GetLocation();
    TargetRotation = NewTransform.GetRotation().Rotator();
    TargetVelocity = NetworkVelocity;

    // ���� ������Ʈ
    EPlayerState PreviousState = CurrentState;
    CurrentState = NewState;

    // �ʱ� ��ġ ���� (�ڷ���Ʈ)
    if (!bInitialPositionSet)
    {
        SetActorLocation(TargetLocation);
        SetActorRotation(TargetRotation);
        bInitialPositionSet = true;
    }

    // ���º� ó��
    switch (NewState)
    {
    case EPlayerState::ATTACKING:
        if (PreviousState != EPlayerState::ATTACKING && AttackMontage)
        {
            if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
            {
                AnimInstance->Montage_Play(AttackMontage);
            }
        }
        break;

    case EPlayerState::JUMPING:
        if (GetCharacterMovement()->MovementMode != MOVE_Falling)
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Falling);
        }
        break;

    case EPlayerState::RUNNING:
        GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
        break;

    case EPlayerState::WALKING:
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
        if (GetCharacterMovement()->MovementMode != MOVE_Walking)
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        }
        break;

    case EPlayerState::IDLE:
    default:
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
        if (GetCharacterMovement()->MovementMode != MOVE_Walking)
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        }
        break;
    }
}

void AMyCharacter::InterpolateRemoteMovement(float DeltaTime)
{
    // ��ġ ����
    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
    SetActorLocation(NewLocation);

    // ȸ�� ����
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
    SetActorRotation(NewRotation);

    // �ӵ� ���� (�ε巯�� �ִϸ��̼��� ����)
    FVector CurrentVelocity = GetVelocity();
    FVector NewVelocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, DeltaTime, VelocityInterpSpeed);
    GetCharacterMovement()->Velocity = NewVelocity;
}

bool AMyCharacter::HasInputChanged() const
{
    const float Threshold = 0.01f; // �Է� ��ȭ �Ӱ谪

    return (FMath::Abs(ForwardInput - PreviousForwardInput) > Threshold ||
        FMath::Abs(RightInput - PreviousRightInput) > Threshold ||
        FMath::Abs(PitchInput - PreviousPitchInput) > 1.0f ||
        FMath::Abs(YawInput - PreviousYawInput) > 1.0f ||
        bRunPressed != bPreviousRunPressed ||
        bJumpPressed != bPreviousJumpPressed ||
        bAttackPressed != bPreviousAttackPressed);
}

void AMyCharacter::DisplayDebugInfo()
{
    if (!bShowDebugInfo) return;

    FVector Location = GetActorLocation();
    FVector Velocity = GetVelocity();
    FRotator Rotation = GetActorRotation();

    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    int32 MyId = NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;

    // ���� ���ڿ� ��ȯ
    FString StateString;
    switch (CurrentState)
    {
    case EPlayerState::IDLE:
        StateString = TEXT("IDLE");
        break;
    case EPlayerState::WALKING:
        StateString = TEXT("WALKING");
        break;
    case EPlayerState::RUNNING:
        StateString = TEXT("RUNNING");
        break;
    case EPlayerState::JUMPING:
        StateString = TEXT("JUMPING");
        break;
    case EPlayerState::ATTACKING:
        StateString = TEXT("ATTACKING");
        break;
    default:
        StateString = TEXT("UNKNOWN");
        break;
    }

    // ��Ʈ��ũ ���� ����
    FString NetworkStatus = TEXT("Disconnected");
    FString PlayerType = TEXT("Unknown");
    float Ping = 0.0f;

    if (NetworkManager)
    {
        NetworkStatus = NetworkManager->IsConnected() ? TEXT("Connected") : TEXT("Disconnected");
        Ping = NetworkManager->GetPingTime();
    }

    if (bIsLocalPlayer)
        PlayerType = TEXT("Local");
    else if (bIsRemoteControlled)
        PlayerType = TEXT("Remote");

    // �Է� ���� ����
    FString InputInfo = FString::Printf(TEXT("Input: F=%.2f R=%.2f"), ForwardInput, RightInput);

    // ��ư ���� ����
    TArray<FString> ButtonStates;
    if (bRunPressed) ButtonStates.Add(TEXT("RUN"));
    if (bJumpPressed) ButtonStates.Add(TEXT("JUMP"));
    if (bAttackPressed) ButtonStates.Add(TEXT("ATTACK"));

    FString ButtonString = ButtonStates.Num() > 0 ?
        FString::Printf(TEXT("Buttons: %s"), *FString::Join(ButtonStates, TEXT("|"))) :
        TEXT("Buttons: None");

    // ȸ�� ����
    FString RotationInfo = FString::Printf(TEXT("Rot: P=%.1f Y=%.1f R=%.1f"),
        Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

    // �ӵ� �м�
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float VerticalSpeed = Velocity.Z;

    // �ִ� �ӵ��� ��
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
    float SpeedPercentage = MaxSpeed > 0 ? (Speed2D / MaxSpeed) * 100.0f : 0.0f;

    // ���� ����� �ؽ�Ʈ ����
    FString DebugText = FString::Printf(
        TEXT("=== PLAYER DEBUG INFO ===\n")
        TEXT("ID: %d | Type: %s\n")
        TEXT("Network: %s | Ping: %.0fms\n")
        TEXT("State: %s\n")
        TEXT("Position: (%.1f, %.1f, %.1f)\n")
        TEXT("Speed: %.1f/%.1f (%.0f%%)\n")
        TEXT("V-Speed: %.1f | 2D-Speed: %.1f\n")
        TEXT("%s\n")
        TEXT("%s\n")
        TEXT("%s\n")
        TEXT("=== CONTROLS ===\n")
        TEXT("Camera: P=%.1f Y=%.1f"),
        MyId, *PlayerType,
        *NetworkStatus, Ping,
        *StateString,
        Location.X, Location.Y, Location.Z,
        Speed2D, MaxSpeed, SpeedPercentage,
        VerticalSpeed, Speed2D,
        *InputInfo,
        *ButtonString,
        *RotationInfo,
        PitchInput, YawInput
    );

    // �ؽ�Ʈ ��ġ (ĳ���� �������� �� �ø�)
    FVector TextLocation = Location + FVector(0, 0, 150);

    // �÷��̾� Ÿ�Կ� ���� ���� ����
    FColor TextColor = FColor::White;
    if (bIsLocalPlayer)
        TextColor = FColor::Cyan;      // ���� �÷��̾�: û�ϻ�
    else if (bIsRemoteControlled)
        TextColor = FColor::Orange;    // ���� �÷��̾�: ��Ȳ��
    else
        TextColor = FColor::Yellow;    // ��Ÿ: �����

    // ��Ʈ��ũ ���¿� ���� ���� ����
    if (NetworkManager && !NetworkManager->IsConnected())
        TextColor = FColor::Red;       // ���� ����: ������

    // 3D ���忡 �ؽ�Ʈ ǥ��
    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, TextColor, 0.0f, true);

    // �߰�: �̵� ���� �ð�ȭ (ȭ��ǥ�� ǥ��)
    if (bShowDebugInfo && !Velocity.IsZero())
    {
        FVector VelocityEnd = Location + (Velocity.GetSafeNormal() * 100.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, VelocityEnd, 20.0f, FColor::Green, false, 0.0f, 0, 3.0f);
    }

    // �߰�: �Է� ���� �ð�ȭ
    if (bShowDebugInfo && (FMath::Abs(ForwardInput) > 0.01f || FMath::Abs(RightInput) > 0.01f))
    {
        FVector InputDirection = FVector(ForwardInput, RightInput, 0).GetSafeNormal();
        FVector InputEnd = Location + (InputDirection * 80.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, InputEnd, 15.0f, FColor::Blue, false, 0.0f, 0, 2.0f);
    }
}