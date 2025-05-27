// MyGameModeBase.cpp - ���� ������ ����
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"

AMyGameModeBase::AMyGameModeBase()
{
    // �⺻ �÷��̾� ĳ���� Ŭ���� ����
    DefaultPawnClass = AMyCharacter::StaticClass();
    NetworkPlayerClass = AMyCharacter::StaticClass();

    // ��Ʈ��ũ ����
    DefaultServerIp = TEXT("127.0.0.1");
    DefaultServerPort = 9000;
    bAutoConnect = true;
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // ��Ʈ��ũ �Ŵ��� ��������
    NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (!NetworkManager)
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkManager not found!"));
        return;
    }

    // ��Ʈ��ũ �̺�Ʈ ���ε�
    NetworkManager->OnPlayerJoined.AddDynamic(this, &AMyGameModeBase::OnPlayerJoined);
    NetworkManager->OnPlayerLeft.AddDynamic(this, &AMyGameModeBase::OnPlayerLeft);
    NetworkManager->OnPlayerPositionUpdated.AddDynamic(this, &AMyGameModeBase::OnPlayerPositionUpdated);
    NetworkManager->OnPlayerStateChanged.AddDynamic(this, &AMyGameModeBase::OnPlayerStateChanged);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
    NetworkManager->OnConnectionError.AddDynamic(this, &AMyGameModeBase::OnConnectionError);

    // �⺻ ���� ��ġ ����
    SetupDefaultSpawnPoints();

    // ���� �÷��̾� ����
    SetupLocalPlayer();

    // �ڵ� ���� ����
    if (bAutoConnect)
    {
        UE_LOG(LogTemp, Log, TEXT("Auto-connecting to server: %s:%d"), *DefaultServerIp, DefaultServerPort);
        ConnectToServer(DefaultServerIp, DefaultServerPort);
    }

    // �Է� ������Ʈ Ÿ�̸� ���� (20Hz - 0.05�ʸ���)
    GetWorldTimerManager().SetTimer(InputUpdateTimerHandle, this, &AMyGameModeBase::UpdatePlayerInput, 0.05f, true);

    UE_LOG(LogTemp, Log, TEXT("MyGameModeBase initialized"));
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Ÿ�̸� ����
    GetWorldTimerManager().ClearTimer(InputUpdateTimerHandle);

    // ��Ʈ��ũ �̺�Ʈ ����ε�
    if (NetworkManager)
    {
        NetworkManager->OnPlayerJoined.RemoveDynamic(this, &AMyGameModeBase::OnPlayerJoined);
        NetworkManager->OnPlayerLeft.RemoveDynamic(this, &AMyGameModeBase::OnPlayerLeft);
        NetworkManager->OnPlayerPositionUpdated.RemoveDynamic(this, &AMyGameModeBase::OnPlayerPositionUpdated);
        NetworkManager->OnPlayerStateChanged.RemoveDynamic(this, &AMyGameModeBase::OnPlayerStateChanged);
        NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
        NetworkManager->OnConnectionError.RemoveDynamic(this, &AMyGameModeBase::OnConnectionError);
    }

    // ��Ʈ��ũ �÷��̾�� ����
    for (auto& Pair : NetworkPlayers)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            Pair.Value->Destroy();
        }
    }
    NetworkPlayers.Empty();

    Super::EndPlay(EndPlayReason);
}

// ��Ʈ��ũ ���� �Լ��� ����
bool AMyGameModeBase::ConnectToServer(const FString& IpAddress, int32 Port)
{
    if (NetworkManager)
    {
        UE_LOG(LogTemp, Log, TEXT("Attempting to connect to server: %s:%d"), *IpAddress, Port);
        return NetworkManager->ConnectToServer(IpAddress, Port);
    }
    return false;
}

void AMyGameModeBase::DisconnectFromServer()
{
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
    }
}

// �Է� ������Ʈ �Լ� ����
void AMyGameModeBase::UpdatePlayerInput()
{
    if (!NetworkManager || !NetworkManager->IsConnected())
        return;

    // ���� �÷��̾� ã��
    AMyCharacter* LocalCharacter = nullptr;

    // NetworkPlayers���� ���� �÷��̾� ã��
    for (auto& Pair : NetworkPlayers)
    {
        if (Pair.Value && Pair.Value->IsLocalPlayer())
        {
            LocalCharacter = Pair.Value;
            break;
        }
    }

    if (!LocalCharacter)
        return;

    // ���� �Է°� �������� (MyCharacter.h�� public ���������)
    float CurrentForwardInput = LocalCharacter->ForwardInput;
    float CurrentRightInput = LocalCharacter->RightInput;
    float CurrentPitch = LocalCharacter->PitchInput;
    float CurrentYaw = LocalCharacter->YawInput;
    float CurrentRoll = LocalCharacter->RollInput;
    bool bCurrentRunPressed = LocalCharacter->bRunPressed;
    bool bCurrentJumpPressed = LocalCharacter->bJumpPressed;
    bool bCurrentAttackPressed = LocalCharacter->bAttackPressed;

    // �Է� ���� Ȯ��
    bool bInputChanged =
        FMath::Abs(CurrentForwardInput - PreviousForwardInput) > 0.01f ||
        FMath::Abs(CurrentRightInput - PreviousRightInput) > 0.01f ||
        FMath::Abs(CurrentPitch - PreviousPitchInput) > 0.1f ||
        FMath::Abs(CurrentYaw - PreviousYawInput) > 0.1f ||
        FMath::Abs(CurrentRoll - PreviousRollInput) > 0.1f ||
        bCurrentRunPressed != bPreviousRunPressed ||
        bCurrentJumpPressed != bPreviousJumpPressed ||
        bCurrentAttackPressed != bPreviousAttackPressed;

    // ���� ������ ���� Ȯ�� (�������� ������ �� ������ �˸�)
    bool bSendZeroMovement =
        (FMath::Abs(CurrentForwardInput) < 0.01f && FMath::Abs(PreviousForwardInput) >= 0.01f) ||
        (FMath::Abs(CurrentRightInput) < 0.01f && FMath::Abs(PreviousRightInput) >= 0.01f);

    if (bInputChanged || bSendZeroMovement)
    {
        NetworkManager->SendPlayerInput(
            CurrentForwardInput,
            CurrentRightInput,
            CurrentPitch,
            CurrentYaw,
            CurrentRoll,
            bCurrentRunPressed,
            bCurrentJumpPressed,
            bCurrentAttackPressed
        );

        // ���� �� ������Ʈ
        PreviousForwardInput = CurrentForwardInput;
        PreviousRightInput = CurrentRightInput;
        PreviousPitchInput = CurrentPitch;
        PreviousYawInput = CurrentYaw;
        PreviousRollInput = CurrentRoll;
        bPreviousRunPressed = bCurrentRunPressed;
        bPreviousJumpPressed = bCurrentJumpPressed;
        bPreviousAttackPressed = bCurrentAttackPressed;
    }
}

void AMyGameModeBase::OnPlayerJoined(int32 PlayerId)
{
    UE_LOG(LogTemp, Log, TEXT("Player joined: %d"), PlayerId);

    // ���� �÷��̾��� ��� ���� �÷��̾� ����
    if (NetworkManager && PlayerId == NetworkManager->GetCurrentPlayerId())
    {
        if (LocalPlayer)
        {
            LocalPlayer->SetPlayerId(PlayerId);
            LocalPlayer->SetIsLocalPlayer(true);
            LocalPlayer->SetIsRemoteControlled(false);
            NetworkPlayers.Add(PlayerId, LocalPlayer);

            UE_LOG(LogTemp, Log, TEXT("Local player ID set to: %d"), PlayerId);
        }
    }
    else
    {
        // ���� �÷��̾� ����
        AMyCharacter* NewPlayer = CreateNetworkPlayer(PlayerId);
        if (NewPlayer)
        {
            NetworkPlayers.Add(PlayerId, NewPlayer);
            UE_LOG(LogTemp, Log, TEXT("Remote player created: %d"), PlayerId);
        }
    }
}

void AMyGameModeBase::OnPlayerLeft(int32 PlayerId)
{
    UE_LOG(LogTemp, Log, TEXT("Player left: %d"), PlayerId);
    RemoveNetworkPlayer(PlayerId);
}

void AMyGameModeBase::OnPlayerPositionUpdated(int32 PlayerId, FTransform NewTransform, FVector Velocity)
{
    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
    if (Player && Player->IsRemoteControlled())
    {
        // ���� �÷��̾ ���� ��ġ�� ������Ʈ
        Player->UpdateFromNetwork(NewTransform, Velocity, Player->CurrentState);
    }
}

void AMyGameModeBase::OnPlayerStateChanged(int32 PlayerId, EPlayerState NewState)
{
    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
    if (Player)
    {
        // ���� ������Ʈ (����/���� ���)
        FTransform CurrentTransform = Player->GetActorTransform();
        FVector CurrentVelocity = Player->GetVelocity();
        Player->UpdateFromNetwork(CurrentTransform, CurrentVelocity, NewState);
    }
}

void AMyGameModeBase::OnConnectionStatusChanged(bool bIsConnected)
{
    UE_LOG(LogTemp, Log, TEXT("Connection status changed: %s"), bIsConnected ? TEXT("Connected") : TEXT("Disconnected"));

    if (!bIsConnected)
    {
        // ������ ������ ��� ��� ���� �÷��̾� ����
        TArray<int32> PlayersToRemove;
        for (auto& Pair : NetworkPlayers)
        {
            if (Pair.Value && Pair.Value->IsRemoteControlled())
            {
                PlayersToRemove.Add(Pair.Key);
            }
        }

        for (int32 PlayerId : PlayersToRemove)
        {
            RemoveNetworkPlayer(PlayerId);
        }
    }
}

void AMyGameModeBase::OnConnectionError()
{
    UE_LOG(LogTemp, Error, TEXT("Network connection error occurred"));
    // ���⿡ �߰� ���� ó�� ���� ����
}

AMyCharacter* AMyGameModeBase::GetPlayerCharacter(int32 PlayerId)
{
    AMyCharacter** FoundPlayer = NetworkPlayers.Find(PlayerId);
    return FoundPlayer ? *FoundPlayer : nullptr;
}

TArray<AMyCharacter*> AMyGameModeBase::GetAllNetworkPlayers()
{
    TArray<AMyCharacter*> Players;
    for (auto& Pair : NetworkPlayers)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            Players.Add(Pair.Value);
        }
    }
    return Players;
}

int32 AMyGameModeBase::GetLocalPlayerId()
{
    return NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;
}

bool AMyGameModeBase::IsLocalPlayer(int32 PlayerId)
{
    return NetworkManager && PlayerId == NetworkManager->GetCurrentPlayerId();
}

AMyCharacter* AMyGameModeBase::CreateNetworkPlayer(int32 PlayerId)
{
    if (!NetworkPlayerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkPlayerClass not set!"));
        return nullptr;
    }

    // ���� ��ġ ��������
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // �÷��̾� ĳ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMyCharacter* NewPlayer = GetWorld()->SpawnActor<AMyCharacter>(
        NetworkPlayerClass,
        SpawnTransform.GetLocation(),
        SpawnTransform.GetRotation().Rotator(),
        SpawnParams
    );

    if (NewPlayer)
    {
        // ���� �÷��̾�� ����
        NewPlayer->SetPlayerId(PlayerId);
        NewPlayer->SetIsLocalPlayer(false);
        NewPlayer->SetIsRemoteControlled(true);

        UE_LOG(LogTemp, Log, TEXT("Network player created successfully - ID: %d"), PlayerId);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create network player - ID: %d"), PlayerId);
    }

    return NewPlayer;
}

void AMyGameModeBase::RemoveNetworkPlayer(int32 PlayerId)
{
    AMyCharacter** FoundPlayer = NetworkPlayers.Find(PlayerId);
    if (FoundPlayer && *FoundPlayer)
    {
        AMyCharacter* Player = *FoundPlayer;

        // ���� �÷��̾�� �������� ����
        if (!Player->IsLocalPlayer())
        {
            Player->Destroy();
            UE_LOG(LogTemp, Log, TEXT("Network player removed - ID: %d"), PlayerId);
        }

        NetworkPlayers.Remove(PlayerId);
    }
}

void AMyGameModeBase::SetupLocalPlayer()
{
    // ���� �÷��̾� ��Ʈ�ѷ��� �� ��������
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        LocalPlayer = Cast<AMyCharacter>(PC->GetPawn());
        if (LocalPlayer)
        {
            LocalPlayer->SetIsLocalPlayer(true);
            LocalPlayer->SetIsRemoteControlled(false);
            UE_LOG(LogTemp, Log, TEXT("Local player set up successfully"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Local player not found or wrong type"));
        }
    }
}

FTransform AMyGameModeBase::GetSpawnTransform(int32 PlayerId)
{
    // ������ ���� ����Ʈ�� ������ ���
    if (SpawnPoints.Num() > 0)
    {
        int32 SpawnIndex = (PlayerId - 1) % SpawnPoints.Num();
        return SpawnPoints[SpawnIndex];
    }

    // PlayerStart ���͵� ã��
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() > 0)
    {
        int32 StartIndex = (PlayerId - 1) % PlayerStarts.Num();
        return PlayerStarts[StartIndex]->GetActorTransform();
    }

    // �⺻ ��ġ (���� ��ġ)
    float Angle = (2.0f * PI * (PlayerId - 1)) / 8.0f; // 8����� ���� ��ġ
    float Radius = 500.0f;
    FVector SpawnLocation(
        Radius * FMath::Cos(Angle),
        Radius * FMath::Sin(Angle),
        100.0f // ���鿡�� �ణ ��
    );

    return FTransform(FRotator::ZeroRotator, SpawnLocation);
}

void AMyGameModeBase::SetupDefaultSpawnPoints()
{
    // �⺻ ���� ��ġ�� ���� (������ �����ϰ�)
    SpawnPoints.Empty();

    const float Radius = 500.0f;
    const int32 SpawnCount = 8;
    const float GroundLevel = 100.0f;

    for (int32 i = 0; i < SpawnCount; ++i)
    {
        float Angle = (2.0f * PI * i) / SpawnCount;
        FVector SpawnLocation(
            Radius * FMath::Cos(Angle),
            Radius * FMath::Sin(Angle),
            GroundLevel
        );

        SpawnPoints.Add(FTransform(FRotator::ZeroRotator, SpawnLocation));
    }

    // �߾� ���� ��ġ�� �߰�
    SpawnPoints.Add(FTransform(FRotator::ZeroRotator, FVector(0, 0, GroundLevel)));

    UE_LOG(LogTemp, Log, TEXT("Default spawn points set up: %d points"), SpawnPoints.Num());
}