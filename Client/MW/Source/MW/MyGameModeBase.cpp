// MyGameModeBase.cpp - �ܼ�ȭ�� ����
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Math/UnrealMathUtility.h"

AMyGameModeBase::AMyGameModeBase()
{
    // �⺻ �÷��̾� ĳ���� Ŭ���� ���� (�ϳ��� ����)
    DefaultPawnClass = AMyCharacter::StaticClass();
    DefaultPlayerClass = AMyCharacter::StaticClass();

    // ��Ʈ��ũ ����
    DefaultServerIp = TEXT("127.0.0.1");
    DefaultServerPort = 9000;
    bAutoConnect = true;

    // ���� ����
    MaxPlayers = 8;
    bAllowLateJoin = true;
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    InitializeGameMode();

    UE_LOG(LogTemp, Log, TEXT("MyGameModeBase initialized"));
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CleanupGameMode();
    Super::EndPlay(EndPlayReason);
}

void AMyGameModeBase::InitializeGameMode()
{
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
    NetworkManager->OnPlayerUpdated.AddDynamic(this, &AMyGameModeBase::OnPlayerUpdated);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
    NetworkManager->OnConnectionError.AddDynamic(this, &AMyGameModeBase::OnConnectionError);

    // ���� ���� �÷��̾� ���� (���� ������ ����)
    RemoveExistingLocalPlayer();

    // �ڵ� ���� ����
    if (bAutoConnect)
    {
        UE_LOG(LogTemp, Log, TEXT("Auto-connecting to server: %s:%d"), *DefaultServerIp, DefaultServerPort);
        ConnectToServer(DefaultServerIp, DefaultServerPort);
    }

    bIsInitialized = true;
}

void AMyGameModeBase::CleanupGameMode()
{
    // Ÿ�̸� ����
    GetWorldTimerManager().ClearTimer(NetworkUpdateTimerHandle);

    // ��Ʈ��ũ �̺�Ʈ ����ε�
    if (NetworkManager)
    {
        NetworkManager->OnPlayerJoined.RemoveDynamic(this, &AMyGameModeBase::OnPlayerJoined);
        NetworkManager->OnPlayerLeft.RemoveDynamic(this, &AMyGameModeBase::OnPlayerLeft);
        NetworkManager->OnPlayerUpdated.RemoveDynamic(this, &AMyGameModeBase::OnPlayerUpdated);
        NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
        NetworkManager->OnConnectionError.RemoveDynamic(this, &AMyGameModeBase::OnConnectionError);
    }

    // ��Ʈ��ũ �÷��̾�� ����
    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            Pair.Value->Destroy();
        }
    }
    Players.Empty();

    bIsInitialized = false;
}

// ===== ��Ʈ��ũ ���� �Լ��� =====
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

// ===== ��Ʈ��ũ �̺�Ʈ �ڵ鷯�� =====
// MyGameModeBase.cpp - �ߺ� ���� ���� �߰�

void AMyGameModeBase::OnPlayerJoined(int32 PlayerId)
{
    UE_LOG(LogTemp, Error, TEXT("=== ON PLAYER JOINED CALLED ==="));
    UE_LOG(LogTemp, Error, TEXT("PlayerId: %d"), PlayerId);
    UE_LOG(LogTemp, Error, TEXT("MyID: %d"), NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1);
    UE_LOG(LogTemp, Error, TEXT("Current Players count: %d"), Players.Num());

    // ===== �ߺ� ���� ���� =====
    if (Players.Contains(PlayerId))
    {
        UE_LOG(LogTemp, Error, TEXT("Player %d already exists! Skipping creation."), PlayerId);
        return;
    }

    // �ִ� �÷��̾� �� üũ
    if (Players.Num() >= MaxPlayers && !bAllowLateJoin)
    {
        UE_LOG(LogTemp, Warning, TEXT("Server full! Cannot add player %d"), PlayerId);
        return;
    }

    UE_LOG(LogTemp, Error, TEXT("Creating player character for ID: %d"), PlayerId);

    // ����/���� ���� ����
    int32 MyPlayerId = NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;
    bool bIsMyPlayer = (PlayerId == MyPlayerId);

    UE_LOG(LogTemp, Error, TEXT("PlayerId %d vs MyPlayerId %d = %s"),
        PlayerId, MyPlayerId, bIsMyPlayer ? TEXT("LOCAL") : TEXT("REMOTE"));

    // �÷��̾� ����
    AMyCharacter* NewPlayer = CreatePlayerCharacter(PlayerId);
    if (NewPlayer)
    {
        Players.Add(PlayerId, NewPlayer);
        UE_LOG(LogTemp, Error, TEXT("Player %d added to Players map. New count: %d"), PlayerId, Players.Num());

        if (bIsMyPlayer)
        {
            // ========== ���� �÷��̾� ���� ==========
            UE_LOG(LogTemp, Error, TEXT("Setting up LOCAL player: %d"), PlayerId);

            NewPlayer->SetIsLocalPlayer(true);

            // ===== PlayerController ���� (���� ���� ���� ��) =====
            if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
            {
                // ������ ���ǵ� ���� ������ ����
                if (APawn* CurrentPawn = PC->GetPawn())
                {
                    if (CurrentPawn != NewPlayer)
                    {
                        UE_LOG(LogTemp, Error, TEXT("Unpossessing previous pawn: %s"), *CurrentPawn->GetName());
                        PC->UnPossess();
                    }
                }

                PC->Possess(NewPlayer);
                UE_LOG(LogTemp, Error, TEXT("Local player possessed: ID %d"), PlayerId);

                // ���� ���� ������ ����
                NewPlayer->NotifySpawn();
            }
        }
        else
        {
            // ========== ���� �÷��̾� ���� ==========
            UE_LOG(LogTemp, Error, TEXT("Setting up REMOTE player: %d"), PlayerId);

            NewPlayer->SetIsLocalPlayer(false);
            // ���� �÷��̾�� ��Ʈ�ѷ��� �������� ����!

            UE_LOG(LogTemp, Error, TEXT("Remote player created: ID %d at %s"),
                PlayerId, *NewPlayer->GetActorLocation().ToString());
        }

        // �������Ʈ �̺�Ʈ ȣ��
        OnPlayerConnected(PlayerId);

        LogPlayerAction(PlayerId, TEXT("JOINED"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("FAILED to create player %d!"), PlayerId);
    }
}

void AMyGameModeBase::OnPlayerLeft(int32 PlayerId)
{
    UE_LOG(LogTemp, Log, TEXT("Player left: %d"), PlayerId);

    // �������Ʈ �̺�Ʈ ȣ��
    OnPlayerDisconnected(PlayerId);

    LogPlayerAction(PlayerId, TEXT("LEFT"));

    RemovePlayer(PlayerId);
}

void AMyGameModeBase::OnPlayerUpdated(int32 PlayerId, FTransform NewTransform, FVector Velocity, EPlayerState State, EPlayerAction Action)
{
    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
    if (!Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player %d not found for update!"), PlayerId);
        return;
    }

    Player->UpdateFromNetwork(NewTransform, Velocity, State, Action);

    // ������Ʈ �ð� ���
    LastPlayerUpdateTime = GetWorld()->GetTimeSeconds();

    // �� �α� (�ʿ��)
    if (Player->IsRemoteControlled())
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Updated remote player %d: (%.1f, %.1f, %.1f)"),
            PlayerId, NewTransform.GetLocation().X, NewTransform.GetLocation().Y, NewTransform.GetLocation().Z);
    }
    else if (Player->IsLocalPlayer())
    {
        UE_LOG(LogTemp, VeryVerbose, TEXT("Updated local player %d from server: (%.1f, %.1f, %.1f)"),
            PlayerId, NewTransform.GetLocation().X, NewTransform.GetLocation().Y, NewTransform.GetLocation().Z);
    }
}

void AMyGameModeBase::OnConnectionStatusChanged(bool bIsConnected)
{
    UE_LOG(LogTemp, Log, TEXT("Connection status changed: %s"), bIsConnected ? TEXT("Connected") : TEXT("Disconnected"));

    if (!bIsConnected)
    {
        // ������ ������ ��� ��� ���� �÷��̾� ����
        TArray<int32> PlayersToRemove;
        for (auto& Pair : Players)
        {
            if (Pair.Value && Pair.Value->IsRemoteControlled())
            {
                PlayersToRemove.Add(Pair.Key);
            }
        }

        for (int32 PlayerId : PlayersToRemove)
        {
            RemovePlayer(PlayerId);
        }

        // ���� ���� ����
        bGameStarted = false;
    }
}

void AMyGameModeBase::OnConnectionError()
{
    UE_LOG(LogTemp, Error, TEXT("Network connection error occurred"));

    // ���� ���� �� ��� ���� �÷��̾� ����
    OnConnectionStatusChanged(false);
}

// ===== �÷��̾� ����/���� �Լ��� =====
AMyCharacter* AMyGameModeBase::CreatePlayerCharacter(int32 PlayerId)
{
    if (!DefaultPlayerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("DefaultPlayerClass not set!"));
        return nullptr;
    }

    // ���� ��ġ ���
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // ���� ��ġ ����
    if (!ValidatePlayerSpawn(PlayerId, SpawnTransform))
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawn validation failed for player %d"), PlayerId);
    }

    UE_LOG(LogTemp, Log, TEXT("Spawning player %d at: %s"), PlayerId, *SpawnTransform.GetLocation().ToString());

    // �÷��̾� ĳ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMyCharacter* NewPlayer = GetWorld()->SpawnActor<AMyCharacter>(
        DefaultPlayerClass,
        SpawnTransform.GetLocation(),
        SpawnTransform.GetRotation().Rotator(),
        SpawnParams
    );

    if (NewPlayer)
    {
        NewPlayer->SetPlayerId(PlayerId);
        UE_LOG(LogTemp, Log, TEXT("Player character created successfully - ID: %d"), PlayerId);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create player character - ID: %d"), PlayerId);
    }

    return NewPlayer;
}

void AMyGameModeBase::RemovePlayer(int32 PlayerId)
{
    AMyCharacter** FoundPlayer = Players.Find(PlayerId);
    if (FoundPlayer && *FoundPlayer)
    {
        AMyCharacter* Player = *FoundPlayer;

        // ���� �÷��̾�� �������� ���� (���� ���� �ÿ���)
        if (!Player->IsLocalPlayer())
        {
            Player->Destroy();
            UE_LOG(LogTemp, Log, TEXT("Remote player removed - ID: %d"), PlayerId);
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Local player %d marked for removal (but not destroyed)"), PlayerId);
        }

        Players.Remove(PlayerId);
    }
}

void AMyGameModeBase::RemoveExistingLocalPlayer()
{
    // ������ ������ ���� �÷��̾� ����
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (APawn* ExistingPawn = PC->GetPawn())
        {
            PC->UnPossess();
            ExistingPawn->Destroy();
            UE_LOG(LogTemp, Log, TEXT("Removed existing local player"));
        }
    }
}

// ===== �÷��̾� ���� �Լ��� =====
AMyCharacter* AMyGameModeBase::GetPlayerCharacter(int32 PlayerId)
{
    AMyCharacter** FoundPlayer = Players.Find(PlayerId);
    return FoundPlayer ? *FoundPlayer : nullptr;
}

TArray<AMyCharacter*> AMyGameModeBase::GetAllPlayers()
{
    TArray<AMyCharacter*> AllPlayers;
    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            AllPlayers.Add(Pair.Value);
        }
    }
    return AllPlayers;
}

int32 AMyGameModeBase::GetLocalPlayerId()
{
    return NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;
}

bool AMyGameModeBase::IsLocalPlayer(int32 PlayerId)
{
    return NetworkManager && PlayerId == NetworkManager->GetCurrentPlayerId();
}

// ===== ���� ���� �Լ��� =====
FTransform AMyGameModeBase::GetSpawnTransform(int32 PlayerId)
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerStart found, using default spawn location"));
        return FTransform(FRotator::ZeroRotator, DefaultSpawnLocation);
    }

    // PlayerId�� �������� �����ϰ� ���� ��ġ ����
    int32 StartIndex = FMath::Abs(PlayerId) % PlayerStarts.Num();
    AActor* SelectedPlayerStart = PlayerStarts[StartIndex];
    FTransform SpawnTransform = SelectedPlayerStart->GetActorTransform();

    // PlayerStart�� ������ ��� ������ �߰�
    if (PlayerStarts.Num() < Players.Num() + 1)
    {
        float AngleStep = 360.0f / FMath::Max(1, Players.Num() + 1);
        float Angle = FMath::DegreesToRadians(AngleStep * PlayerId);

        FVector Offset = FVector(
            FMath::Cos(Angle) * PlayerSpawnRadius,
            FMath::Sin(Angle) * PlayerSpawnRadius,
            0.0f
        );

        SpawnTransform.AddToTranslation(Offset);

        UE_LOG(LogTemp, Log, TEXT("Added circular offset for Player %d: %s (Angle: %.1f)"),
            PlayerId, *Offset.ToString(), FMath::RadiansToDegrees(Angle));
    }

    // ���� ���� ȸ�� ����
    if (bUseRandomSpawnRotation)
    {
        FRotator RandomRotation = FRotator(0, FMath::RandRange(0.0f, 360.0f), 0);
        SpawnTransform.SetRotation(RandomRotation.Quaternion());
    }

    return SpawnTransform;
}

// ===== ����� �Լ��� =====
void AMyGameModeBase::PrintAllPlayersInfo()
{
    UE_LOG(LogTemp, Warning, TEXT("=== PLAYERS INFO ==="));
    UE_LOG(LogTemp, Warning, TEXT("Total Players: %d"), Players.Num());

    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            AMyCharacter* Player = Pair.Value;
            FVector Location = Player->GetActorLocation();

            UE_LOG(LogTemp, Warning, TEXT("Player %d: %s at (%.1f, %.1f, %.1f)"),
                Pair.Key,
                Player->IsLocalPlayer() ? TEXT("LOCAL") : TEXT("REMOTE"),
                Location.X, Location.Y, Location.Z);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player %d: INVALID"), Pair.Key);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("=================="));
}

void AMyGameModeBase::SetDebugModeForAllPlayers(bool bEnabled)
{
    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            // MyCharacter�� SetDebugMode �Լ��� �ִٸ� ȣ��
            // Pair.Value->SetDebugMode(bEnabled);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Debug mode %s for all players"),
        bEnabled ? TEXT("ENABLED") : TEXT("DISABLED"));
}

FString AMyGameModeBase::GetGameModeStatus()
{
    int32 LocalPlayers = 0;
    int32 RemotePlayers = 0;

    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            if (Pair.Value->IsLocalPlayer())
                LocalPlayers++;
            else
                RemotePlayers++;
        }
    }

    FString ConnectionStatus = NetworkManager && NetworkManager->IsConnected() ?
        TEXT("Connected") : TEXT("Disconnected");

    return FString::Printf(TEXT("GameMode: %s | Players: %d (Local: %d, Remote: %d) | Started: %s"),
        *ConnectionStatus, Players.Num(), LocalPlayers, RemotePlayers,
        bGameStarted ? TEXT("Yes") : TEXT("No"));
}

// ===== ���� �Լ��� =====
bool AMyGameModeBase::ValidatePlayerSpawn(int32 PlayerId, const FTransform& SpawnTransform)
{
    // ���� ��ġ�� �ٸ� �÷��̾�� �ʹ� ������� üũ
    FVector SpawnLocation = SpawnTransform.GetLocation();

    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            float Distance = FVector::Dist(SpawnLocation, Pair.Value->GetActorLocation());
            if (Distance < 100.0f) // 100���� �̳�
            {
                UE_LOG(LogTemp, Warning, TEXT("Player %d spawn too close to player %d (Distance: %.1f)"),
                    PlayerId, Pair.Key, Distance);
                return false;
            }
        }
    }

    return true;
}

void AMyGameModeBase::LogPlayerAction(int32 PlayerId, const FString& Action)
{
    UE_LOG(LogTemp, Log, TEXT("[PLAYER ACTION] Player %d: %s at %.2f seconds"),
        PlayerId, *Action, GetWorld()->GetTimeSeconds());
}