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

    // 컴포넌트 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 캐릭터 무브먼트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // 스프링 암 생성
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // 카메라 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // 초기 상태 설정
    CurrentState = EPlayerState::IDLE;
    CurrentForwardValue = 0.0f;
    CurrentRightValue = 0.0f;
    bIsAttacking = false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input 설정
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

    // 매 프레임마다 상태 업데이트
    UpdateCharacterState();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Enhanced Input 바인딩 설정
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 이동 액션 바인딩
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::StopMoving);
        // 시선 액션 바인딩
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        // 점프 액션 바인딩
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJumping);
        // 공격 액션 바인딩
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AMyCharacter::Attack);
    }
}

void AMyCharacter::UpdateCharacterState()
{
    // 이전 상태 저장
    EPlayerState PreviousState = CurrentState;

    // 새 상태 계산
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

    // 상태가 변경되었으면 이벤트 발생
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
        // 앞/뒤 이동
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

        // 좌/우 이동
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
    // 키를 떼면 명시적으로 0 값으로 설정
	CurrentForwardValue = 0.0f;
	CurrentRightValue = 0.0f;

    // 상태 업데이트
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

    // 점프 시 즉시 상태 업데이트
    UpdateCharacterState();
}

void AMyCharacter::StopJumping()
{
    Super::StopJumping();

    // 점프 중단 시 즉시 상태 업데이트
    UpdateCharacterState();
}

void AMyCharacter::Attack()
{
    if (bIsAttacking)
        return; // 이미 공격 중이면 무시

    bIsAttacking = true;

    // 즉시 상태 업데이트
    UpdateCharacterState();

    // 애니메이션 재생
    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            float MontageLength = AnimInstance->Montage_Play(AttackMontage, 1.0f);

            // 몽타주 재생이 끝나면 bIsAttacking을 false로 설정
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    bIsAttacking = false;
                    UpdateCharacterState(); // 공격 종료 시 상태 업데이트
                }, MontageLength, false);
        }
    }
    else
    {
        // 몽타주가 없으면 빠르게 상태 리셋
        bIsAttacking = false;
        UpdateCharacterState();
    }
}