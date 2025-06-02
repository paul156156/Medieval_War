// OtherCharacter.cpp - MyCharacter 상속으로 원격 플레이어 구현
#include "OtherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AOtherCharacter::AOtherCharacter()
{
    // 부모 생성자 호출 후 원격 플레이어로 초기화
    InitializeAsRemotePlayer();
}

void AOtherCharacter::BeginPlay()
{
    // 부모의 BeginPlay는 호출하지 않음 (Enhanced Input 설정 방지)
    ACharacter::BeginPlay();  // ACharacter의 BeginPlay만 호출

    // 원격 플레이어 설정 재확인
    InitializeAsRemotePlayer();

    UE_LOG(LogTemp, Log, TEXT("Remote player spawned: %s (ID: %d)"), *GetName(), PlayerId);
}

void AOtherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // 원격 플레이어는 입력을 받지 않음 - 아무것도 하지 않음
    UE_LOG(LogTemp, Log, TEXT("OtherCharacter: Skipping input setup (Remote Player)"));

    // 부모 함수 호출하지 않음 - 입력 바인딩 완전 방지
}

void AOtherCharacter::Tick(float DeltaTime)
{
    // ACharacter의 Tick만 호출 (MyCharacter의 SendInputToServer 방지)
    ACharacter::Tick(DeltaTime);

    // 원격 플레이어는 부모의 InterpolateToServerPosition 사용
    InterpolateToServerPosition(DeltaTime);

    // 네트워크 디버그 정보 표시
    if (bShowDebugInfo)
    {
        DisplayNetworkDebugInfo();
    }

    // 네트워크 업데이트 빈도 계산
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastUpdateTime > 1.0f) // 1초마다 계산
    {
        NetworkUpdateFrequency = UpdateCount / (CurrentTime - LastUpdateTime);
        UpdateCount = 0;
        LastUpdateTime = CurrentTime;
    }
}

// UpdateFromNetwork 오버라이드 - 부모 기능 + 네트워크 입력 추정
void AOtherCharacter::UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction)
{
    // 부모의 UpdateFromNetwork 호출 (공통 로직)
    Super::UpdateFromNetwork(NewTransform, NetworkVelocity, NewState, NewAction);

    // 네트워크 업데이트 시간 기록
    LastNetworkUpdateTime = GetWorld()->GetTimeSeconds();
    UpdateCount++;

    // 네트워크 입력 추정 (시각화용)
    FVector MovementDirection = NetworkVelocity.GetSafeNormal2D();
    if (!MovementDirection.IsZero())
    {
        // 대략적인 입력 방향 추정
        FRotator LookDirection = NewTransform.GetRotation().Rotator();
        FVector ForwardVector = LookDirection.Vector();
        FVector RightVector = FRotationMatrix(LookDirection).GetUnitAxis(EAxis::Y);

        NetworkForwardInput = FVector::DotProduct(MovementDirection, ForwardVector);
        NetworkRightInput = FVector::DotProduct(MovementDirection, RightVector);

        // 값 정규화
        NetworkForwardInput = FMath::Clamp(NetworkForwardInput, -1.0f, 1.0f);
        NetworkRightInput = FMath::Clamp(NetworkRightInput, -1.0f, 1.0f);
    }
    else
    {
        NetworkForwardInput = 0.0f;
        NetworkRightInput = 0.0f;
    }

    // 상태별 네트워크 입력 상태 설정
    switch (NewState)
    {
    case EPlayerState::JUMPING:
        bNetworkJumpPressed = true;
        break;
    case EPlayerState::RUNNING:
        bNetworkRunPressed = true;
        break;
    case EPlayerState::WALKING:
        bNetworkRunPressed = false;
        break;
    case EPlayerState::IDLE:
    default:
		bNetworkJumpPressed = false;
		bNetworkRunPressed = false;
        break;
    }

	// 액션 상태 업데이트
    switch (NewAction)
    {
        case EPlayerAction::ATTACK:
            bNetworkAttackPressed = true;
			break;
        case EPlayerAction::DEFEND:
            bNetworkDefensePressed = true;
            break;
		case EPlayerAction::NONE:
        default:
            bNetworkAttackPressed = false;
            bNetworkDefensePressed = false;
			break;
    }
}

void AOtherCharacter::DisplayNetworkDebugInfo()
{
    FVector Location = GetActorLocation();
    FVector Velocity = GetVelocity();

    // 네트워크 상태 분석
    float TimeSinceLastUpdate = GetWorld()->GetTimeSeconds() - LastNetworkUpdateTime;
    FString SyncStatus;
    FColor SyncColor;

    if (TimeSinceLastUpdate < 0.5f)
    {
        SyncStatus = TEXT("Active");
        SyncColor = FColor::Green;
    }
    else if (TimeSinceLastUpdate < 2.0f)
    {
        SyncStatus = TEXT("Delayed");
        SyncColor = FColor::Yellow;
    }
    else
    {
        SyncStatus = TEXT("Stale");
        SyncColor = FColor::Red;
    }

    // 상태 정보
    FString StateString = GetPlayerStateString();
	FString ActionString = GetPlayerActionString();
    FString MovementMode = GetMovementModeString();

    // 속도 분석
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float VSpeed = Velocity.Z;
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;

    // 네트워크 입력 상태
    FString NetworkInputInfo = TEXT("No Input");
    if (FMath::Abs(NetworkForwardInput) > 0.01f || FMath::Abs(NetworkRightInput) > 0.01f)
    {
        FString ForwardDir = NetworkForwardInput > 0.01f ? TEXT("W") : (NetworkForwardInput < -0.01f ? TEXT("S") : TEXT(""));
        FString RightDir = NetworkRightInput > 0.01f ? TEXT("D") : (NetworkRightInput < -0.01f ? TEXT("A") : TEXT(""));
        NetworkInputInfo = FString::Printf(TEXT("Input: %s%s"), *ForwardDir, *RightDir);
    }

    // 활성 액션
    TArray<FString> ActiveActions;
    if (bNetworkRunPressed) ActiveActions.Add(TEXT("RUN"));
    if (bNetworkJumpPressed) ActiveActions.Add(TEXT("JUMP"));
    if (bNetworkAttackPressed) ActiveActions.Add(TEXT("ATTACK"));
    if (bNetworkDefensePressed) ActiveActions.Add(TEXT("DEFENSE"));
    FString ActionInfo = ActiveActions.Num() > 0 ?
        FString::Join(ActiveActions, TEXT(" | ")) :
        TEXT("No actions");

    // 동기화 정확도
    float DistanceToTarget = FVector::Dist(Location, TargetLocation);
    FString AccuracyInfo;
    if (DistanceToTarget > 20.0f)
    {
        AccuracyInfo = FString::Printf(TEXT("Sync Gap: %.1f units"), DistanceToTarget);
    }
    else
    {
        AccuracyInfo = TEXT("Well Synced");
    }

    // 종합 디버그 정보
    FString DebugText = FString::Printf(
        TEXT("=== REMOTE PLAYER [ID:%d] ===\n")
        TEXT("Status: %s (%.1fs ago)\n")
        TEXT("Update Rate: %.1f Hz\n")
        TEXT("State: %s | Mode: %s\n")
        TEXT("=== POSITION DATA ===\n")
        TEXT("Current: (%.0f, %.0f, %.0f)\n")
        TEXT("Target: (%.0f, %.0f, %.0f)\n")
        TEXT("Speed: H=%.1f V=%.1f (Max=%.0f)\n")
        TEXT("%s\n")
        TEXT("=== NETWORK INPUT ===\n")
        TEXT("%s\n")
        TEXT("Actions: %s"),
        PlayerId,
        *SyncStatus, TimeSinceLastUpdate,
        NetworkUpdateFrequency,
        *StateString, *MovementMode,
        Location.X, Location.Y, Location.Z,
        TargetLocation.X, TargetLocation.Y, TargetLocation.Z,
        Speed2D, VSpeed, MaxSpeed,
        *AccuracyInfo,
        *NetworkInputInfo,
        *ActionInfo
    );

    // 텍스트 표시
    FVector TextLocation = Location + FVector(0, 0, 200);
    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, SyncColor, 0.0f, true);

    // 시각적 상태 표시
    DrawNetworkStatusVisuals(Location);
}

void AOtherCharacter::InitializeAsRemotePlayer()
{
    // 카메라 비활성화 (다른 플레이어의 카메라는 필요없음)
    if (FollowCamera)
    {
        FollowCamera->SetActive(false);
    }

    // Spring Arm도 비활성화
    if (SpringArm)
    {
        SpringArm->SetActive(false);
    }

    // 원격 플레이어용 보간 설정 (부모의 설정 오버라이드)
    InterpSpeed = 12.0f;
    VelocityInterpSpeed = 8.0f;

    // 디버그 정보는 기본적으로 활성화 (원격 플레이어 모니터링용)
    bShowDebugInfo = true;

    UE_LOG(LogTemp, Log, TEXT("OtherCharacter initialized as remote player: %s"), *GetName());
}

// 헬퍼 함수들
FString AOtherCharacter::GetPlayerStateString() const
{
    switch (CurrentState)
    {
    case EPlayerState::IDLE: return TEXT("IDLE");
    case EPlayerState::WALKING: return TEXT("WALKING");
    case EPlayerState::RUNNING: return TEXT("RUNNING");
    case EPlayerState::JUMPING: return TEXT("JUMPING");
    case EPlayerState::DEAD: return TEXT("DEAD");
    default: return TEXT("UNKNOWN");
    }
}

FString AOtherCharacter::GetPlayerActionString() const
{
    switch (CurrentAction)
    {
	case EPlayerAction::NONE: return TEXT("NONE");
    case EPlayerAction::ATTACK: return TEXT("ATTACK");
    case EPlayerAction::DEFEND: return TEXT("DEFEND");
    default: return TEXT("NONE");
    }
}

FString AOtherCharacter::GetMovementModeString() const
{
    switch (GetCharacterMovement()->MovementMode)
    {
    case MOVE_None: return TEXT("None");
    case MOVE_Walking: return TEXT("Walking");
    case MOVE_Falling: return TEXT("Falling");
    case MOVE_Swimming: return TEXT("Swimming");
    case MOVE_Flying: return TEXT("Flying");
    default: return TEXT("Unknown");
    }
}

FColor AOtherCharacter::GetNetworkStatusColor() const
{
    float TimeSinceLastUpdate = GetWorld()->GetTimeSeconds() - LastNetworkUpdateTime;

    if (TimeSinceLastUpdate < 0.5f)
        return FColor::Green;    // 최신 상태
    else if (TimeSinceLastUpdate < 2.0f)
        return FColor::Yellow;   // 약간 지연
    else
        return FColor::Red;      // 오래된 상태
}

FColor AOtherCharacter::GetStateCircleColor() const
{
    switch (CurrentState)
    {
    case EPlayerState::IDLE: return FColor::White;
    case EPlayerState::WALKING: return FColor::Green;
    case EPlayerState::RUNNING: return FColor::Yellow;
    case EPlayerState::JUMPING: return FColor::Blue;
    case EPlayerState::DEAD: return FColor::Red;
    default: return FColor::Magenta;
    }
}

FColor AOtherCharacter::GetActionCircleColor() const
{
    switch (CurrentAction)
    {
	case EPlayerAction::NONE: return FColor::Black;
    case EPlayerAction::ATTACK: return FColor::Purple;
    case EPlayerAction::DEFEND: return FColor::Orange;
    default: return FColor::White;
    }
}

void AOtherCharacter::DrawNetworkStatusVisuals(const FVector& Location) const
{
    // 플레이어 상태 원형
    FColor CircleColor = GetStateCircleColor();
    DrawDebugCircle(GetWorld(), Location, 80.0f, 16, CircleColor, false, 0.0f, 0, 3.0f,
        FVector(0, 1, 0), FVector(1, 0, 0));

    // 목표 위치 표시 (주황색 구체)
    if (!TargetLocation.IsZero())
    {
        DrawDebugSphere(GetWorld(), TargetLocation, 25.0f, 8, FColor::Orange, false, 0.0f, 0, 2.0f);

        // 현재 위치와 목표 위치 연결선
        float Distance = FVector::Dist(Location, TargetLocation);
        if (Distance > 10.0f)
        {
            DrawDebugLine(GetWorld(), Location, TargetLocation, FColor::Orange, false, 0.0f, 0, 2.0f);

            // 거리 표시
            FString DistanceText = FString::Printf(TEXT("%.0f"), Distance);
            DrawDebugString(GetWorld(), (Location + TargetLocation) * 0.5f, DistanceText,
                nullptr, FColor::Orange, 0.0f);
        }
    }

    // 네트워크 입력 방향 화살표 (파랑색)
    if (FMath::Abs(NetworkForwardInput) > 0.01f || FMath::Abs(NetworkRightInput) > 0.01f)
    {
        FVector InputDir = FVector(NetworkForwardInput, NetworkRightInput, 0).GetSafeNormal();
        FVector InputEnd = Location + (InputDir * 90.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, InputEnd, 18.0f, FColor::Blue, false, 0.0f, 0, 3.0f);
    }

    // 실제 이동 방향 화살표 (초록색)
    FVector Velocity = GetVelocity();
    if (!Velocity.IsZero())
    {
        FVector VelEnd = Location + (Velocity.GetSafeNormal() * 110.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, VelEnd, 22.0f, FColor::Green, false, 0.0f, 0, 4.0f);
    }

    // 네트워크 상태 표시 (동기화 상태에 따른 색상)
    FColor NetworkStatusColor = GetNetworkStatusColor();
    DrawDebugSphere(GetWorld(), Location + FVector(0, 0, 100), 15.0f, 6, NetworkStatusColor, false, 0.0f, 0, 2.0f);
}