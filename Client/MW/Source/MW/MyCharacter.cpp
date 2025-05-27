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

    // 스프링암 컴포넌트 설정
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 300.0f;
    SpringArm->bUsePawnControlRotation = true;

    // 카메라 컴포넌트 설정
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // 캐릭터 이동 설정 (서버와 동일한 값으로 설정)
    GetCharacterMovement()->bOrientRotationToMovement = bAlwaysFaceMovementDirection;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, MovementRotationRate, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    GetCharacterMovement()->JumpZVelocity = 500.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->GravityScale = 1.0f;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = !bAlwaysFaceMovementDirection;  // 이동 방향을 향하지 않을 때만 컨트롤러 회전 사용
    bUseControllerRotationRoll = false;

    // 스프링암 설정 (더 자연스러운 카메라 동작을 위해)
    SpringArm->bDoCollisionTest = true;
    SpringArm->bInheritPitch = true;
    SpringArm->bInheritYaw = true;
    SpringArm->bInheritRoll = false;

    // 초기 상태 설정
    CurrentState = EPlayerState::IDLE;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 로컬 플레이어만 입력 설정 및 서버 알림
    if (!bIsRemoteControlled)
    {
        NotifySpawn();

        // Enhanced Input 설정
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
    // 원격 제어되는 캐릭터는 입력을 받지 않음
    if (bIsRemoteControlled)
    {
        return;
    }

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
            Input->BindAction(RunAction, ETriggerEvent::Started, this, &AMyCharacter::StartRun);
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

    // 원격 캐릭터는 보간 처리
    if (bIsRemoteControlled)
    {
        InterpolateRemoteMovement(DeltaTime);
    }
    // 로컬 플레이어는 입력을 서버로 전송
    else
    {
        SendInputToServer();
    }

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

        // 입력값 저장 (서버 전송용)
        ForwardInput = Movement.Y;
        RightInput = Movement.X;
        PitchInput = Rotation.Pitch;
        YawInput = Rotation.Yaw;
        RollInput = Rotation.Roll;

        // 로컬 움직임 처리 (즉시 반응성을 위해)
        if (!Movement.IsZero())
        {
            // 카메라 기준 이동 방향 계산
            const FVector ForwardDirection = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::X);
            const FVector RightDirection = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::Y);

            // 이동 입력 적용
            AddMovementInput(ForwardDirection, Movement.Y);
            AddMovementInput(RightDirection, Movement.X);

            // bAlwaysFaceMovementDirection이 false일 때만 수동 회전
            if (!bAlwaysFaceMovementDirection)
            {
                // 월드 좌표계에서 이동 방향 계산
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
    // 서버 설정과 동일 (500 * 2 = 1000)
    GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
    bRunPressed = true;
}

void AMyCharacter::StopRun(const FInputActionValue& Value)
{
    // 서버 기본 속도와 동일
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

    // 공격 애니메이션 재생
    if (AttackMontage)
    {
        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            AnimInstance->Montage_Play(AttackMontage);
        }
    }

    // 공격 상태 리셋 타이밍
    GetWorld()->GetTimerManager().SetTimer(AttackResetHandle, [this]()
        {
            bAttackPressed = false;
        }, AttackMontageDuration, false);
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
    if (HasInputChanged() || (CurrentTime - LastInputSendTime > 0.1f))
    {
        // 새 서버 InputPacket 구조에 맞춰 전송
        NetworkManager->SendPlayerInput(
            ForwardInput, RightInput,
            PitchInput, YawInput, RollInput,
            bRunPressed, bJumpPressed, bAttackPressed
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
    }
}

void AMyCharacter::UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState)
{
    // 목표 위치 및 회전 설정
    TargetLocation = NewTransform.GetLocation();
    TargetRotation = NewTransform.GetRotation().Rotator();
    TargetVelocity = NetworkVelocity;

    // 상태 업데이트
    EPlayerState PreviousState = CurrentState;
    CurrentState = NewState;

    // 초기 위치 설정 (텔레포트)
    if (!bInitialPositionSet)
    {
        SetActorLocation(TargetLocation);
        SetActorRotation(TargetRotation);
        bInitialPositionSet = true;
    }

    // 상태별 처리
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
    // 위치 보간
    FVector CurrentLocation = GetActorLocation();
    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
    SetActorLocation(NewLocation);

    // 회전 보간
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
    SetActorRotation(NewRotation);

    // 속도 보간 (부드러운 애니메이션을 위해)
    FVector CurrentVelocity = GetVelocity();
    FVector NewVelocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, DeltaTime, VelocityInterpSpeed);
    GetCharacterMovement()->Velocity = NewVelocity;
}

bool AMyCharacter::HasInputChanged() const
{
    const float Threshold = 0.01f; // 입력 변화 임계값

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

    // 상태 문자열 변환
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

    // 네트워크 상태 정보
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

    // 입력 상태 정보
    FString InputInfo = FString::Printf(TEXT("Input: F=%.2f R=%.2f"), ForwardInput, RightInput);

    // 버튼 상태 정보
    TArray<FString> ButtonStates;
    if (bRunPressed) ButtonStates.Add(TEXT("RUN"));
    if (bJumpPressed) ButtonStates.Add(TEXT("JUMP"));
    if (bAttackPressed) ButtonStates.Add(TEXT("ATTACK"));

    FString ButtonString = ButtonStates.Num() > 0 ?
        FString::Printf(TEXT("Buttons: %s"), *FString::Join(ButtonStates, TEXT("|"))) :
        TEXT("Buttons: None");

    // 회전 정보
    FString RotationInfo = FString::Printf(TEXT("Rot: P=%.1f Y=%.1f R=%.1f"),
        Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

    // 속도 분석
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float VerticalSpeed = Velocity.Z;

    // 최대 속도와 비교
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
    float SpeedPercentage = MaxSpeed > 0 ? (Speed2D / MaxSpeed) * 100.0f : 0.0f;

    // 종합 디버그 텍스트 생성
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

    // 텍스트 위치 (캐릭터 위쪽으로 더 올림)
    FVector TextLocation = Location + FVector(0, 0, 150);

    // 플레이어 타입에 따른 색상 구분
    FColor TextColor = FColor::White;
    if (bIsLocalPlayer)
        TextColor = FColor::Cyan;      // 로컬 플레이어: 청록색
    else if (bIsRemoteControlled)
        TextColor = FColor::Orange;    // 원격 플레이어: 주황색
    else
        TextColor = FColor::Yellow;    // 기타: 노란색

    // 네트워크 상태에 따른 색상 조정
    if (NetworkManager && !NetworkManager->IsConnected())
        TextColor = FColor::Red;       // 연결 끊김: 빨간색

    // 3D 월드에 텍스트 표시
    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, TextColor, 0.0f, true);

    // 추가: 이동 벡터 시각화 (화살표로 표시)
    if (bShowDebugInfo && !Velocity.IsZero())
    {
        FVector VelocityEnd = Location + (Velocity.GetSafeNormal() * 100.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, VelocityEnd, 20.0f, FColor::Green, false, 0.0f, 0, 3.0f);
    }

    // 추가: 입력 방향 시각화
    if (bShowDebugInfo && (FMath::Abs(ForwardInput) > 0.01f || FMath::Abs(RightInput) > 0.01f))
    {
        FVector InputDirection = FVector(ForwardInput, RightInput, 0).GetSafeNormal();
        FVector InputEnd = Location + (InputDirection * 80.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, InputEnd, 15.0f, FColor::Blue, false, 0.0f, 0, 2.0f);
    }
}