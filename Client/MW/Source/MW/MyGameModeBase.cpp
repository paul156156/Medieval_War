// MyGameModeBase.cpp - ������ ���� ����
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Math/UnrealMathUtility.h"

AMyGameModeBase::AMyGameModeBase()
{
    // �⺻ �÷��̾� ĳ���� Ŭ���� ����
    DefaultPawnClass = AMyCharacter::StaticClass();
    LocalPlayerClass = AMyCharacter::StaticClass();
    RemotePlayerClass = AOtherCharacter::StaticClass();

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
    NetworkManager->OnPlayerUpdated.AddDynamic(this, &AMyGameModeBase::OnPlayerUpdated);
    //NetworkManager->OnPlayerStateChanged.AddDynamic(this, &AMyGameModeBase::OnPlayerStateChanged);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
    NetworkManager->OnConnectionError.AddDynamic(this, &AMyGameModeBase::OnConnectionError);

    // ���� �÷��̾� ����
    SetupLocalPlayer();

    // �ڵ� ���� ����
    if (bAutoConnect)
    {
        UE_LOG(LogTemp, Log, TEXT("Auto-connecting to server: %s:%d"), *DefaultServerIp, DefaultServerPort);
        ConnectToServer(DefaultServerIp, DefaultServerPort);
    }

    UE_LOG(LogTemp, Log, TEXT("MyGameModeBase initialized"));
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Ÿ�̹� ����
    GetWorldTimerManager().ClearTimer(InputUpdateTimerHandle);

    // ��Ʈ��ũ �̺�Ʈ ����ε�
    if (NetworkManager)
    {
        NetworkManager->OnPlayerJoined.RemoveDynamic(this, &AMyGameModeBase::OnPlayerJoined);
        NetworkManager->OnPlayerLeft.RemoveDynamic(this, &AMyGameModeBase::OnPlayerLeft);
        NetworkManager->OnPlayerUpdated.RemoveDynamic(this, &AMyGameModeBase::OnPlayerUpdated);
        //NetworkManager->OnPlayerStateChanged.RemoveDynamic(this, &AMyGameModeBase::OnPlayerStateChanged);
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

void AMyGameModeBase::OnPlayerJoined(int32 PlayerId)
{
    UE_LOG(LogTemp, Log, TEXT("Player joined: %d"), PlayerId);

    // ���� �÷��̾��� ��� ���� �÷��̾� ����
    if (NetworkManager && PlayerId == NetworkManager->GetCurrentPlayerId())
    {
        if (LocalPlayer)
        {
            LocalPlayer->SetPlayerId(PlayerId);
            // SetIsLocalPlayer, SetIsRemoteControlled ȣ�� ���� (���� �Լ��� �����)
            Players.Add(PlayerId, LocalPlayer);

            UE_LOG(LogTemp, Log, TEXT("Local player ID set to: %d"), PlayerId);

            LocalPlayer->NotifySpawn();
        }
    }
    else
    {
        // ���� �÷��̾� ����
        AOtherCharacter* NewRemotePlayer = CreateRemotePlayer(PlayerId);
        if (NewRemotePlayer)
        {
            // AMyCharacter*�� ĳ�����Ͽ� �ʿ� ���� (���� �������̽� ȣȯ�� ����)
            Players.Add(PlayerId, Cast<AMyCharacter>(NewRemotePlayer));
            UE_LOG(LogTemp, Log, TEXT("Remote player (OtherCharacter) created: %d"), PlayerId);
        }
    }
}

void AMyGameModeBase::OnPlayerLeft(int32 PlayerId)
{
    UE_LOG(LogTemp, Log, TEXT("Player left: %d"), PlayerId);
    RemovePlayer(PlayerId);
}

void AMyGameModeBase::OnPlayerUpdated(int32 PlayerId, FTransform NewTransform, FVector Velocity, EPlayerState State, EPlayerAction Action)
{
    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
    if (!Player) return;

    Player->UpdateFromNetwork(NewTransform, Velocity, State, Action);

    if (Player->IsRemoteControlled())
    {
        UE_LOG(LogTemp, Log, TEXT("Updated remote player %d: (%.1f, %.1f, %.1f)"),
            PlayerId, NewTransform.GetLocation().X, NewTransform.GetLocation().Y, NewTransform.GetLocation().Z);
    }
    else if (Player->IsLocalPlayer())
    {
        UE_LOG(LogTemp, Log, TEXT("Updated local player %d from server: (%.1f, %.1f, %.1f)"),
            PlayerId, NewTransform.GetLocation().X, NewTransform.GetLocation().Y, NewTransform.GetLocation().Z);
    }
}

//void AMyGameModeBase::OnPlayerStateChanged(int32 PlayerId, EPlayerState NewState)
//{
//    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
//    if (Player)
//    {
//        // ���� ������Ʈ (����/���� ���)
//        FTransform CurrentTransform = Player->GetActorTransform();
//        FVector CurrentVelocity = Player->GetVelocity();
//        Player->UpdateFromNetwork(CurrentTransform, CurrentVelocity, NewState);
//    }
//}

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
    }
}

void AMyGameModeBase::OnConnectionError()
{
    UE_LOG(LogTemp, Error, TEXT("Network connection error occurred"));
    // ���⿡ �߰� ���� ó�� ���� ����
}

AMyCharacter* AMyGameModeBase::GetPlayerCharacter(int32 PlayerId)
{
    AMyCharacter** FoundPlayer = Players.Find(PlayerId);
    return FoundPlayer ? *FoundPlayer : nullptr;
}

TArray<AMyCharacter*> AMyGameModeBase::GetAllPlayers()
{
    TArray<AMyCharacter*> Player;
    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            Player.Add(Pair.Value);
        }
    }
    return Player;
}

int32 AMyGameModeBase::GetLocalPlayerId()
{
    return NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;
}

bool AMyGameModeBase::IsLocalPlayer(int32 PlayerId)
{
    return NetworkManager && PlayerId == NetworkManager->GetCurrentPlayerId();
}

AMyCharacter* AMyGameModeBase::CreateLocalPlayer(int32 PlayerId)
{
    if (!LocalPlayerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("LocalPlayerClass not set!"));
        return nullptr;
    }

    // ���� ��ġ ��������
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // �÷��̾� ĳ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMyCharacter* NewPlayer = GetWorld()->SpawnActor<AMyCharacter>(
        LocalPlayerClass,
        SpawnTransform.GetLocation(),
        SpawnTransform.GetRotation().Rotator(),
        SpawnParams
    );

    if (NewPlayer)
    {
        // ���� �÷��̾�� ����
        NewPlayer->SetPlayerId(PlayerId);
        // MyCharacter�� �⺻������ ���� �÷��̾��̹Ƿ� �߰� ���� ���ʿ�

        UE_LOG(LogTemp, Log, TEXT("Local player created successfully - ID: %d"), PlayerId);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create local player - ID: %d"), PlayerId);
    }

    return NewPlayer;
}

AOtherCharacter* AMyGameModeBase::CreateRemotePlayer(int32 PlayerId)
{
    if (!RemotePlayerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("RemotePlayerClass not set!"));
        return nullptr;
    }

    // ���� ��ġ ��������
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // ���� �÷��̾� ĳ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AOtherCharacter* NewPlayer = GetWorld()->SpawnActor<AOtherCharacter>(
        RemotePlayerClass,
        SpawnTransform.GetLocation(),
        SpawnTransform.GetRotation().Rotator(),
        SpawnParams
    );

    if (NewPlayer)
    {
        // ���� �÷��̾�� ����
        NewPlayer->SetPlayerId(PlayerId);
        // OtherCharacter�� �⺻������ ���� �÷��̾��̹Ƿ� �߰� ���� ���ʿ�

        UE_LOG(LogTemp, Log, TEXT("Remote player(OtherCharacter) created successfully - ID: %d at (%.1f, %.1f, %.1f)"),
            PlayerId, SpawnTransform.GetLocation().X, SpawnTransform.GetLocation().Y, SpawnTransform.GetLocation().Z);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create remote player - ID: %d"), PlayerId);
    }

    return NewPlayer;
}

void AMyGameModeBase::RemovePlayer(int32 PlayerId)
{
    AMyCharacter** FoundPlayer = Players.Find(PlayerId);
    if (FoundPlayer && *FoundPlayer)
    {
        AMyCharacter* Player = *FoundPlayer;

        // ���� �÷��̾�� �������� ����
        if (!Player->IsLocalPlayer())
        {
            Player->Destroy();
            UE_LOG(LogTemp, Log, TEXT("Network player removed - ID: %d"), PlayerId);
        }

        Players.Remove(PlayerId);
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
            // MyCharacter�� �⺻������ ���� �÷��̾��̹Ƿ� �߰� ���� ���ʿ�
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
    // PlayerStart ���͵� ã��
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0)
    {
        // PlayerStart�� ������ �⺻ ��ġ ��ȯ
        UE_LOG(LogTemp, Warning, TEXT("No PlayerStart found, using default spawn location"));
        return FTransform(FRotator::ZeroRotator, FVector(0, 0, 100));
    }

    // PlayerId�� ���� PlayerStart ����
    int32 StartIndex = (PlayerId - 1) % PlayerStarts.Num();
    AActor* SelectedPlayerStart = PlayerStarts[StartIndex];

    FTransform SpawnTransform = SelectedPlayerStart->GetActorTransform();

    return SpawnTransform;
}