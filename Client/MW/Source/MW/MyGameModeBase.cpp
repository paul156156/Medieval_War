// MyGameModeBase.cpp - 단순화된 구조
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Math/UnrealMathUtility.h"

AMyGameModeBase::AMyGameModeBase()
{
    // 기본 플레이어 캐릭터 클래스 설정 (하나로 통일)
    DefaultPawnClass = AMyCharacter::StaticClass();
    DefaultPlayerClass = AMyCharacter::StaticClass();

    // 네트워크 설정
    DefaultServerIp = TEXT("127.0.0.1");
    DefaultServerPort = 9000;
    bAutoConnect = true;

    // 게임 설정
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
    // 네트워크 매니저 가져오기
    NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (!NetworkManager)
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkManager not found!"));
        return;
    }

    // 네트워크 이벤트 바인딩
    NetworkManager->OnPlayerJoined.AddDynamic(this, &AMyGameModeBase::OnPlayerJoined);
    NetworkManager->OnPlayerLeft.AddDynamic(this, &AMyGameModeBase::OnPlayerLeft);
    NetworkManager->OnPlayerUpdated.AddDynamic(this, &AMyGameModeBase::OnPlayerUpdated);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
    NetworkManager->OnConnectionError.AddDynamic(this, &AMyGameModeBase::OnConnectionError);

    // 기존 로컬 플레이어 제거 (새로 생성할 예정)
    RemoveExistingLocalPlayer();

    // 자동 연결 설정
    if (bAutoConnect)
    {
        UE_LOG(LogTemp, Log, TEXT("Auto-connecting to server: %s:%d"), *DefaultServerIp, DefaultServerPort);
        ConnectToServer(DefaultServerIp, DefaultServerPort);
    }

    bIsInitialized = true;
}

void AMyGameModeBase::CleanupGameMode()
{
    // 타이머 정리
    GetWorldTimerManager().ClearTimer(NetworkUpdateTimerHandle);

    // 네트워크 이벤트 언바인딩
    if (NetworkManager)
    {
        NetworkManager->OnPlayerJoined.RemoveDynamic(this, &AMyGameModeBase::OnPlayerJoined);
        NetworkManager->OnPlayerLeft.RemoveDynamic(this, &AMyGameModeBase::OnPlayerLeft);
        NetworkManager->OnPlayerUpdated.RemoveDynamic(this, &AMyGameModeBase::OnPlayerUpdated);
        NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
        NetworkManager->OnConnectionError.RemoveDynamic(this, &AMyGameModeBase::OnConnectionError);
    }

    // 네트워크 플레이어들 정리
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

// ===== 네트워크 연결 함수들 =====
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

// ===== 네트워크 이벤트 핸들러들 =====
// MyGameModeBase.cpp - 중복 생성 방지 추가

void AMyGameModeBase::OnPlayerJoined(int32 PlayerId)
{
    UE_LOG(LogTemp, Error, TEXT("=== ON PLAYER JOINED CALLED ==="));
    UE_LOG(LogTemp, Error, TEXT("PlayerId: %d"), PlayerId);
    UE_LOG(LogTemp, Error, TEXT("MyID: %d"), NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1);
    UE_LOG(LogTemp, Error, TEXT("Current Players count: %d"), Players.Num());

    // ===== 중복 생성 방지 =====
    if (Players.Contains(PlayerId))
    {
        UE_LOG(LogTemp, Error, TEXT("Player %d already exists! Skipping creation."), PlayerId);
        return;
    }

    // 최대 플레이어 수 체크
    if (Players.Num() >= MaxPlayers && !bAllowLateJoin)
    {
        UE_LOG(LogTemp, Warning, TEXT("Server full! Cannot add player %d"), PlayerId);
        return;
    }

    UE_LOG(LogTemp, Error, TEXT("Creating player character for ID: %d"), PlayerId);

    // 로컬/원격 구분 로직
    int32 MyPlayerId = NetworkManager ? NetworkManager->GetCurrentPlayerId() : -1;
    bool bIsMyPlayer = (PlayerId == MyPlayerId);

    UE_LOG(LogTemp, Error, TEXT("PlayerId %d vs MyPlayerId %d = %s"),
        PlayerId, MyPlayerId, bIsMyPlayer ? TEXT("LOCAL") : TEXT("REMOTE"));

    // 플레이어 생성
    AMyCharacter* NewPlayer = CreatePlayerCharacter(PlayerId);
    if (NewPlayer)
    {
        Players.Add(PlayerId, NewPlayer);
        UE_LOG(LogTemp, Error, TEXT("Player %d added to Players map. New count: %d"), PlayerId, Players.Num());

        if (bIsMyPlayer)
        {
            // ========== 로컬 플레이어 설정 ==========
            UE_LOG(LogTemp, Error, TEXT("Setting up LOCAL player: %d"), PlayerId);

            NewPlayer->SetIsLocalPlayer(true);

            // ===== PlayerController 빙의 (기존 빙의 해제 후) =====
            if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
            {
                // 기존에 빙의된 폰이 있으면 해제
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

                // 스폰 정보 서버에 전송
                NewPlayer->NotifySpawn();
            }
        }
        else
        {
            // ========== 원격 플레이어 설정 ==========
            UE_LOG(LogTemp, Error, TEXT("Setting up REMOTE player: %d"), PlayerId);

            NewPlayer->SetIsLocalPlayer(false);
            // 원격 플레이어는 컨트롤러에 빙의하지 않음!

            UE_LOG(LogTemp, Error, TEXT("Remote player created: ID %d at %s"),
                PlayerId, *NewPlayer->GetActorLocation().ToString());
        }

        // 블루프린트 이벤트 호출
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

    // 블루프린트 이벤트 호출
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

    // 업데이트 시간 기록
    LastPlayerUpdateTime = GetWorld()->GetTimeSeconds();

    // 상세 로그 (필요시)
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
        // 연결이 끊어진 경우 모든 원격 플레이어 제거
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

        // 게임 상태 리셋
        bGameStarted = false;
    }
}

void AMyGameModeBase::OnConnectionError()
{
    UE_LOG(LogTemp, Error, TEXT("Network connection error occurred"));

    // 연결 에러 시 모든 원격 플레이어 제거
    OnConnectionStatusChanged(false);
}

// ===== 플레이어 생성/제거 함수들 =====
AMyCharacter* AMyGameModeBase::CreatePlayerCharacter(int32 PlayerId)
{
    if (!DefaultPlayerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("DefaultPlayerClass not set!"));
        return nullptr;
    }

    // 스폰 위치 계산
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // 스폰 위치 검증
    if (!ValidatePlayerSpawn(PlayerId, SpawnTransform))
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawn validation failed for player %d"), PlayerId);
    }

    UE_LOG(LogTemp, Log, TEXT("Spawning player %d at: %s"), PlayerId, *SpawnTransform.GetLocation().ToString());

    // 플레이어 캐릭터 생성
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

        // 로컬 플레이어는 제거하지 않음 (연결 해제 시에만)
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
    // 기존에 생성된 로컬 플레이어 제거
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

// ===== 플레이어 관리 함수들 =====
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

// ===== 스폰 관련 함수들 =====
FTransform AMyGameModeBase::GetSpawnTransform(int32 PlayerId)
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerStart found, using default spawn location"));
        return FTransform(FRotator::ZeroRotator, DefaultSpawnLocation);
    }

    // PlayerId를 기준으로 안전하게 스폰 위치 선택
    int32 StartIndex = FMath::Abs(PlayerId) % PlayerStarts.Num();
    AActor* SelectedPlayerStart = PlayerStarts[StartIndex];
    FTransform SpawnTransform = SelectedPlayerStart->GetActorTransform();

    // PlayerStart가 부족한 경우 오프셋 추가
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

    // 랜덤 스폰 회전 적용
    if (bUseRandomSpawnRotation)
    {
        FRotator RandomRotation = FRotator(0, FMath::RandRange(0.0f, 360.0f), 0);
        SpawnTransform.SetRotation(RandomRotation.Quaternion());
    }

    return SpawnTransform;
}

// ===== 디버그 함수들 =====
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
            // MyCharacter에 SetDebugMode 함수가 있다면 호출
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

// ===== 헬퍼 함수들 =====
bool AMyGameModeBase::ValidatePlayerSpawn(int32 PlayerId, const FTransform& SpawnTransform)
{
    // 스폰 위치가 다른 플레이어와 너무 가까운지 체크
    FVector SpawnLocation = SpawnTransform.GetLocation();

    for (auto& Pair : Players)
    {
        if (Pair.Value && IsValid(Pair.Value))
        {
            float Distance = FVector::Dist(SpawnLocation, Pair.Value->GetActorLocation());
            if (Distance < 100.0f) // 100유닛 이내
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