// MyNetworkGameMode.cpp
#include "MyNetworkGameMode.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"
#include "MyCharacter.h"
#include "OtherCharacter.h"
#include "Kismet/GameplayStatics.h"

AMyNetworkGameMode::AMyNetworkGameMode()
    : NetworkManager(nullptr)
    , ServerIP(TEXT("127.0.0.1"))
    , ServerPort(9000)
    , bAutoConnect(false)
    , LocalClientId(-1)
{
}

void AMyNetworkGameMode::BeginPlay()
{
    Super::BeginPlay();

    // ��Ʈ��ũ �Ŵ��� ���� �� �ʱ�ȭ
    if (!NetworkManager)
    {
        NetworkManager = NewObject<USimpleNetworkManager>(this);

        // ��Ʈ��ũ �̺�Ʈ �ڵ鷯 ���ε�
        NetworkManager->OnPlayerUpdate.AddDynamic(this, &AMyNetworkGameMode::OnPlayerUpdateReceived);
        NetworkManager->OnClientIdReceived.AddDynamic(this, &AMyNetworkGameMode::OnClientIdReceived);
        NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyNetworkGameMode::OnConnectionStatusChanged);
    }

    // �ڵ� ���� ���� Ȯ��
    if (bAutoConnect)
    {
        FTimerHandle ConnectTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(ConnectTimerHandle, this, &AMyNetworkGameMode::ConnectToServer, 1.0f, false);
    }
}

void AMyNetworkGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // ���� ���� ����
    DisconnectFromServer();

    Super::EndPlay(EndPlayReason);
}

void AMyNetworkGameMode::ConnectToServer()
{
    if (!NetworkManager)
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkManager is null"));
        OnServerConnectionFailed();
        return;
    }

    // ���� ���� �õ�
    bool bConnected = NetworkManager->ConnectToServer(ServerIP, ServerPort);

    if (bConnected)
    {
        UE_LOG(LogTemp, Display, TEXT("Successfully connected to server %s:%d"), *ServerIP, ServerPort);
        OnServerConnected();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server %s:%d"), *ServerIP, ServerPort);
        OnServerConnectionFailed();
    }
}

void AMyNetworkGameMode::DisconnectFromServer()
{
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->DisconnectFromServer();
        OnServerDisconnected();
    }
}

void AMyNetworkGameMode::OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, EPlayerState State)
{
    // �ڽ��� ������Ʈ�� ����
    if (ClientId == LocalClientId)
        return;

    // �ش� ID�� �÷��̾ �̹� �����ϴ��� Ȯ��
    AOtherCharacter* ExistingCharacter = nullptr;
    if (OtherPlayers.Contains(ClientId))
    {
        ExistingCharacter = OtherPlayers[ClientId];
    }

    // �������� ������ ���� ����
    if (!ExistingCharacter || !IsValid(ExistingCharacter))
    {
        ExistingCharacter = SpawnOtherPlayerCharacter(ClientId, Position);
        if (!ExistingCharacter)
            return;
    }

    // ��ġ �� ���� ������Ʈ
    ExistingCharacter->UpdateTransform(Position, Rotation, Velocity);
    ExistingCharacter->UpdateAnimationState(State);
}

void AMyNetworkGameMode::OnClientIdReceived(int32 ClientId)
{
    // ���� Ŭ���̾�Ʈ ID ����
    LocalClientId = ClientId;
    UE_LOG(LogTemp, Display, TEXT("Client ID received: %d"), LocalClientId);
}

void AMyNetworkGameMode::OnConnectionStatusChanged(bool IsConnected)
{
    if (IsConnected)
    {
        UE_LOG(LogTemp, Display, TEXT("Connected to server"));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Disconnected from server"));
        RemoveAllOtherPlayers();
    }
}

AOtherCharacter* AMyNetworkGameMode::SpawnOtherPlayerCharacter(int32 ClientId, const FVector& Position)
{
    if (!GetWorld() || !OtherPlayerCharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player: Invalid World or Character Class"));
        return nullptr;
    }

    // �ٸ� �÷��̾� ĳ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AOtherCharacter* NewPlayerCharacter = GetWorld()->SpawnActor<AOtherCharacter>(
        OtherPlayerCharacterClass,
        Position,
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (NewPlayerCharacter)
    {
        UE_LOG(LogTemp, Display, TEXT("Spawned other player character for client ID %d at: X=%.2f Y=%.2f Z=%.2f"),
            ClientId, Position.X, Position.Y, Position.Z);

        // ĳ���� ���� ����
        OtherPlayers.Add(ClientId, NewPlayerCharacter);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player character!"));
    }

    return NewPlayerCharacter;
}

void AMyNetworkGameMode::RemoveOtherPlayerCharacter(int32 ClientId)
{
    // Ư�� ID�� �÷��̾ ����
    if (OtherPlayers.Contains(ClientId))
    {
        AOtherCharacter* CharacterToRemove = OtherPlayers[ClientId];
        if (CharacterToRemove && IsValid(CharacterToRemove))
        {
            CharacterToRemove->Destroy();
            OtherPlayers.Remove(ClientId);
            UE_LOG(LogTemp, Display, TEXT("Removed player character for client ID: %d"), ClientId);
        }
    }
}

void AMyNetworkGameMode::RemoveAllOtherPlayers()
{
    // ��� �ٸ� �÷��̾� ĳ���� ����
    for (auto& Pair : OtherPlayers)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            Pair.Value->Destroy();
        }
    }

    OtherPlayers.Empty();
    UE_LOG(LogTemp, Display, TEXT("All other player characters removed"));
}