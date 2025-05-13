// MultiplayerCharacter.cpp
// 게임 내 플레이어 캐릭터 클래스 구현

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
    // 매 프레임 Tick 활성화
    PrimaryActorTick.bCanEverTick = true;

    // 캡슐 컴포넌트 설정
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // 회전 설정 - 카메라 방향으로 회전하지 않도록 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 캐릭터 무브먼트 컴포넌트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // 스프링 암 컴포넌트 생성 (카메라 봉)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // 카메라 컴포넌트 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // 기본 변수 초기화
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

    // 초기 상태 설정
    SetCurrentState(EPlayerState::IDLE);

    // Enhanced Input 매핑 컨텍스트 추가
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                // 매핑 컨텍스트 로드 및 추가
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
    // 기존 입력 설정 코드 제거
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Enhanced Input Component로 캐스팅
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 이동
        if (UInputAction* LoadedMoveAction = MoveAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedMoveAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::Move);
            EnhancedInputComponent->BindAction(LoadedMoveAction, ETriggerEvent::Completed, this, &AMultiplayerCharacter::StopMove);
        }


        // 시점 회전
        if (UInputAction* LoadedLookAction = LookAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedLookAction, ETriggerEvent::Triggered, this, &AMultiplayerCharacter::Look);
        }

        // 점프
        if (UInputAction* LoadedJumpAction = JumpAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedJumpAction, ETriggerEvent::Started, this, &AMultiplayerCharacter::StartJump);
            EnhancedInputComponent->BindAction(LoadedJumpAction, ETriggerEvent::Completed, this, &AMultiplayerCharacter::StopJump);
        }

        // 공격
        if (UInputAction* LoadedAttackAction = AttackAction.LoadSynchronous())
        {
            EnhancedInputComponent->BindAction(LoadedAttackAction, ETriggerEvent::Started, this, &AMultiplayerCharacter::Attack);
        }
    }
}

void AMultiplayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 로컬 플레이어만 애니메이션 상태 업데이트
    if (bIsLocalPlayer)
    {
        UpdateAnimationState();

        // 컨트롤러가 있는 경우 컨트롤 회전 업데이트
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

    // 2D 벡터 값 가져오기
    const FVector2D MovementVector = Value.Get<FVector2D>();

    // 현재 회전 방향 가져오기
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // 전방 벡터 계산
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    // 우측 벡터 계산
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // 이동 입력 추가
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);

    // 입력값 저장
    ForwardInput = MovementVector.Y;
    RightInput = MovementVector.X;
}

void AMultiplayerCharacter::StopMove(const FInputActionValue& Value)
{
	if (!bIsLocalPlayer) return;
	// 이동 입력을 멈춤
	ForwardInput = 0.0f;
	RightInput = 0.0f;
	// 현재 상태에 따라 애니메이션 상태 업데이트
	//UpdateAnimationState();    if (CurrentState != EPlayerState::ATTACKING && CurrentState != EPlayerState::JUMPING)
    //{
        UpdateAnimationState();
    //}
}

void AMultiplayerCharacter::Look(const FInputActionValue& Value)
{
    if (!bIsLocalPlayer) return;

    // 2D 벡터 값 가져오기
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    // 회전 입력 추가
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);

    // 컨트롤러 회전 저장
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

    // 공격 상태로 변경
    SetCurrentState(EPlayerState::ATTACKING);

    // 공격 애니메이션 재생
    if (AttackMontage)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            AnimInstance->Montage_Play(AttackMontage, 1.0f);
        }
    }

    // 공격 완료 타이머 설정
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
    // 공격 완료 후 상태 변경
    if (CurrentState == EPlayerState::ATTACKING)
    {
        // 이동 중이면 WALKING, 아니면 IDLE로 변경
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

        // 상태 변경에 따른 추가 로직 구현 가능
        UE_LOG(LogTemp, Log, TEXT("Player ID %d State Changed: %d"), PlayerId, static_cast<int32>(CurrentState));
    }
}

void AMultiplayerCharacter::UpdateAnimationState()
{
    // 현재 상태에 따라 애니메이션 업데이트
    if (CurrentState != EPlayerState::ATTACKING && CurrentState != EPlayerState::JUMPING)
    {
        // 이동 중이면 WALKING, 아니면 IDLE로 변경
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
        // 점프 후 착지했는지 확인
        if (GetCharacterMovement()->IsFalling() == false)
        {
            // 이동 중이면 WALKING, 아니면 IDLE로 변경
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

    // 로컬 플레이어가 아닌 경우에만 네트워크 업데이트 적용
    if (!bIsLocalPlayer)
    {
        // 위치, 회전 업데이트
        SetActorTransform(NewTransform);

        // 현재 위치와 새 위치 간 거리 계산
        //FVector CurrentLocation = GetActorLocation();
        //FVector NewLocation = NewTransform.GetLocation();
        //float Distance = FVector::Dist(CurrentLocation, NewLocation);

        //UE_LOG(LogTemp, Warning, TEXT("Position Changed: ID=%d, 거리=%f, 현재=(%f, %f, %f), 새위치=(%f, %f, %f)"),
        //    GetPlayerId(), Distance,
        //    CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z,
        //    NewLocation.X, NewLocation.Y, NewLocation.Z);

        //// 위치, 회전 강제 적용
        //SetActorLocationAndRotation(
        //    NewTransform.GetLocation(),
        //    NewTransform.GetRotation().Rotator(),
        //    false, // sweep
        //    nullptr,
        //    ETeleportType::TeleportPhysics // 물리 이동 강제 적용
        //);


        // 상태 업데이트
        SetCurrentState(NewState);

        // 상태에 따른 추가 처리
        if (NewState == EPlayerState::ATTACKING)
        {
            // 공격 애니메이션 재생
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
            // 점프 애니메이션은 CharacterMovement를 통해 자동으로 처리됨
            GetCharacterMovement()->SetMovementMode(MOVE_Falling);
        }
    }
}

void AMultiplayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 리플리케이션 변수 등록
    DOREPLIFETIME(AMultiplayerCharacter, PlayerId);
}