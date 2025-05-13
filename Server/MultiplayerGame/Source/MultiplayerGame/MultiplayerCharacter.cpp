// MultiplayerCharacter.cpp
// ���� �� �÷��̾� ĳ���� Ŭ���� ����

#include "MultiplayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

AMultiplayerCharacter::AMultiplayerCharacter()
{
    // �� ������ Tick Ȱ��ȭ
    PrimaryActorTick.bCanEverTick = true;

    // ĸ�� ������Ʈ ����
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // ȸ�� ���� - ī�޶� �������� ȸ������ �ʵ��� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ĳ���� �����Ʈ ������Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // ������ �� ������Ʈ ���� (ī�޶� ��)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // ī�޶� ������Ʈ ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // �⺻ ���� �ʱ�ȭ
    PlayerId = -1;
    bIsLocalPlayer = false;
    CurrentState = EPlayerState::IDLE;
    ForwardInput = 0.0f;
    RightInput = 0.0f;
    ControlRotationYaw = 0.0f;
    LastStateChangeTime = 0.0f;
    AttackAnimDuration = 1.0f;
}

void AMultiplayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    // �ʱ� ���� ����
    SetCurrentState(EPlayerState::IDLE);

    // Enhanced Input ���� ���ؽ�Ʈ �߰�
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                // ���� ���ؽ�Ʈ �ε� �� �߰�
                if (UInputMappingContext* LoadedContext = DefaultMappingContext.LoadSynchronous())
                {
                    Subsystem->AddMappingContext(LoadedContext, 0);
                }
            }
        }
    }
}

void AMultiplayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // ���� �Է� ���� �ڵ� ����
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Enhanced Input Component�� ĳ����
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // �̵�
        if (UInputAction* LoadedMoveAction = MoveAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedMoveAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::Move);
            EnhancedInputComponent->BindAction(LoadedMoveAction, ETriggerEvent::Completed, this, &AMultiplayerCharacter::StopMove);
        }


        // ���� ȸ��
        if (UInputAction* LoadedLookAction = LookAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedLookAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::Look);
        }

        // ����
        if (UInputAction* LoadedJumpAction = JumpAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedJumpAction, ETriggerEvent::Started, this, &AMultiplayerCharacter::StartJump);
            EnhancedInputComponent->BindAction(LoadedJumpAction, ETriggerEvent::Completed, this, &AMultiplayerCharacter::StopJump);
        }

        // ����
        if (UInputAction* LoadedAttackAction = AttackAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedAttackAction, ETriggerEvent::Started, this, &AMultiplayerCharacter::Attack);
        }
    }
}

void AMultiplayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ���� �÷��̾ �ִϸ��̼� ���� ������Ʈ
    if (bIsLocalPlayer)
    {
        UpdateAnimationState();

        // ��Ʈ�ѷ��� �ִ� ��� ��Ʈ�� ȸ�� ������Ʈ
        if (Controller)
        {
            ControlRotationYaw = Controller->GetControlRotation().Yaw;
        }
    }
}

void AMultiplayerCharacter::Move(const FInputActionValue& Value)
{
    //UE_LOG(LogTemp, Warning, TEXT("Move Called! bIsLocalPlayer: %s"), bIsLocalPlayer ? TEXT("True") : TEXT("False"));

    if (!bIsLocalPlayer || !Controller) return;

    // 2D ���� �� ��������
    const FVector2D MovementVector = Value.Get<FVector2D>();

    // ���� ȸ�� ���� ��������
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // ���� ���� ���
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    // ���� ���� ���
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // �̵� �Է� �߰�
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);

    // �Է°� ����
    ForwardInput = MovementVector.Y;
    RightInput = MovementVector.X;
}

void AMultiplayerCharacter::StopMove(const FInputActionValue& Value)
{
	if (!bIsLocalPlayer) return;
	// �̵� �Է��� ����
	ForwardInput = 0.0f;
	RightInput = 0.0f;
	// ���� ���¿� ���� �ִϸ��̼� ���� ������Ʈ
	//UpdateAnimationState();    if (CurrentState != EPlayerState::ATTACKING && CurrentState != EPlayerState::JUMPING)
    //{
        UpdateAnimationState();
    //}
}

void AMultiplayerCharacter::Look(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    // 2D ���� �� ��������
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    // ȸ�� �Է� �߰�
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);

    // ��Ʈ�ѷ� ȸ�� ����
    if (Controller)
    {
        ControlRotationYaw = Controller->GetControlRotation().Yaw;
    }
}

void AMultiplayerCharacter::StartJump(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    Jump();
    SetCurrentState(EPlayerState::JUMPING);
}

void AMultiplayerCharacter::StopJump(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    StopJumping();
}

void AMultiplayerCharacter::Attack(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    // ���� ���·� ����
    SetCurrentState(EPlayerState::ATTACKING);

    // ���� �ִϸ��̼� ���
    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            AnimInstance->Montage_Play(AttackMontage, 1.0f);
        }
    }

    // ���� �Ϸ� Ÿ�̸� ����
    FTimerManager& TimerManager = GetWorldTimerManager();
    TimerManager.ClearTimer(AttackTimerHandle);
    TimerManager.SetTimer(
        AttackTimerHandle,
        this,
        &AMultiplayerCharacter::OnAttackFinished,
        AttackAnimDuration,
        false
    );
}

void AMultiplayerCharacter::OnAttackFinished()
{
    // ���� �Ϸ� �� ���� ����
    if (CurrentState == EPlayerState::ATTACKING)
    {
        // �̵� ���̸� WALKING, �ƴϸ� IDLE�� ����
        if (GetCharacterMovement()->Velocity.Size() > 10.0f)
        {
            SetCurrentState(EPlayerState::WALKING);
        }
        else
        {
            SetCurrentState(EPlayerState::IDLE);
        }
    }
}

void AMultiplayerCharacter::SetCurrentState(EPlayerState NewState)
{
    if (CurrentState != NewState)
    {
        CurrentState = NewState;
        LastStateChangeTime = GetWorld()->GetTimeSeconds();

        // ���� ���濡 ���� �߰� ���� ���� ����
        UE_LOG(LogTemp, Log, TEXT("Player ID %d State Changed: %d"), PlayerId, static_cast<int32>(CurrentState));
    }
}

void AMultiplayerCharacter::UpdateAnimationState()
{
    // ���� ���¿� ���� �ִϸ��̼� ������Ʈ
    if (CurrentState != EPlayerState::ATTACKING && CurrentState != EPlayerState::JUMPING)
    {
        // �̵� ���̸� WALKING, �ƴϸ� IDLE�� ����
        if (GetCharacterMovement()->Velocity.Size() > 10.0f)
        {
            SetCurrentState(EPlayerState::WALKING);
        }
        else
        {
            SetCurrentState(EPlayerState::IDLE);
        }
    }
    else if (CurrentState == EPlayerState::JUMPING)
    {
        // ���� �� �����ߴ��� Ȯ��
        if (GetCharacterMovement()->IsFalling() == false)
        {
            // �̵� ���̸� WALKING, �ƴϸ� IDLE�� ����
            if (GetCharacterMovement()->Velocity.Size() > 10.0f)
            {
                SetCurrentState(EPlayerState::WALKING);
            }
            else
            {
                SetCurrentState(EPlayerState::IDLE);
            }
        }
    }
}

void AMultiplayerCharacter::UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateFromNetwork Called: ID=%d, IsLocal=%d, NewPos=(%f, %f, %f)"),
        GetPlayerId(), IsLocalPlayer(),
        NewTransform.GetLocation().X, NewTransform.GetLocation().Y, NewTransform.GetLocation().Z);

    // ���� �÷��̾ �ƴ� ��쿡�� ��Ʈ��ũ ������Ʈ ����
    if (!bIsLocalPlayer)
    {
        // ��ġ, ȸ�� ������Ʈ
        SetActorTransform(NewTransform);

        // ���� ��ġ�� �� ��ġ �� �Ÿ� ���
        //FVector CurrentLocation = GetActorLocation();
        //FVector NewLocation = NewTransform.GetLocation();
        //float Distance = FVector::Dist(CurrentLocation, NewLocation);

        //UE_LOG(LogTemp, Warning, TEXT("Position Changed: ID=%d, �Ÿ�=%f, ����=(%f, %f, %f), ����ġ=(%f, %f, %f)"),
        //    GetPlayerId(), Distance,
        //    CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z,
        //    NewLocation.X, NewLocation.Y, NewLocation.Z);

        //// ��ġ, ȸ�� ���� ����
        //SetActorLocationAndRotation(
        //    NewTransform.GetLocation(),
        //    NewTransform.GetRotation().Rotator(),
        //    false, // sweep
        //    nullptr,
        //    ETeleportType::TeleportPhysics // ���� �̵� ���� ����
        //);


        // ���� ������Ʈ
        SetCurrentState(NewState);

        // ���¿� ���� �߰� ó��
        if (NewState == EPlayerState::ATTACKING)
        {
            // ���� �ִϸ��̼� ���
            if (AttackMontage)
            {
                UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
                if (AnimInstance)
                {
                    AnimInstance->Montage_Play(AttackMontage, 1.0f);
                }
            }
        }
        else if (NewState == EPlayerState::JUMPING)
        {
            // ���� �ִϸ��̼��� CharacterMovement�� ���� �ڵ����� ó����
            GetCharacterMovement()->SetMovementMode(MOVE_Falling);
        }
    }
}

void AMultiplayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // ���ø����̼� ���� ���
    DOREPLIFETIME(AMultiplayerCharacter, PlayerId);
}