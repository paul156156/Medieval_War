// OtherCharacter.cpp - MyCharacter ������� ���� �÷��̾� ����
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
    // �θ� ������ ȣ�� �� ���� �÷��̾�� �ʱ�ȭ
    InitializeAsRemotePlayer();
}

void AOtherCharacter::BeginPlay()
{
    // �θ��� BeginPlay�� ȣ������ ���� (Enhanced Input ���� ����)
    ACharacter::BeginPlay();  // ACharacter�� BeginPlay�� ȣ��

    // ���� �÷��̾� ���� ��Ȯ��
    InitializeAsRemotePlayer();

    UE_LOG(LogTemp, Log, TEXT("Remote player spawned: %s (ID: %d)"), *GetName(), PlayerId);
}

void AOtherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // ���� �÷��̾�� �Է��� ���� ���� - �ƹ��͵� ���� ����
    UE_LOG(LogTemp, Log, TEXT("OtherCharacter: Skipping input setup (Remote Player)"));

    // �θ� �Լ� ȣ������ ���� - �Է� ���ε� ���� ����
}

void AOtherCharacter::Tick(float DeltaTime)
{
    // ACharacter�� Tick�� ȣ�� (MyCharacter�� SendInputToServer ����)
    ACharacter::Tick(DeltaTime);

    // ���� �÷��̾�� �θ��� InterpolateToServerPosition ���
    InterpolateToServerPosition(DeltaTime);

    // ��Ʈ��ũ ����� ���� ǥ��
    if (bShowDebugInfo)
    {
        DisplayNetworkDebugInfo();
    }

    // ��Ʈ��ũ ������Ʈ �� ���
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastUpdateTime > 1.0f) // 1�ʸ��� ���
    {
        NetworkUpdateFrequency = UpdateCount / (CurrentTime - LastUpdateTime);
        UpdateCount = 0;
        LastUpdateTime = CurrentTime;
    }
}

// UpdateFromNetwork �������̵� - �θ� ��� + ��Ʈ��ũ �Է� ����
void AOtherCharacter::UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction)
{
    // �θ��� UpdateFromNetwork ȣ�� (���� ����)
    Super::UpdateFromNetwork(NewTransform, NetworkVelocity, NewState, NewAction);

    // ��Ʈ��ũ ������Ʈ �ð� ���
    LastNetworkUpdateTime = GetWorld()->GetTimeSeconds();
    UpdateCount++;

    // ��Ʈ��ũ �Է� ���� (�ð�ȭ��)
    FVector MovementDirection = NetworkVelocity.GetSafeNormal2D();
    if (!MovementDirection.IsZero())
    {
        // �뷫���� �Է� ���� ����
        FRotator LookDirection = NewTransform.GetRotation().Rotator();
        FVector ForwardVector = LookDirection.Vector();
        FVector RightVector = FRotationMatrix(LookDirection).GetUnitAxis(EAxis::Y);

        NetworkForwardInput = FVector::DotProduct(MovementDirection, ForwardVector);
        NetworkRightInput = FVector::DotProduct(MovementDirection, RightVector);

        // �� ����ȭ
        NetworkForwardInput = FMath::Clamp(NetworkForwardInput, -1.0f, 1.0f);
        NetworkRightInput = FMath::Clamp(NetworkRightInput, -1.0f, 1.0f);
    }
    else
    {
        NetworkForwardInput = 0.0f;
        NetworkRightInput = 0.0f;
    }

    // ���º� ��Ʈ��ũ �Է� ���� ����
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

	// �׼� ���� ������Ʈ
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

    // ��Ʈ��ũ ���� �м�
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

    // ���� ����
    FString StateString = GetPlayerStateString();
	FString ActionString = GetPlayerActionString();
    FString MovementMode = GetMovementModeString();

    // �ӵ� �м�
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float VSpeed = Velocity.Z;
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;

    // ��Ʈ��ũ �Է� ����
    FString NetworkInputInfo = TEXT("No Input");
    if (FMath::Abs(NetworkForwardInput) > 0.01f || FMath::Abs(NetworkRightInput) > 0.01f)
    {
        FString ForwardDir = NetworkForwardInput > 0.01f ? TEXT("W") : (NetworkForwardInput < -0.01f ? TEXT("S") : TEXT(""));
        FString RightDir = NetworkRightInput > 0.01f ? TEXT("D") : (NetworkRightInput < -0.01f ? TEXT("A") : TEXT(""));
        NetworkInputInfo = FString::Printf(TEXT("Input: %s%s"), *ForwardDir, *RightDir);
    }

    // Ȱ�� �׼�
    TArray<FString> ActiveActions;
    if (bNetworkRunPressed) ActiveActions.Add(TEXT("RUN"));
    if (bNetworkJumpPressed) ActiveActions.Add(TEXT("JUMP"));
    if (bNetworkAttackPressed) ActiveActions.Add(TEXT("ATTACK"));
    if (bNetworkDefensePressed) ActiveActions.Add(TEXT("DEFENSE"));
    FString ActionInfo = ActiveActions.Num() > 0 ?
        FString::Join(ActiveActions, TEXT(" | ")) :
        TEXT("No actions");

    // ����ȭ ��Ȯ��
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

    // ���� ����� ����
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

    // �ؽ�Ʈ ǥ��
    FVector TextLocation = Location + FVector(0, 0, 200);
    DrawDebugString(GetWorld(), TextLocation, DebugText, nullptr, SyncColor, 0.0f, true);

    // �ð��� ���� ǥ��
    DrawNetworkStatusVisuals(Location);
}

void AOtherCharacter::InitializeAsRemotePlayer()
{
    // ī�޶� ��Ȱ��ȭ (�ٸ� �÷��̾��� ī�޶�� �ʿ����)
    if (FollowCamera)
    {
        FollowCamera->SetActive(false);
    }

    // Spring Arm�� ��Ȱ��ȭ
    if (SpringArm)
    {
        SpringArm->SetActive(false);
    }

    // ���� �÷��̾�� ���� ���� (�θ��� ���� �������̵�)
    InterpSpeed = 12.0f;
    VelocityInterpSpeed = 8.0f;

    // ����� ������ �⺻������ Ȱ��ȭ (���� �÷��̾� ����͸���)
    bShowDebugInfo = true;

    UE_LOG(LogTemp, Log, TEXT("OtherCharacter initialized as remote player: %s"), *GetName());
}

// ���� �Լ���
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
        return FColor::Green;    // �ֽ� ����
    else if (TimeSinceLastUpdate < 2.0f)
        return FColor::Yellow;   // �ణ ����
    else
        return FColor::Red;      // ������ ����
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
    // �÷��̾� ���� ����
    FColor CircleColor = GetStateCircleColor();
    DrawDebugCircle(GetWorld(), Location, 80.0f, 16, CircleColor, false, 0.0f, 0, 3.0f,
        FVector(0, 1, 0), FVector(1, 0, 0));

    // ��ǥ ��ġ ǥ�� (��Ȳ�� ��ü)
    if (!TargetLocation.IsZero())
    {
        DrawDebugSphere(GetWorld(), TargetLocation, 25.0f, 8, FColor::Orange, false, 0.0f, 0, 2.0f);

        // ���� ��ġ�� ��ǥ ��ġ ���ἱ
        float Distance = FVector::Dist(Location, TargetLocation);
        if (Distance > 10.0f)
        {
            DrawDebugLine(GetWorld(), Location, TargetLocation, FColor::Orange, false, 0.0f, 0, 2.0f);

            // �Ÿ� ǥ��
            FString DistanceText = FString::Printf(TEXT("%.0f"), Distance);
            DrawDebugString(GetWorld(), (Location + TargetLocation) * 0.5f, DistanceText,
                nullptr, FColor::Orange, 0.0f);
        }
    }

    // ��Ʈ��ũ �Է� ���� ȭ��ǥ (�Ķ���)
    if (FMath::Abs(NetworkForwardInput) > 0.01f || FMath::Abs(NetworkRightInput) > 0.01f)
    {
        FVector InputDir = FVector(NetworkForwardInput, NetworkRightInput, 0).GetSafeNormal();
        FVector InputEnd = Location + (InputDir * 90.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, InputEnd, 18.0f, FColor::Blue, false, 0.0f, 0, 3.0f);
    }

    // ���� �̵� ���� ȭ��ǥ (�ʷϻ�)
    FVector Velocity = GetVelocity();
    if (!Velocity.IsZero())
    {
        FVector VelEnd = Location + (Velocity.GetSafeNormal() * 110.0f);
        DrawDebugDirectionalArrow(GetWorld(), Location, VelEnd, 22.0f, FColor::Green, false, 0.0f, 0, 4.0f);
    }

    // ��Ʈ��ũ ���� ǥ�� (����ȭ ���¿� ���� ����)
    FColor NetworkStatusColor = GetNetworkStatusColor();
    DrawDebugSphere(GetWorld(), Location + FVector(0, 0, 100), 15.0f, 6, NetworkStatusColor, false, 0.0f, 0, 2.0f);
}