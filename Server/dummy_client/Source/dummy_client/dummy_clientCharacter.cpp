#include "dummy_clientCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "dummy_clientGameMode.h"
#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

Adummy_clientCharacter::Adummy_clientCharacter()
    : NetworkManager(nullptr)
    , bEnableNetworkUpdates(true)
    , LastPositionSentTime(0.0f)
    , PositionUpdateInterval(0.1f) // 10Hz ������Ʈ ����
    , OtherPlayerCharacterClass(nullptr)
{
    // ĸ�� ������Ʈ ����
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // �Է� ����
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // ��Ʈ�ѷ� ȸ���� ���� ĳ���Ͱ� ȸ������ �ʵ��� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ĳ���� �����Ʈ ������Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // ī�޶� �� ����
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // �ȷο� ī�޶� ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Tick �Լ� Ȱ��ȭ
    PrimaryActorTick.bCanEverTick = true;
}

void Adummy_clientCharacter::BeginPlay()
{
    Super::BeginPlay();

    // ��Ʈ��ũ �Ŵ��� �ʱ�ȭ
    InitializeNetworkManager();
}

void Adummy_clientCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ����� ���
    FVector Velocity = GetVelocity();
    if (Velocity.SizeSquared() > 0.0f)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Character velocity: X=%.2f Y=%.2f Z=%.2f"),
            Velocity.X, Velocity.Y, Velocity.Z);
    }

    // �÷��̾ ���� ��Ʈ�ѷ��� ������ �ְ�, ��Ʈ��ũ ������Ʈ�� Ȱ��ȭ�� ���
    if (IsLocallyControlled() && bEnableNetworkUpdates && NetworkManager && NetworkManager->IsConnected())
    {
        // ��ġ ������Ʈ ���� üũ
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastPositionSentTime >= PositionUpdateInterval)
        {
            // ������ ��ġ ���� ����
            SendPositionToServer();
            LastPositionSentTime = CurrentTime;
        }
    }

    // �ٸ� �÷��̾� ĳ���� ��ġ ���� ó��
    UpdateOtherPlayerCharacters(DeltaTime);
}

void Adummy_clientCharacter::InitializeNetworkManager()
{
    // ���� ��忡�� ��Ʈ��ũ �Ŵ��� ��������
    if (Adummy_clientGameMode* GameMode = Cast<Adummy_clientGameMode>(GetWorld()->GetAuthGameMode()))
    {
        NetworkManager = GameMode->GetNetworkManager();

        if (NetworkManager)
        {
            // ��������Ʈ ���ε�
            NetworkManager->OnPositionUpdate.AddDynamic(this, &Adummy_clientCharacter::OnPositionUpdateReceived);
            NetworkManager->OnRotationUpdate.AddDynamic(this, &Adummy_clientCharacter::OnRotationUpdateReceived);
            NetworkManager->OnJumpStateUpdate.AddDynamic(this, &Adummy_clientCharacter::OnJumpStateUpdateReceived);
            NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &Adummy_clientCharacter::OnConnectionStatusChanged);
        }
    }
}

void Adummy_clientCharacter::SendPositionToServer()
{
    if (!NetworkManager)
    {
        return;
    }

    // ���� ��ġ�� ȸ���� ��������
    FVector CurrentLocation = GetActorLocation();
    FRotator CurrentRotation = GetActorRotation();

    // �̵� ������ Ȯ�� (�ӵ� üũ)
    float ForwardValue = 0.0f;
    float RightValue = 0.0f;

    if (Controller && Controller->IsLocalPlayerController())
    {
        ForwardValue = GetInputAxisValue("MoveForward");
        RightValue = GetInputAxisValue("MoveRight");

        // ����� ��� �߰�
        UE_LOG(LogTemp, Display, TEXT("Input Values - Forward: %.2f, Right: %.2f"),
            ForwardValue, RightValue);
    }

    // �̵� ��Ŷ ����
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void Adummy_clientCharacter::OnPositionUpdateReceived(const FVector& NewPosition)
{
    // �ٸ� �÷��̾ �����ϴ��� Ȯ��
    bool bPlayerExists = false;
    for (auto& OtherPlayer : OtherPlayers)
    {
        // ���� ����� �÷��̾ ã�� ��ġ ������Ʈ
        // ���� ���������� �÷��̾� ID ���� ����ؾ� ��
        if (!bPlayerExists || (OtherPlayer.Key->GetActorLocation() - NewPosition).SizeSquared() < 100000.0f)
        {
            OtherPlayer.Value.TargetPosition = NewPosition;
            OtherPlayer.Value.PositionInterpolationTime = 0.0f;
            bPlayerExists = true;
            break;
        }
    }

    // �������� �ʴ� ��� ���� ����
    if (!bPlayerExists)
    {
        SpawnOtherPlayerCharacterInternal(NewPosition);
    }
}

void Adummy_clientCharacter::OnRotationUpdateReceived(const FRotator& NewRotation)
{
    // ���� �ֱٿ� ������Ʈ�� �÷��̾��� ȸ���� ����
    for (auto& OtherPlayer : OtherPlayers)
    {
        OtherPlayer.Value.TargetRotation = NewRotation;
        OtherPlayer.Value.RotationInterpolationTime = 0.0f;
        break; // ����� �ܼ��� ù ��° �÷��̾�Ը� ����
    }
}

void Adummy_clientCharacter::OnJumpStateUpdateReceived(bool IsJumping)
{
    // ���� �ֱٿ� ������Ʈ�� �÷��̾��� ���� ���� ����
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (IsJumping)
        {
            // ĳ���Ͱ� ACharacter Ŭ������ �ν��Ͻ����� Ȯ��
            if (ACharacter* OtherCharacter = Cast<ACharacter>(OtherPlayer.Key))
            {
                OtherCharacter->Jump();
            }
        }
        break; // ����� �ܼ��� ù ��° �÷��̾�Ը� ����
    }
}

void Adummy_clientCharacter::OnConnectionStatusChanged(bool IsConnected)
{
    if (!IsConnected)
    {
        // ���� ���� �� �ٸ� �÷��̾� ĳ���� ����
        for (auto& OtherPlayer : OtherPlayers)
        {
            if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
            {
                OtherPlayer.Key->Destroy();
            }
        }
        OtherPlayers.Empty();

        // UI�� ���� ���� ǥ�� �� �߰� ��� ���� ����
        OnNetworkDisconnected();
    }
    else
    {
        // ���� ���� �� ó��
        OnNetworkConnected();
    }
}

void Adummy_clientCharacter::UpdateOtherPlayerCharacters(float DeltaTime)
{
    // �ٸ� �÷��̾� ĳ���� ��ġ/ȸ�� ���� ó��
    TArray<AActor*> InvalidActors;

    for (auto& OtherPlayer : OtherPlayers)
    {
        if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
        {
            // ��ġ ����
            OtherPlayer.Value.PositionInterpolationTime += DeltaTime;
            float PosAlpha = FMath::Clamp(OtherPlayer.Value.PositionInterpolationTime / 0.1f, 0.0f, 1.0f);
            FVector NewPos = FMath::Lerp(OtherPlayer.Key->GetActorLocation(), OtherPlayer.Value.TargetPosition, PosAlpha);
            OtherPlayer.Key->SetActorLocation(NewPos);

            // ȸ�� ����
            OtherPlayer.Value.RotationInterpolationTime += DeltaTime;
            float RotAlpha = FMath::Clamp(OtherPlayer.Value.RotationInterpolationTime / 0.1f, 0.0f, 1.0f);
            FRotator NewRot = FMath::Lerp(OtherPlayer.Key->GetActorRotation(), OtherPlayer.Value.TargetRotation, RotAlpha);
            OtherPlayer.Key->SetActorRotation(NewRot);

            // �Է� ���� ��Ȱ��ȭ Ȯ�� (�ٸ� �÷��̾� ĳ���ʹ� �Է��� ���� �ʵ���)
            if (ACharacter* OtherCharacter = Cast<ACharacter>(OtherPlayer.Key))
            {
                if (APlayerController* PC = Cast<APlayerController>(OtherCharacter->GetController()))
                {
                    PC->DisableInput(PC);
                }
            }
        }
        else
        {
            // ��ȿ���� ���� ���� ǥ��
            InvalidActors.Add(OtherPlayer.Key);
        }
    }

    // ��ȿ���� ���� ���� ����
    for (AActor* Actor : InvalidActors)
    {
        OtherPlayers.Remove(Actor);
    }
}

void Adummy_clientCharacter::Jump()
{
    Super::Jump();

    // ���� ���� ������ ����
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(true, GetActorLocation());
    }
}

void Adummy_clientCharacter::StopJumping()
{
    Super::StopJumping();

    // ���� �ߴ� ���� ������ ����
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(false, GetActorLocation());
    }
}

AActor* Adummy_clientCharacter::SpawnOtherPlayerCharacterInternal(const FVector& Position)
{
    if (!GetWorld() || !OtherPlayerCharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player: Invalid World or Character Class"));
        return nullptr;
    }

    // �ٸ� �÷��̾� ĳ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AActor* NewPlayerActor = GetWorld()->SpawnActor<AActor>(OtherPlayerCharacterClass, Position, FRotator::ZeroRotator, SpawnParams);

    if (NewPlayerActor)
    {
        UE_LOG(LogTemp, Display, TEXT("Spawned other player character at: X=%.2f Y=%.2f Z=%.2f"),
            Position.X, Position.Y, Position.Z);

        // �÷��̾� �Է� ��Ȱ��ȭ
        if (ACharacter* OtherCharacter = Cast<ACharacter>(NewPlayerActor))
        {
            // AI ��Ʈ�ѷ� ��� �⺻ ��Ʈ�ѷ� ���
            AController* NewController = GetWorld()->SpawnActor<AController>(AController::StaticClass());
            if (NewController)
            {
                OtherCharacter->AIControllerClass = nullptr;
                OtherCharacter->bUseControllerRotationYaw = false;
                NewController->Possess(OtherCharacter);
                NewController->SetIgnoreMoveInput(true);
            }
        }

        // ĳ���� ���� ����
        FOtherPlayerInfo PlayerInfo;
        PlayerInfo.TargetPosition = Position;
        PlayerInfo.TargetRotation = FRotator::ZeroRotator;
        PlayerInfo.PositionInterpolationTime = 0.0f;
        PlayerInfo.RotationInterpolationTime = 0.0f;

        OtherPlayers.Add(NewPlayerActor, PlayerInfo);

        // �������Ʈ �̺�Ʈ ȣ��
        OnOtherPlayerSpawned(NewPlayerActor);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player character!"));
    }

    return NewPlayerActor;
}

// �⺻ �Է� �Լ��� ����
void Adummy_clientCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // ���� ī�޶� �ٶ󺸴� ���� ã��
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // ���� ���� ã��
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void Adummy_clientCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // ���� ī�޶� �ٶ󺸴� ���� ã��
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // ������ ���� ã��
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void Adummy_clientCharacter::TurnAtRate(float Rate)
{
    // �ʴ� �Է°��� turn rate ������� ȸ�� ���
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Adummy_clientCharacter::LookUpAtRate(float Rate)
{
    // �ʴ� �Է°��� look up/down rate ������� ȸ�� ���
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void Adummy_clientCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    Jump();
}

void Adummy_clientCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    StopJumping();
}

void Adummy_clientCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // ����
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Adummy_clientCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &Adummy_clientCharacter::StopJumping);

    // �̵�
    PlayerInputComponent->BindAxis("MoveForward", this, &Adummy_clientCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &Adummy_clientCharacter::MoveRight);

    // ȸ��
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &Adummy_clientCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &Adummy_clientCharacter::LookUpAtRate);

    // ��ġ ��� ����
    PlayerInputComponent->BindTouch(IE_Pressed, this, &Adummy_clientCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &Adummy_clientCharacter::TouchStopped);
}