// MyNetworkGameMode.cpp
#include "MyNetworkGameMode.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"
#include "SimpleNetworking/Public/SimpleNetworkReplicator.h"
#include "MyCharacter.h"
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
        NetworkReplicator->OnMyInitialPositionReceived.AddDynamic(this, &AMyNetworkGameMode::HandleInitialPositionReceived);
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

void AMyNetworkGameMode::HandlePlayerPositionUpdated(int32 ClientId, FVector Position, float Yaw, float Roll, FVector Velocity, EPlayerState State, float Timestamp)
{
    //if (ClientId == LocalClientId)
    //    return;
    
    if (DeferredCharacter && ClientId == LocalClientId) // 내 캐릭터라면
    {
        DeferredCharacter->SetActorLocation(Position);
    }

    AOtherCharacter* OtherPlayer = nullptr;

    if (OtherPlayers.Contains(ClientId))
    {
        OtherPlayer = OtherPlayers[ClientId];
    }
    else
    {
        OtherPlayer = SpawnOtherPlayerCharacter(ClientId, Position, Yaw, Roll);
    }

    if (OtherPlayer)
    {
        OtherPlayer->UpdateTransform(Position, Yaw, Roll, Velocity);
        OtherPlayer->UpdateAnimationState(State);
    }
}

void AMyNetworkGameMode::HandleInitialPositionReceived(int32 ClientId, FVector Position, FVector Velocity, EPlayerState State)
{
    if (!DeferredCharacter)
    {
        FTransform SpawnTransform;
        SpawnTransform.SetLocation(Position); // 서버에서 받은 초기 위치 적용

        DeferredCharacter = Cast<AMyCharacter>(
            UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AMyCharacter::StaticClass(), SpawnTransform)
        );

        if (!DeferredCharacter)
        {
            UE_LOG(LogTemp, Error, TEXT("[NetworkGameMode] Character Deferred Spawn Fail"));
            return;
        }

        UE_LOG(LogTemp, Warning, TEXT("[NetworkGameMode] Character Deferred Spawn Done, Initial Position Setting"));

        UGameplayStatics::FinishSpawningActor(DeferredCharacter, SpawnTransform);

        UE_LOG(LogTemp, Warning, TEXT("[NetworkGameMode] Character Finish Spawning Done"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[NetworkGameMode] Already Character Exist. Position Update"));
        DeferredCharacter->SetActorLocation(Position);
    }
}

AOtherCharacter* AMyNetworkGameMode::SpawnOtherPlayerCharacter(int32 ClientId, const FVector& SpawnPosition, const float& SpawnYaw, const float& SpawnRoll)
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
        NewOtherPlayer->UpdateTransform(SpawnPosition, SpawnYaw, SpawnRoll, FVector::ZeroVector);
    }

    return NewOtherPlayer;
}