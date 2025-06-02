// MyCharacter.cpp - 로컬 플레이어 전용으로 정리
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

    // 스프링암 컴포넌트 설정
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bDoCollisionTest = true;
    SpringArm->bInheritPitch = true;
    SpringArm->bInheritYaw = true;
    SpringArm->bInheritRoll = false;

    // 카메라 컴포넌트 설정
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // 캐릭터 이동 설정
    GetCharacterMovement()->bOrientRotationToMovement = bAlwaysFaceMovementDirection;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, MovementRotationRate, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->GravityScale = 1.0f;

    // 컨트롤러 회전 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = !bAlwaysFaceMovementDirection;
    bUseControllerRotationRoll = false;

    // 초기 상태 설정
    CurrentState = EPlayerState::IDLE;

	// 초기 액션 설정
	CurrentAction = EPlayerAction::NONE;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Enhanced Input 설정 (로컬 플레이어만)
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

    UE_LOG(LogTemp, Log, TEXT("Local player spawned: %s"), *GetName());
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // 로컬 플레이어만 입력 바인딩
    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // 이동 입력
        if (MoveAction)
        {
            Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
            Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::Move);
        }

        // 달리기 입력
        if (RunAction)
        {
            Input->BindAction(RunAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartRun);
            Input->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
        }

        // 점프 입력
        if (JumpAction)
        {
            Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::StartJump);
            Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);
        }

        // 공격 입력
        if (AttackAction)
        {
            Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
        }

        // 방어 입력
        if (DefendAction)
        {
            Input->BindAction(DefendAction, ETriggerEvent::Triggered, this, &AMyCharacter::StartDefend);
            Input->BindAction(DefendAction, ETriggerEvent::Completed, this, &AMyCharacter::StopDefend);
        }

        // 마우스 룩 입력
        if (LookAction)
        {
            Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        }
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 로컬 플레이어는 입력을 서버로 전송
    SendInputToServer();

    // 서버에서 받은 위치로 이동 (원격 플레이어와 동일)
    InterpolateToServerPosition(DeltaTime);
    
    // 디버그 정보 표시
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

        // 입력값만 저장 (서버 전송용) - 즉시 이동하지 않음
        ForwardInput = Movement.Y;
        RightInput = Movement.X;
        PitchInput = Rotation.Pitch;
        YawInput = Rotation.Yaw;
        RollInput = Rotation.Roll;

        // AddMovementInput 제거 - 서버 응답을 기다림
        // 로컬 예측 이동 없음, 순수하게 서버 위치로만 이동
    }
}

void AMyCharacter::StartRun(const FInputActionValue& Value)
{
    // 입력 상태만 변경 - 실제 속도는 서버에서 결정
    bRunPressed = true;
    GetCharacterMovement()->MaxWalkSpeed = 1000.0f;

}

void AMyCharacter::StopRun(const FInputActionValue& Value)
{
    // 입력 상태만 변경 - 실제 속도는 서버에서 결정
    bRunPressed = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // 기본 속도로 되돌림
}

void AMyCharacter::StartJump(const FInputActionValue& Value)
{
    // 입력 상태만 변경 - 실제 점프는 서버에서 처리
    bJumpPressed = true;

	Jump(); // 점프 애니메이션 재생 (로컬에서 즉시 반응)
}

void AMyCharacter::StopJump(const FInputActionValue& Value)
{
    // 입력 상태만 변경
    bJumpPressed = false;

	StopJumping(); // 점프 애니메이션 중지 (로컬에서 즉시 반응)
}

void AMyCharacter::Attack(const FInputActionValue& Value)
{
    // 입력 상태만 변경 - 실제 애니메이션은 서버에서 결정
    bAttackPressed = true;

    if (AttackMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Play(AttackMontage);
        }
	}
    //// 공격 상태 리셋 타이머 (입력 지속 시간 제한)
    //GetWorld()->GetTimerManager().SetTimer(AttackResetHandle, [this]()
    //    {    
    //        bAttackPressed = false;
    //    }, AttackMontageDuration, false);

}

void AMyCharacter::StartDefend(const FInputActionValue& Value)
{
    // 입력 상태만 변경 - 실제 애니메이션은 서버에서 결정
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
    // 입력 상태만 변경
    bDefendPressed = false;

    if (DefendMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Stop(0.2f, DefendMontage); // 애니메이션 중지
        }
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();

    // 마우스 입력으로 카메라 회전
    AddControllerYawInput(LookAxis.X);
    AddControllerPitchInput(LookAxis.Y);

    // 회전값 업데이트 (서버 전송용)
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

        // 서버의 Vec3/Rot3 구조체로 변환
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

    // 입력 전송 빈도 제한 (60Hz)
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastInputSendTime < (1.0f / InputSendRate))
    {
        return;
    }

    // 입력이 변경되었거나 주기적으로 전송
    if (HasInputChanged() || (CurrentTime - LastInputSendTime > 0.5f))
    {
        NetworkManager->SendPlayerInput(
            ForwardInput, RightInput,
            PitchInput, YawInput, RollInput,
            bRunPressed, bJumpPressed, bAttackPressed, bDefendPressed
        );

        LastInputSendTime = CurrentTime;

        // 이전 입력값 저장
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
    //서버에서 받은 권한 있는 데이터로 목표 설정 (원격 플레이어와 동일)
    TargetLocation = NewTransform.GetLocation();
    TargetRotation = NewTransform.GetRotation().Rotator();
    TargetVelocity = NetworkVelocity;

    // 초기 위치 설정 (텔레포트)
    //if (!bInitialPositionSet)
    //{
    //    SetActorLocation(TargetLocation);
    //    SetActorRotation(TargetRotation);
    //    GetCharacterMovement()->Velocity = TargetVelocity;
    //    bInitialPositionSet = true;

    //    UE_LOG(LogTemp, Log, TEXT("Local player %d initial position set: (%.1f, %.1f, %.1f)"),
    //        PlayerId, TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
    //}

    // 상태 업데이트
    EPlayerState PreviousState = CurrentState;
    CurrentState = NewState;

    // 상태별 처리 (서버에서 결정된 상태에 따라)
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

    // 액션 처리
    EPlayerAction PreviousAction = CurrentAction;
    CurrentAction = NewAction;

    if (PreviousAction != CurrentAction)
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

        switch (CurrentAction)
        {
        case EPlayerAction::ATTACK:
            if (AttackMontage && AnimInstance)
                AnimInstance->Montage_Play(AttackMontage);
            break;
        case EPlayerAction::DEFEND:
            if (DefendMontage && AnimInstance)
                AnimInstance->Montage_Play(DefendMontage);
            break;
        default:
            break;
        }
    }
}

void AMyCharacter::InterpolateToServerPosition(float DeltaTime)
{
    if (TargetLocation.IsZero()) return;

    // 위치 보간 (원격 플레이어와 동일한 방식)
    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
    SetActorLocation(NewLocation);

    // 회전 보간
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
    SetActorRotation(NewRotation);

    // 속도 보간 (부드러운 애니메이션을 위해)
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
	const float roatonThreshold = 0.1f; // 회전 입력 변화 감지 임계값

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
    if (!bShowDebugInfo) return;

    FVector Location = GetActorLocation();
    FVector Velocity = GetVelocity();
    FRotator Rotation = GetActorRotation();

    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    int32 MyId = NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;

    // 상태 문자열 변환
    FString StateString = GetStateString(CurrentState);
	FString ActionString = GetActionString(CurrentAction);

    // 네트워크 상태 정보
    FString NetworkStatus = TEXT("Disconnected");
    float Ping = 0.0f;

    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkStatus = TEXT("Connected");
        Ping = NetworkManager->GetPingTime();
    }

    // 입력 상태 정보
    FString MoveInfo = FString::Printf(TEXT("Input: F=%.2f R=%.2f"), ForwardInput, RightInput);

    // 버튼 상태 정보
    TArray<FString> ActiveButtons;
    if (bRunPressed) ActiveButtons.Add(TEXT("RUN"));
    if (bJumpPressed) ActiveButtons.Add(TEXT("JUMP"));
    if (bAttackPressed) ActiveButtons.Add(TEXT("ATTACK"));
    if (bDefendPressed) ActiveButtons.Add(TEXT("DEFEND"));

    FString ButtonString = ActiveButtons.Num() > 0 ?
        FString::Printf(TEXT("Actions: %s"), *FString::Join(ActiveButtons, TEXT("|"))) :
        TEXT("Actions: None");

    // 속도 분석
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
    float SpeedPercentage = MaxSpeed > 0 ? (Speed2D / MaxSpeed) * 100.0f : 0.0f;

    // 종합 디버그 텍스트 생성
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

    // 디버그 표시 위치 및 색상
    FVector TextLocation = Location + FVector(0, 0, 150);
    FColor TextColor = GetDebugColor();

    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, TextColor, 0.0f, true);

    // 이동 벡터 시각화
    DrawMovementVectors(Location, Velocity);

    // 목표 위치 시각화 (원격 플레이어와 동일)
    if (!TargetLocation.IsZero() && bShowDebugInfo)
    {
        // 목표 위치 표시 (파란 구체)
        DrawDebugSphere(GetWorld(), TargetLocation, 20.0f, 8, FColor::Blue, false, 0.0f, 0, 2.0f);

        // 현재-목표 위치 연결선
        float TargetDistance = FVector::Dist(Location, TargetLocation);
        if (TargetDistance > 5.0f)
        {
            FColor LineColor = TargetDistance > 50.0f ? FColor::Red : FColor::Green;
            DrawDebugLine(GetWorld(), Location, TargetLocation, LineColor, false, 0.0f, 0, 2.0f);
        }
    }
}

// 헬퍼 함수들
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
    return TEXT("Local");  // 항상 로컬 플레이어
}

FColor AMyCharacter::GetDebugColor() const
{
    UNetworkManager* NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();

    if (NetworkManager && NetworkManager->IsConnected())
        return FColor::Cyan;    // 연결된 로컬 플레이어: 청록색
    else
        return FColor::Red;     // 연결 끊김: 빨간색
}

void AMyCharacter::DrawMovementVectors(const FVector& Location, const FVector& Velocity) const
{
    if (!bShowDebugInfo) return;

    // 속도 벡터 (초록 화살표)
    if (!Velocity.IsZero())
    {
        FVector VelocityEnd = Location + (Velocity.GetSafeNormal() * 100.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, VelocityEnd, 20.0f, FColor::Green, false, 0.0f, 0, 3.0f);
    }

    // 입력 방향 벡터 (파랑 화살표)
    if (FMath::Abs(ForwardInput) > 0.01f || FMath::Abs(RightInput) > 0.01f)
    {
        FVector InputDirection = FVector(ForwardInput, RightInput, 0).GetSafeNormal();
        FVector InputEnd = Location + (InputDirection * 80.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, InputEnd, 15.0f, FColor::Blue, false, 0.0f, 0, 2.0f);
    }
}