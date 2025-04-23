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

    // 네트워크 매니저 생성 및 초기화
    if (!NetworkManager)
    {
        NetworkManager = NewObject<USimpleNetworkManager>(this);

        // 네트워크 이벤트 핸들러 바인딩
        NetworkManager->OnPlayerUpdate.AddDynamic(this, &AMyNetworkGameMode::OnPlayerUpdateReceived);
        NetworkManager->OnClientIdReceived.AddDynamic(this, &AMyNetworkGameMode::OnClientIdReceived);
        NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyNetworkGameMode::OnConnectionStatusChanged);
    }

    // 자동 연결 설정 확인
    if (bAutoConnect)
    {
        FTimerHandle ConnectTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(ConnectTimerHandle, this, &AMyNetworkGameMode::ConnectToServer, 1.0f, false);
    }

    // 플레이어 캐릭터의 상태 변경 이벤트에 바인딩
    if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        PlayerCharacter->OnCharacterStateChanged.AddDynamic(this, &AMyNetworkGameMode::OnCharacterStateChanged);
    }
}

void AMyNetworkGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 서버 연결 해제
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

    // 서버 연결 시도
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

void AMyNetworkGameMode::OnCharacterStateChanged(EPlayerState NewState, const FVector& Position, const FRotator& Rotation)
{
    // 플레이어 상태 변경 시 서버로 전송
    if (!NetworkManager || !NetworkManager->IsConnected())
        return;

    AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (!PlayerCharacter)
        return;

    float ForwardValue = PlayerCharacter->CurrentForwardValue;
    float RightValue = PlayerCharacter->CurrentRightValue;

    // 상태에 따라 다른 패킷 전송
    switch (NewState)
    {
    case EPlayerState::JUMPING:
        NetworkManager->SendJumpPacket(true, Position, NewState);
        break;
    case EPlayerState::ATTACKING:
        NetworkManager->SendAttackPacket(Position, NewState);
        break;
    default:
        NetworkManager->SendMovePacket(ForwardValue, RightValue, Position, Rotation, NewState);
        break;
    }
}

void AMyNetworkGameMode::OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, EPlayerState State)
{
    // 자신의 업데이트는 무시
    if (ClientId == LocalClientId)
        return;

    // 해당 ID의 플레이어가 이미 존재하는지 확인
    AOtherCharacter* ExistingCharacter = nullptr;
    if (OtherPlayers.Contains(ClientId))
    {
        ExistingCharacter = OtherPlayers[ClientId];
    }

    // 존재하지 않으면 새로 생성
    if (!ExistingCharacter || !IsValid(ExistingCharacter))
    {
        ExistingCharacter = SpawnOtherPlayerCharacter(ClientId, Position);
        if (!ExistingCharacter)
            return;
    }

    // 위치 및 상태 업데이트
    ExistingCharacter->UpdateTransform(Position, Rotation);
    ExistingCharacter->UpdateAnimationState(State);
}

void AMyNetworkGameMode::OnClientIdReceived(int32 ClientId)
{
    // 로컬 클라이언트 ID 저장
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

    // 다른 플레이어 캐릭터 스폰
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

        // 플레이어 입력 비활성화
        if (APlayerController* NewController = GetWorld()->SpawnActor<APlayerController>())
        {
            NewPlayerCharacter->bUseControllerRotationYaw = false;
            NewController->Possess(NewPlayerCharacter);
            NewController->SetIgnoreMoveInput(true);
            NewController->SetIgnoreLookInput(true);
        }

        // 캐릭터 정보 저장
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
    // 특정 ID의 플레이어만 제거
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
    // 모든 다른 플레이어 캐릭터 제거
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