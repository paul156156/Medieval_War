// MyGameModeBase.cpp - 최종 수정된 버전
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"

AMyGameModeBase::AMyGameModeBase()
{
    // 기본 플레이어 캐릭터 클래스 설정
    DefaultPawnClass = AMyCharacter::StaticClass();
    LocalPlayerClass = AMyCharacter::StaticClass();
    RemotePlayerClass = AOtherCharacter::StaticClass();

    // 네트워크 설정
    DefaultServerIp = TEXT("127.0.0.1");
    DefaultServerPort = 9000;
    bAutoConnect = true;
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

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
    NetworkManager->OnPlayerPositionUpdated.AddDynamic(this, &AMyGameModeBase::OnPlayerPositionUpdated);
    NetworkManager->OnPlayerStateChanged.AddDynamic(this, &AMyGameModeBase::OnPlayerStateChanged);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMyGameModeBase::OnConnectionStatusChanged);
    NetworkManager->OnConnectionError.AddDynamic(this, &AMyGameModeBase::OnConnectionError);

    // 기본 스폰 위치 설정
    SetupDefaultSpawnPoints();

    // 로컬 플레이어 설정
    SetupLocalPlayer();

    // 자동 연결 설정
    if (bAutoConnect)
    {
        UE_LOG(LogTemp, Log, TEXT("Auto-connecting to server: %s:%d"), *DefaultServerIp, DefaultServerPort);
        ConnectToServer(DefaultServerIp, DefaultServerPort);
    }

    // 입력 업데이트 타이머 설정 (20Hz - 0.05초마다)
    GetWorldTimerManager().SetTimer(InputUpdateTimerHandle, this, &AMyGameModeBase::UpdatePlayerInput, 0.05f, true);

    UE_LOG(LogTemp, Log, TEXT("MyGameModeBase initialized"));
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 타이머 정리
    GetWorldTimerManager().ClearTimer(InputUpdateTimerHandle);

    // 네트워크 이벤트 언바인딩
    if (NetworkManager)
    {
        NetworkManager->OnPlayerJoined.RemoveDynamic(this, &AMyGameModeBase::OnPlayerJoined);
        NetworkManager->OnPlayerLeft.RemoveDynamic(this, &AMyGameModeBase::OnPlayerLeft);
        NetworkManager->OnPlayerPositionUpdated.RemoveDynamic(this, &AMyGameModeBase::OnPlayerPositionUpdated);
        NetworkManager->OnPlayerStateChanged.RemoveDynamic(this, &AMyGameModeBase::OnPlayerStateChanged);
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

    Super::EndPlay(EndPlayReason);
}

// 네트워크 연결 함수들 구현
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

// 입력 업데이트 함수 구현
void AMyGameModeBase::UpdatePlayerInput()
{
    if (!NetworkManager || !NetworkManager->IsConnected())
        return;

    // 로컬 플레이어 찾기
    AMyCharacter* LocalCharacter = nullptr;

    // Players에서 로컬 플레이어 찾기
    for (auto& Pair : Players)
    {
        if (Pair.Value && Pair.Value->IsLocalPlayer())
        {
            LocalCharacter = Pair.Value;
            break;
        }
    }

    if (!LocalCharacter)
        return;

    // 현재 입력값 가져오기 (MyCharacter.h의 public 멤버변수들)
    float CurrentForwardInput = LocalCharacter->ForwardInput;
    float CurrentRightInput = LocalCharacter->RightInput;
    float CurrentPitch = LocalCharacter->PitchInput;
    float CurrentYaw = LocalCharacter->YawInput;
    float CurrentRoll = LocalCharacter->RollInput;
    bool bCurrentRunPressed = LocalCharacter->bRunPressed;
    bool bCurrentJumpPressed = LocalCharacter->bJumpPressed;
    bool bCurrentAttackPressed = LocalCharacter->bAttackPressed;

    // 입력 변경 확인
    bool bInputChanged =
        FMath::Abs(CurrentForwardInput - PreviousForwardInput) > 0.01f ||
        FMath::Abs(CurrentRightInput - PreviousRightInput) > 0.01f ||
        FMath::Abs(CurrentPitch - PreviousPitchInput) > 0.1f ||
        FMath::Abs(CurrentYaw - PreviousYawInput) > 0.1f ||
        FMath::Abs(CurrentRoll - PreviousRollInput) > 0.1f ||
        bCurrentRunPressed != bPreviousRunPressed ||
        bCurrentJumpPressed != bPreviousJumpPressed ||
        bCurrentAttackPressed != bPreviousAttackPressed;

    // 제로 움직임 전송 확인 (움직임이 멈췄을 때 서버에 알림)
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

        // 이전 값 업데이트
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

    // 로컬 플레이어인 경우 기존 플레이어 설정
    if (NetworkManager && PlayerId == NetworkManager->GetCurrentPlayerId())
    {
        if (LocalPlayer)
        {
            LocalPlayer->SetPlayerId(PlayerId);
            LocalPlayer->SetIsLocalPlayer(true);
            LocalPlayer->SetIsRemoteControlled(false);
            Players.Add(PlayerId, LocalPlayer);

            UE_LOG(LogTemp, Log, TEXT("Local player ID set to: %d"), PlayerId);
        }
    }
    else
    {
        // 원격 플레이어 생성
        AOtherCharacter* NewRemotePlayer = CreateRemotePlayer(PlayerId);
        if (NewRemotePlayer)
        {
            // AMyCharacter*로 캐스팅하여 맵에 저장 (기존 인터페이스 호환성 유지)
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

void AMyGameModeBase::OnPlayerPositionUpdated(int32 PlayerId, FTransform NewTransform, FVector Velocity)
{
    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
    if (!Player) return;

    if (Player->IsRemoteControlled())
    {
        // 원격 플레이어 업데이트
        Player->UpdateFromNetwork(NewTransform, Velocity, Player->CurrentState);

        UE_LOG(LogTemp, VeryVerbose, TEXT("Updated remote player %d: (%.1f, %.1f, %.1f)"),
            PlayerId, NewTransform.GetLocation().X, NewTransform.GetLocation().Y, NewTransform.GetLocation().Z);
    }
    else if (Player->IsLocalPlayer())
    {
        // 로컬 플레이어는 서버 보정이 필요한 경우에만 업데이트
        FVector LocalPos = Player->GetActorLocation();
        FVector ServerPos = NewTransform.GetLocation();
        float PositionError = FVector::Dist(LocalPos, ServerPos);

        // 위치 차이가 크면 서버 위치로 보정
        if (PositionError > 100.0f)
        {
            UE_LOG(LogTemp, Warning, TEXT("Local player position corrected by server: Error=%.1f"), PositionError);
            Player->UpdateFromNetwork(NewTransform, Velocity, Player->CurrentState);
        }
    }
}
void AMyGameModeBase::OnPlayerStateChanged(int32 PlayerId, EPlayerState NewState)
{
    AMyCharacter* Player = GetPlayerCharacter(PlayerId);
    if (Player)
    {
        // 상태 업데이트 (로컬/원격 모두)
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
    }
}

void AMyGameModeBase::OnConnectionError()
{
    UE_LOG(LogTemp, Error, TEXT("Network connection error occurred"));
    // 여기에 추가 오류 처리 로직 구현
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
    if (!LocalPlayer)
    {
        UE_LOG(LogTemp, Error, TEXT("LocalPlayerClass not set!"));
        return nullptr;
    }

    // 스폰 위치 가져오기
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // 플레이어 캐릭터 생성
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
        // 원격 플레이어로 설정
        NewPlayer->SetPlayerId(PlayerId);
        NewPlayer->SetIsLocalPlayer(false);
        NewPlayer->SetIsRemoteControlled(true);

        UE_LOG(LogTemp, Log, TEXT("Player created successfully - ID: %d"), PlayerId);
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

    // 스폰 위치 가져오기
    FTransform SpawnTransform = GetSpawnTransform(PlayerId);

    // 원격 플레이어 캐릭터 생성
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
        // 원격 플레이어로 설정
        NewPlayer->SetPlayerId(PlayerId);
        NewPlayer->SetIsRemoteControlled(true);

        UE_LOG(LogTemp, Log, TEXT("Remote player(OtherCharacter) created successfully - ID: % d at(% .1f, % .1f, % .1f)"),
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

        bool bIsLocal = Player->IsLocalPlayer();
        bool bIsRemote = Player->IsRemoteControlled();

        // 로컬 플레이어는 제거하지 않음
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
    // 현재 플레이어 컨트롤러의 폰 가져오기
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
    // PlayerStart 액터들 찾기
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    // PlayerId에 따라 PlayerStart 선택
    int32 StartIndex = (PlayerId - 1) % PlayerStarts.Num();
    AActor* SelectedPlayerStart = PlayerStarts[StartIndex];

    FTransform SpawnTransform = SelectedPlayerStart->GetActorTransform();

    return SpawnTransform;
}

void AMyGameModeBase::SetupDefaultSpawnPoints()
{
    // 기본 스폰 위치들 설정 (서버와 유사하게)
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

    // 중앙 스폰 위치도 추가
    SpawnPoints.Add(FTransform(FRotator::ZeroRotator, FVector(0, 0, GroundLevel)));

    UE_LOG(LogTemp, Log, TEXT("Default spawn points set up: %d points"), SpawnPoints.Num());
}