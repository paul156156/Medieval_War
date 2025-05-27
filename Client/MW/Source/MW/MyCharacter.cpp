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
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;        // ������ ���� (500.0f)
    GetCharacterMovement()->JumpZVelocity = 600.0f;       // ������ ���� (600.0f)
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->GravityScale = 1.0f;          // ���� �߷�(980)�� UE �⺻�� ����

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
            // ����/����
            const FVector ForwardDirection = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::X);
            AddMovementInput(ForwardDirection, Movement.Y);

            // ��/��
            const FVector RightDirection = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::Y);
            AddMovementInput(RightDirection, Movement.X);
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

    FString DebugText = FString::Printf(TEXT("ID: %d | %s\nPos: (%.1f, %.1f, %.1f)\nSpeed: %.1f\nInput: F=%.2f R=%.2f"),
        MyId,
        *StateString,
        Location.X, Location.Y, Location.Z,
        Velocity.Size(),
        ForwardInput, RightInput
    );

    FVector TextLocation = Location + FVector(0, 0, 120);
    FColor TextColor = bIsRemoteControlled ? FColor::Orange : FColor::Cyan;

    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, TextColor, 0.0f, true);
}