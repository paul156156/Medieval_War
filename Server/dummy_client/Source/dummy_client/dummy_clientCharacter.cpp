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
    , LocalClientId(-1)  // �ʱ� Ŭ���̾�Ʈ ID�� -1�� ����
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

    // ����� �α� �߰�
    UE_LOG(LogTemp, Warning, TEXT("Player Character BeginPlay - Other Player Class: %s"),
        OtherPlayerCharacterClass ? *OtherPlayerCharacterClass->GetName() : TEXT("NULL"));
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
            // ���� ��������Ʈ ���ε� ���� (������ ����)
            NetworkManager->OnPositionUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnPositionUpdateReceived);
            NetworkManager->OnRotationUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnRotationUpdateReceived);
            NetworkManager->OnJumpStateUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnJumpStateUpdateReceived);
            NetworkManager->OnPlayerUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnPlayerUpdateReceived);
            NetworkManager->OnClientIdReceived.RemoveDynamic(this, &Adummy_clientCharacter::OnClientIdReceived);
            NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &Adummy_clientCharacter::OnConnectionStatusChanged);

            // ���ο� ��������Ʈ�� ���ε� (���Žô� ����)
            NetworkManager->OnPlayerUpdate.AddDynamic(this, &Adummy_clientCharacter::OnPlayerUpdateReceived);
            NetworkManager->OnClientIdReceived.AddDynamic(this, &Adummy_clientCharacter::OnClientIdReceived);
            NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &Adummy_clientCharacter::OnConnectionStatusChanged);

            UE_LOG(LogTemp, Display, TEXT("Network Manager initialized with new delegate system"));

            // �̹� ID�� �Ҵ�Ǿ� �ִ� ��� ����
            LocalClientId = NetworkManager->GetClientId();
            UE_LOG(LogTemp, Display, TEXT("Local Client ID: %d"), LocalClientId);
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
        UE_LOG(LogTemp, Verbose, TEXT("Input Values - Forward: %.2f, Right: %.2f"),
            ForwardValue, RightValue);
    }

    // �̵� ��Ŷ ����
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void Adummy_clientCharacter::OnClientIdReceived(int32 ClientId)
{
    // ���� Ŭ���̾�Ʈ ID ����
    LocalClientId = ClientId;

    UE_LOG(LogTemp, Display, TEXT("Client ID received: %d"), LocalClientId);
}

void Adummy_clientCharacter::OnPlayerUpdateReceived(int32 ClientId, const FVector& NewPosition, const FRotator& NewRotation, bool IsJumping)
{
    // �ڽ��� ������Ʈ�� ����
    if (ClientId == LocalClientId)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Ignoring update for local player (ID: %d)"), ClientId);
        return;
    }

    UE_LOG(LogTemp, Verbose, TEXT("Received update for player ID %d: Pos=(%.1f,%.1f,%.1f), Yaw=%.1f, Jumping=%s"),
        ClientId, NewPosition.X, NewPosition.Y, NewPosition.Z, NewRotation.Yaw,
        IsJumping ? TEXT("true") : TEXT("false"));

    // �ش� ID�� �÷��̾ �̹� �����ϴ��� Ȯ��
    AActor* ExistingPlayerActor = nullptr;

    for (auto& Pair : OtherPlayers)
    {
        if (Pair.Value.ClientId == ClientId)
        {
            ExistingPlayerActor = Pair.Key;

            // ��ġ, ȸ��, ���� ���� ������Ʈ
            Pair.Value.TargetPosition = NewPosition;
            Pair.Value.TargetRotation = NewRotation;
            Pair.Value.PositionInterpolationTime = 0.0f;
            Pair.Value.RotationInterpolationTime = 0.0f;
            Pair.Value.IsJumping = IsJumping;

            // ���� ���� ó��
            if (IsJumping && !Pair.Value.IsJumping)
            {
                if (ACharacter* OtherCharacter = Cast<ACharacter>(ExistingPlayerActor))
                {
                    OtherCharacter->Jump();
                }
            }

            break;
        }
    }

    // �������� �ʴ� ��� ���� ����
    if (!ExistingPlayerActor)
    {
        UE_LOG(LogTemp, Display, TEXT("Spawning new player character for client ID: %d"), ClientId);
        SpawnOtherPlayerCharacterInternal(NewPosition, ClientId);
    }
}

void Adummy_clientCharacter::OnPositionUpdateReceived(const FVector& NewPosition)
{
    // ���Ž� ȣȯ�� ���� - ���ο� OnPlayerUpdateReceived�� ��ü ����
    UE_LOG(LogTemp, Warning, TEXT("OnPositionUpdateReceived: Legacy function called. This should be handled by OnPlayerUpdateReceived."));

    // ID ������ �����Ƿ� ���� ����� ĳ���Ϳ��� ���� (���Ž� ����)
    bool bPlayerExists = false;
    float ClosestDistSq = MAX_FLT;
    AActor* ClosestActor = nullptr;

    for (auto& Pair : OtherPlayers)
    {
        float DistSq = (Pair.Key->GetActorLocation() - NewPosition).SizeSquared();
        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            ClosestActor = Pair.Key;
            bPlayerExists = true;
        }
    }

    if (bPlayerExists && ClosestActor)
    {
        OtherPlayers[ClosestActor].TargetPosition = NewPosition;
        OtherPlayers[ClosestActor].PositionInterpolationTime = 0.0f;
    }
    else
    {
        // ID ���� ���� �� ĳ���� ���� (�ӽ� ID -1 ���)
        SpawnOtherPlayerCharacterInternal(NewPosition, -1);
    }
}

void Adummy_clientCharacter::OnRotationUpdateReceived(const FRotator& NewRotation)
{
    // ���Ž� ȣȯ�� ���� - ���ο� OnPlayerUpdateReceived�� ��ü ����
    UE_LOG(LogTemp, Warning, TEXT("OnRotationUpdateReceived: Legacy function called. This should be handled by OnPlayerUpdateReceived."));

    // ID ������ �����Ƿ� ù ��° ĳ���Ϳ��� ���� (���Ž� ����)
    if (OtherPlayers.Num() > 0)
    {
        auto FirstItem = OtherPlayers.CreateIterator();
        FirstItem.Value().TargetRotation = NewRotation;
        FirstItem.Value().RotationInterpolationTime = 0.0f;
    }
}

void Adummy_clientCharacter::OnJumpStateUpdateReceived(bool IsJumping)
{
    // ���Ž� ȣȯ�� ���� - ���ο� OnPlayerUpdateReceived�� ��ü ����
    UE_LOG(LogTemp, Warning, TEXT("OnJumpStateUpdateReceived: Legacy function called. This should be handled by OnPlayerUpdateReceived."));

    // ID ������ �����Ƿ� ù ��° ĳ���Ϳ��� ���� (���Ž� ����)
    if (OtherPlayers.Num() > 0)
    {
        auto FirstItem = OtherPlayers.CreateIterator();
        FirstItem.Value().IsJumping = IsJumping;

        if (IsJumping)
        {
            if (ACharacter* OtherCharacter = Cast<ACharacter>(FirstItem.Key()))
            {
                OtherCharacter->Jump();
            }
        }
    }
}

void Adummy_clientCharacter::OnConnectionStatusChanged(bool IsConnected)
{
    if (!IsConnected)
    {
        // ���� ���� �� �ٸ� �÷��̾� ĳ���� ����
        RemoveAllOtherPlayers();

        // Ŭ���̾�Ʈ ID �ʱ�ȭ
        LocalClientId = -1;

        // UI�� ���� ���� ǥ�� �� �߰� ��� ���� ����
        OnNetworkDisconnected();
    }
    else
    {
        // ���� ���� �� ó��
        OnNetworkConnected();
    }
}

void Adummy_clientCharacter::RemoveAllOtherPlayers()
{
    // ��� �ٸ� �÷��̾� ĳ���� ����
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
        {
            OtherPlayer.Key->Destroy();
        }
    }
    OtherPlayers.Empty();

    UE_LOG(LogTemp, Display, TEXT("All other player characters removed"));
}

void Adummy_clientCharacter::RemoveOtherPlayerCharacter(int32 ClientId)
{
    // Ư�� ID�� �÷��̾ ����
    AActor* ActorToRemove = nullptr;

    for (auto& Pair : OtherPlayers)
    {
        if (Pair.Value.ClientId == ClientId)
        {
            ActorToRemove = Pair.Key;

            if (ActorToRemove && IsValid(ActorToRemove))
            {
                ActorToRemove->Destroy();
                OtherPlayers.Remove(ActorToRemove);

                // �������Ʈ �̺�Ʈ ȣ��
                OnOtherPlayerRemoved(ClientId);

                UE_LOG(LogTemp, Display, TEXT("Removed player character for client ID: %d"), ClientId);
            }

            break;
        }
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

AActor* Adummy_clientCharacter::SpawnOtherPlayerCharacterInternal(const FVector& Position, int32 InClientId)
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
        UE_LOG(LogTemp, Display, TEXT("Spawned other player character for client ID %d at: X=%.2f Y=%.2f Z=%.2f"),
            InClientId, Position.X, Position.Y, Position.Z);

        // �÷��̾� �Է� ��Ȱ��ȭ - ��Ʈ�ѷ� ���� �κ� ����
        if (ACharacter* OtherCharacter = Cast<ACharacter>(NewPlayerActor))
        {
            // ��Ʈ�ѷ� Ŭ������ ��ü Ŭ������ ���� (AController ��� APlayerController ���)
            APlayerController* NewController = GetWorld()->SpawnActor<APlayerController>(APlayerController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            if (NewController)
            {
                OtherCharacter->bUseControllerRotationYaw = false;
                NewController->Possess(OtherCharacter);
                NewController->SetIgnoreMoveInput(true);
                NewController->SetIgnoreLookInput(true);
            }
            else
            {
                // ��Ʈ�ѷ� ���� ���� �� �α�
                UE_LOG(LogTemp, Warning, TEXT("Failed to create controller for other player character"));
            }
        }

        // ĳ���� ���� ����
        FOtherPlayerInfo PlayerInfo;
        PlayerInfo.ClientId = InClientId;
        PlayerInfo.TargetPosition = Position;
        PlayerInfo.TargetRotation = FRotator::ZeroRotator;
        PlayerInfo.PositionInterpolationTime = 0.0f;
        PlayerInfo.RotationInterpolationTime = 0.0f;

        OtherPlayers.Add(NewPlayerActor, PlayerInfo);

        // �������Ʈ �̺�Ʈ ȣ��
        OnOtherPlayerSpawned(NewPlayerActor, InClientId);
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