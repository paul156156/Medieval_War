// MultiplayerGameMode.cpp
#include "MultiplayerGameMode.h"
#include "MultiplayerBaseCharacter.h"
#include "MyPlayerCharacter.h"
#include "OtherPlayerCharacter.h"
#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerGameMode::AMultiplayerGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    NetworkManager = nullptr;
    LastForwardInput = 0.0f;
    LastRightInput = 0.0f;
    LastYawRotation = 0.0f;
    bLastJumpPressed = false;
    bLastAttackPressed = false;
    DefaultServerIp = TEXT("127.0.0.1");
    DefaultServerPort = 9000;
    bAutoConnect = true;
}

void AMultiplayerGameMode::BeginPlay()
{
    Super::BeginPlay();

    NetworkManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UNetworkManager>();
    if (NetworkManager)
    {
        NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &AMultiplayerGameMode::OnConnectionStatusChanged);
        NetworkManager->OnPlayerJoined.AddDynamic(this, &AMultiplayerGameMode::OnPlayerJoined);
        NetworkManager->OnPlayerLeft.AddDynamic(this, &AMultiplayerGameMode::OnPlayerLeft);
        NetworkManager->OnPlayerPositionUpdated.AddDynamic(this, &AMultiplayerGameMode::OnPlayerPositionUpdated);
        NetworkManager->OnPlayerStateChanged.AddDynamic(this, &AMultiplayerGameMode::OnPlayerStateChanged);
        NetworkManager->OnConnectionError.AddDynamic(this, &AMultiplayerGameMode::OnConnectionError);

        if (bAutoConnect)
        {
            ConnectToServer(DefaultServerIp, DefaultServerPort);
        }
    }

    GetWorldTimerManager().SetTimer(InputUpdateTimerHandle, this, &AMultiplayerGameMode::UpdatePlayerInput, 0.05f, true);
}

void AMultiplayerGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool AMultiplayerGameMode::ConnectToServer(const FString& IpAddress, int32 Port)
{
    if (NetworkManager)
    {
        return NetworkManager->ConnectToServer(IpAddress, Port);
    }
    return false;
}

void AMultiplayerGameMode::DisconnectFromServer()
{
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
    }
}

ACharacter* AMultiplayerGameMode::SpawnPlayerCharacter(int32 PlayerId, bool bIsLocalPlayer)
{
    // 여러 PlayerStart 중에서 선택
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    AActor* PlayerStart = nullptr;
    if (PlayerStarts.Num() > 0)
    {
        int32 Index = PlayerId % PlayerStarts.Num(); // 순환할 수도 있음
        PlayerStart = PlayerStarts[Index];
    }

    FVector SpawnLocation = PlayerStart ? PlayerStart->GetActorLocation() : FVector(4300, -9100, 100);
    FRotator SpawnRotation = PlayerStart ? PlayerStart->GetActorRotation() : FRotator::ZeroRotator;

    // 클래스 선택
    TSubclassOf<ACharacter> CharacterClass = bIsLocalPlayer ? MyPlayerCharacterClass : OtherPlayerCharacterClass;

    if (!CharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Character class not set for Player ID=%d, IsLocal=%d"),
            PlayerId, bIsLocalPlayer);
        return nullptr;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(CharacterClass, SpawnLocation, SpawnRotation, SpawnParams);

    if (NewCharacter)
    {
        if (AMultiplayerBaseCharacter* BaseChar = Cast<AMultiplayerBaseCharacter>(NewCharacter))
        {
            BaseChar->SetPlayerId(PlayerId);
            BaseChar->SetIsLocalPlayer(bIsLocalPlayer);
        }

        PlayerCharacters.Add(PlayerId, NewCharacter);
        UE_LOG(LogTemp, Log, TEXT("Player Character Spawned: ID=%d, IsLocal=%d at %s"), PlayerId, bIsLocalPlayer, *SpawnLocation.ToString());
    }

    return NewCharacter;
}

void AMultiplayerGameMode::DestroyPlayerCharacter(int32 PlayerId)
{
    if (ACharacter* Character = PlayerCharacters.FindRef(PlayerId))
    {
        Character->Destroy();
        PlayerCharacters.Remove(PlayerId);
    }
}

ACharacter* AMultiplayerGameMode::GetLocalPlayerCharacter() const
{
    for (const auto& Pair : PlayerCharacters)
    {
        const AMultiplayerBaseCharacter* Char = Cast<AMultiplayerBaseCharacter>(Pair.Value);
        if (Char && Char->GetLocalRole() == ROLE_AutonomousProxy)
        {
            return Pair.Value;
        }
    }
    return nullptr;
}

void AMultiplayerGameMode::OnConnectionStatusChanged(bool bIsConnected)
{
    UE_LOG(LogTemp, Log, TEXT("Server Connection Changed: %s"), bIsConnected ? TEXT("Connect") : TEXT("Disconnect"));
}

void AMultiplayerGameMode::OnPlayerJoined(int32 PlayerId)
{
    bool bIsLocalPlayer = (PlayerId == NetworkManager->GetCurrentPlayerId());
    SpawnPlayerCharacter(PlayerId, bIsLocalPlayer);
}

void AMultiplayerGameMode::OnPlayerLeft(int32 PlayerId)
{
    DestroyPlayerCharacter(PlayerId);
}

void AMultiplayerGameMode::OnPlayerPositionUpdated(int32 PlayerId, FTransform NewTransform)
{
    if (AMultiplayerBaseCharacter* Character = Cast<AMultiplayerBaseCharacter>(PlayerCharacters.FindRef(PlayerId)))
    {
        Character->UpdateFromNetwork(NewTransform, Character->GetCharacterMovement()->IsFalling() ? EPlayerState::JUMPING : EPlayerState::IDLE);
    }
}

void AMultiplayerGameMode::OnPlayerStateChanged(int32 PlayerId, EPlayerState NewState)
{
    if (AMultiplayerBaseCharacter* Character = Cast<AMultiplayerBaseCharacter>(PlayerCharacters.FindRef(PlayerId)))
    {
        Character->UpdateFromNetwork(Character->GetActorTransform(), NewState);
    }
}

void AMultiplayerGameMode::OnConnectionError()
{
    UE_LOG(LogTemp, Error, TEXT("서버 연결 오류 발생"));
}

void AMultiplayerGameMode::UpdatePlayerInput()
{
    if (!NetworkManager || !NetworkManager->IsConnected()) return;

    ACharacter* LocalPlayer = GetLocalPlayerCharacter();
    if (!LocalPlayer) return;

    AMultiplayerBaseCharacter* Character = Cast<AMultiplayerBaseCharacter>(LocalPlayer);
    if (!Character) return;

    float CurrentForwardInput = Character->GetInputAxisValue("MoveForward");
    float CurrentRightInput = Character->GetInputAxisValue("MoveRight");
    float CurrentYawRotation = Character->GetControlRotation().Yaw;

    bool bCurrentJumpPressed = Character->GetCharacterMovement()->IsFalling();
    bool bCurrentAttackPressed = false; // 나중에 공격 처리 연동

    bool bInputChanged =
        FMath::Abs(CurrentForwardInput - LastForwardInput) > 0.01f ||
        FMath::Abs(CurrentRightInput - LastRightInput) > 0.01f ||
        FMath::Abs(CurrentYawRotation - LastYawRotation) > 0.1f ||
        bCurrentJumpPressed != bLastJumpPressed ||
        bCurrentAttackPressed != bLastAttackPressed;

    bool bSendZeroInput =
        (FMath::Abs(CurrentForwardInput) < 0.01f && FMath::Abs(LastForwardInput) >= 0.01f) ||
        (FMath::Abs(CurrentRightInput) < 0.01f && FMath::Abs(LastRightInput) >= 0.01f) ||
        (!bCurrentJumpPressed && bLastJumpPressed) ||
        (!bCurrentAttackPressed && bLastAttackPressed);

    if (bInputChanged || bSendZeroInput)
    {
        NetworkManager->SendPlayerInput(
            CurrentForwardInput,
            CurrentRightInput,
            CurrentYawRotation,
            bCurrentJumpPressed,
            bCurrentAttackPressed
        );

        LastForwardInput = CurrentForwardInput;
        LastRightInput = CurrentRightInput;
        LastYawRotation = CurrentYawRotation;
        bLastJumpPressed = bCurrentJumpPressed;
        bLastAttackPressed = bCurrentAttackPressed;
    }
}
