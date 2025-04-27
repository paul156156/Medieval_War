// MyNetworkGameMode.cpp
#include "MyNetworkGameMode.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"
#include "SimpleNetworking/Public/SimpleNetworkReplicator.h"
#include "OtherCharacter.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AMyNetworkGameMode::AMyNetworkGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyNetworkGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (!NetworkManager)
    {
        NetworkManager = NewObject<USimpleNetworkManager>(this);
    }

    if (!NetworkReplicator)
    {
        NetworkReplicator = NewObject<USimpleNetworkReplicator>(this);

        NetworkReplicator->OnClientIdAssigned.AddDynamic(this, &AMyNetworkGameMode::HandleClientIdAssigned);
        NetworkReplicator->OnPlayerDisconnected.AddDynamic(this, &AMyNetworkGameMode::HandlePlayerDisconnected);
        NetworkReplicator->OnPlayerPositionUpdated.AddDynamic(this, &AMyNetworkGameMode::HandlePlayerPositionUpdated);

    }

    if (NetworkManager && NetworkReplicator)
    {
        NetworkManager->SetReplicator(NetworkReplicator);
    }

    if (bAutoConnect)
    {
        FTimerHandle ConnectTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(ConnectTimerHandle, this, &AMyNetworkGameMode::ConnectToServer, 1.0f, false);
    }
}

void AMyNetworkGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (NetworkManager)
    {
        NetworkManager->TickReceive(DeltaTime);
    }
}

void AMyNetworkGameMode::ConnectToServer()
{
    if (NetworkManager)
    {
        NetworkManager->ConnectToServer(ServerIP, ServerPort);
    }
}

void AMyNetworkGameMode::DisconnectFromServer()
{
    if (NetworkManager)
    {
        NetworkManager->Disconnect();
    }
}

void AMyNetworkGameMode::HandleClientIdAssigned(int32 ClientId)
{
    LocalClientId = ClientId;
    UE_LOG(LogTemp, Display, TEXT("[GameMode] Local ClientId assigned: %d"), LocalClientId);
}

void AMyNetworkGameMode::HandlePlayerDisconnected(int32 ClientId)
{
    if (OtherPlayers.Contains(ClientId))
    {
        AOtherCharacter* DisconnectedPlayer = OtherPlayers[ClientId];
        if (DisconnectedPlayer)
        {
            DisconnectedPlayer->Destroy();
        }
        OtherPlayers.Remove(ClientId);

        UE_LOG(LogTemp, Display, TEXT("[GameMode] Other player disconnected - ClientId: %d"), ClientId);
    }
}

void AMyNetworkGameMode::HandlePlayerPositionUpdated(int32 ClientId, FVector Position, FVector Velocity, EPlayerState State, float Timestamp)
{
    if (ClientId == LocalClientId)
        return;

    AOtherCharacter* OtherPlayer = nullptr;

    if (OtherPlayers.Contains(ClientId))
    {
        OtherPlayer = OtherPlayers[ClientId];
    }
    else
    {
        OtherPlayer = SpawnOtherPlayerCharacter(ClientId, Position);
    }

    if (OtherPlayer)
    {
        OtherPlayer->UpdateTransform(Position, Velocity);
        OtherPlayer->UpdateAnimationState(State);
    }
}

AOtherCharacter* AMyNetworkGameMode::SpawnOtherPlayerCharacter(int32 ClientId, const FVector& SpawnPosition)
{
    if (!OtherPlayerCharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("[GameMode] OtherPlayerCharacterClass is not set!"));
        return nullptr;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AOtherCharacter* NewOtherPlayer = GetWorld()->SpawnActor<AOtherCharacter>(OtherPlayerCharacterClass, SpawnPosition, FRotator::ZeroRotator, SpawnParams);

    if (NewOtherPlayer)
    {
        OtherPlayers.Add(ClientId, NewOtherPlayer);
        NewOtherPlayer->UpdateTransform(SpawnPosition, FVector::ZeroVector);
    }

    return NewOtherPlayer;
}