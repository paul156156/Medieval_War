// OtherCharacter.cpp - ���� �÷��̾� ���� ĳ���� ����
#include "OtherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AOtherCharacter::AOtherCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // ĳ���� �̵� ���� (MyCharacter�� ����)
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->GravityScale = 1.0f;

    // ��Ʈ�ѷ� ȸ�� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ���� ���� ����
    bIsRemoteControlled = true;

    // �ʱ� ���� ����
    CurrentState = EPlayerState::IDLE;

    // �� �ε巯�� ������ ���� ����
    InterpSpeed = 12.0f;
    VelocityInterpSpeed = 8.0f;
}

void AOtherCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("OtherCharacter spawned - ID: %d"), PlayerId);

    // ���� �÷��̾�� �Է��� ���� ����
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        PC->DisableInput(PC);
    }
}

void AOtherCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ���� �÷��̾�� �׻� ���� ó��
    InterpolateRemoteMovement(DeltaTime);

    // ����� ���� ǥ��
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

void AOtherCharacter::UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState)
{
    // ��Ʈ��ũ ������Ʈ �ð� ���
    LastNetworkUpdateTime = GetWorld()->GetTimeSeconds();
    UpdateCount++;

    // ���� ��ġ ���� (���� ����)
    FVector OldLocation = GetActorLocation();

    // ��ǥ ��ġ �� ȸ�� ����
    TargetLocation = NewTransform.GetLocation();
    TargetRotation = NewTransform.GetRotation().Rotator();
    TargetVelocity = NetworkVelocity;

    // ���� ������Ʈ
    EPlayerState PreviousState = CurrentState;
    CurrentState = NewState;

    // ��ġ ���� ���
    float PositionDifference = FVector::Dist(OldLocation, TargetLocation);

    // ū ��ġ ���̰� ������ �α� ���
    if (PositionDifference > 200.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Large position jump for remote player %d: %.1f units"),
            PlayerId, PositionDifference);
    }

    // �ʱ� ��ġ ���� (�ڷ���Ʈ)
    if (!bInitialPositionSet || PositionDifference > 500.0f)
    {
        SetActorLocation(TargetLocation);
        SetActorRotation(TargetRotation);
        bInitialPositionSet = true;

        UE_LOG(LogTemp, Log, TEXT("Remote player %d position set: (%.1f, %.1f, %.1f)"),
            PlayerId, TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
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
                UE_LOG(LogTemp, Verbose, TEXT("Remote player %d started attack animation"), PlayerId);
            }
        }
        bNetworkAttackPressed = true;
        break;

    case EPlayerState::JUMPING:
        if (GetCharacterMovement()->MovementMode != MOVE_Falling)
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Falling);
        }
        bNetworkJumpPressed = true;
        break;

    case EPlayerState::RUNNING:
        GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
        bNetworkRunPressed = true;
        break;

    case EPlayerState::WALKING:
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
        if (GetCharacterMovement()->MovementMode != MOVE_Walking)
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        }
        bNetworkRunPressed = false;
        break;

    case EPlayerState::IDLE:
    default:
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
        if (GetCharacterMovement()->MovementMode != MOVE_Walking)
        {
            GetCharacterMovement()->SetMovementMode(MOVE_Walking);
        }
        bNetworkRunPressed = false;
        bNetworkJumpPressed = false;
        bNetworkAttackPressed = false;
        break;
    }

    // ��Ʈ��ũ �Է� ���� (�ð�ȭ��)
    FVector MovementDirection = TargetVelocity.GetSafeNormal2D();
    if (!MovementDirection.IsZero())
    {
        // �뷫���� �Է� ���� ����
        FRotator LookDirection = TargetRotation;
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
}

void AOtherCharacter::InterpolateRemoteMovement(float DeltaTime)
{
    if (TargetLocation.IsZero()) return;

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
    FString MovementMode = GetMovementModeString();

    // �ӵ� �м�
    float Speed2D = FVector(Velocity.X, Velocity.Y, 0).Size();
    float VSpeed = Velocity.Z;
    float MaxSpeed = GetCharacterMovement()->MaxWalkSpeed;

    // ��Ʈ��ũ �Է� ����
    FString NetworkInputInfo = TEXT("No Input");
    if (FMath::Abs(NetworkForwardInput) > 0.01f || FMath::Abs(NetworkRightInput) > 0.01f)
    {
        FString ForwardDir = NetworkForwardInput > 0.01f ? TEXT("UP") : (NetworkForwardInput < -0.01f ? TEXT("DOWN") : TEXT(""));
        FString RightDir = NetworkRightInput > 0.01f ? TEXT("RIGHT") : (NetworkRightInput < -0.01f ? TEXT("LEFT") : TEXT(""));
        NetworkInputInfo = FString::Printf(TEXT("Input: %s%s"), *ForwardDir, *RightDir);
    }

    // Ȱ�� �׼�
    TArray<FString> ActiveActions;
    if (bNetworkRunPressed) ActiveActions.Add(TEXT("RUN"));
    if (bNetworkJumpPressed) ActiveActions.Add(TEXT("JUMP"));
    if (bNetworkAttackPressed) ActiveActions.Add(TEXT("ATTACK"));
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
        TEXT("���� REMOTE PLAYER [ID:%d] ����\n")
        TEXT("Status: %s (%.1fs ago)\n")
        TEXT("Update Rate: %.1f Hz\n")
        TEXT("State: %s | Mode: %s\n")
        TEXT("�������� POSITION DATA ��������\n")
        TEXT("Current: (%.0f, %.0f, %.0f)\n")
        TEXT("Target: (%.0f, %.0f, %.0f)\n")
        TEXT("Speed: H=%.1f V=%.1f (Max=%.0f)\n")
        TEXT("%s\n")
        TEXT("�������� NETWORK INPUT ��������\n")
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

// ���� �Լ��� ����
FString AOtherCharacter::GetPlayerStateString() const
{
    switch (CurrentState)
    {
    case EPlayerState::IDLE: return TEXT("IDLE");
    case EPlayerState::WALKING: return TEXT("WALKING");
    case EPlayerState::RUNNING: return TEXT("RUNNING");
    case EPlayerState::JUMPING: return TEXT("JUMPING");
    case EPlayerState::ATTACKING: return TEXT("ATTACKING");
	case EPlayerState::DEFENSING: return TEXT("DEFENSING");
    default: return TEXT("UNKNOWN");
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

FColor AOtherCharacter::GetDebugTextColor() const
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
    case EPlayerState::ATTACKING: return FColor::Red;
    default: return FColor::Purple;
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
    FColor NetworkStatusColor = GetDebugTextColor();
    DrawDebugSphere(GetWorld(), Location + FVector(0, 0, 100), 15.0f, 6, NetworkStatusColor, false, 0.0f, 0, 2.0f);
}