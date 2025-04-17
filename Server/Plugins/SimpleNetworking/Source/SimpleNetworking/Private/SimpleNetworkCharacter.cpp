// SimpleNetworkCharacter.cpp
#include "SimpleNetworkCharacter.h"
#include "SimpleNetworkManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "SimpleNetworkGameMode.h"

ASimpleNetworkCharacter::ASimpleNetworkCharacter()
    : NetworkManager(nullptr)
    , bEnableNetworkUpdates(true)
    , PositionUpdateInterval(0.1f)
    , LocalClientId(-1)
    , LastPositionSentTime(0.0f)
{
    // Tick 함수 활성화
    PrimaryActorTick.bCanEverTick = true;
}

void ASimpleNetworkCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // 네트워크 매니저 초기화
    InitializeNetworkManager();
}

void ASimpleNetworkCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 네트워크 이벤트 핸들러 해제
    UnbindNetworkEvents();
    
    Super::EndPlay(EndPlayReason);
}

void ASimpleNetworkCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // 플레이어가 로컬 컨트롤러를 가지고 있고, 네트워크 업데이트가 활성화된 경우
    if (IsLocallyControlled() && bEnableNetworkUpdates && NetworkManager && NetworkManager->IsConnected())
    {
        // 위치 업데이트 간격 체크
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastPositionSentTime >= PositionUpdateInterval)
        {
            // 서버에 위치 정보 전송
            SendPositionToServer();
            LastPositionSentTime = CurrentTime;
        }
    }
    
    // 다른 플레이어 캐릭터 위치 보간 처리
    UpdateOtherPlayerCharacters(DeltaTime);
}

void ASimpleNetworkCharacter::InitializeNetworkManager()
{
    // 게임 모드에서 네트워크 매니저 가져오기
    if (ASimpleNetworkGameMode* GameMode = Cast<ASimpleNetworkGameMode>(GetWorld()->GetAuthGameMode()))
    {
        NetworkManager = GameMode->GetNetworkManager();
        
        if (NetworkManager)
        {
            // 이전 델리게이트 바인딩 제거 (안전을 위해)
            UnbindNetworkEvents();
            
            // 새 델리게이트 바인딩
            BindNetworkEvents();
            
            UE_LOG(LogTemp, Display, TEXT("Network Manager initialized"));
            
            // 이미 ID가 할당되어 있는 경우 적용
            LocalClientId = NetworkManager->GetClientId();
            UE_LOG(LogTemp, Display, TEXT("Local Client ID: %d"), LocalClientId);
        }
    }
}

void ASimpleNetworkCharacter::BindNetworkEvents()
{
    if (!NetworkManager)
    {
        return;
    }
    
    // 델리게이트 바인딩
    NetworkManager->OnPlayerUpdate.AddDynamic(this, &ASimpleNetworkCharacter::OnPlayerUpdateReceived_Implementation);
    NetworkManager->OnClientIdReceived.AddDynamic(this, &ASimpleNetworkCharacter::OnClientIdReceived_Implementation);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &ASimpleNetworkCharacter::OnConnectionStatusChanged);
}

void ASimpleNetworkCharacter::UnbindNetworkEvents()
{
    if (!NetworkManager)
    {
        return;
    }
    
    // 델리게이트 바인딩 해제
    NetworkManager->OnPlayerUpdate.RemoveDynamic(this, &ASimpleNetworkCharacter::OnPlayerUpdateReceived_Implementation);
    NetworkManager->OnClientIdReceived.RemoveDynamic(this, &ASimpleNetworkCharacter::OnClientIdReceived_Implementation);
    NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &ASimpleNetworkCharacter::OnConnectionStatusChanged);
}

void ASimpleNetworkCharacter::SendPositionToServer()
{
    if (!NetworkManager)
    {
        return;
    }
    
    // 현재 위치와 회전값 가져오기
    FVector CurrentLocation = GetActorLocation();
    FRotator CurrentRotation = GetActorRotation();
    
    // 이동 중인지 확인 (속도 체크)
    float ForwardValue = 0.0f;
    float RightValue = 0.0f;
    
    if (Controller && Controller->IsLocalPlayerController())
    {
        ForwardValue = GetInputAxisValue("MoveForward");
        RightValue = GetInputAxisValue("MoveRight");
    }
    
    // 이동 패킷 전송
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void ASimpleNetworkCharacter::Jump()
{
    Super::Jump();
    
    // 점프 상태 서버에 전송
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(true, GetActorLocation());
    }
}

void ASimpleNetworkCharacter::StopJumping()
{
    Super::StopJumping();
    
    // 점프 중단 상태 서버에 전송
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(false, GetActorLocation());
    }
}

AActor* ASimpleNetworkCharacter::SpawnOtherPlayerCharacter(const FVector& Position, int32 InClientId)
{
    return SpawnOtherPlayerCharacterInternal(Position, InClientId);
}

AActor* ASimpleNetworkCharacter::SpawnOtherPlayerCharacterInternal(const FVector& Position, int32 InClientId)
{
    if (!GetWorld() || !OtherPlayerCharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player: Invalid World or Character Class"));
        return nullptr;
    }
    
    // 다른 플레이어 캐릭터 스폰
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
    AActor* NewPlayerActor = GetWorld()->SpawnActor<AActor>(
        OtherPlayerCharacterClass,
        Position,
        FRotator::ZeroRotator,
        SpawnParams
    );
    
    if (NewPlayerActor)
    {
        UE_LOG(LogTemp, Display, TEXT("Spawned other player character for client ID %d at: X=%.2f Y=%.2f Z=%.2f"),
               InClientId, Position.X, Position.Y, Position.Z);
        
        // 플레이어 입력 비활성화 - 컨트롤러 생성 부분 수정
        if (ACharacter* OtherCharacter = Cast<ACharacter>(NewPlayerActor))
        {
            // 컨트롤러 클래스를 구체 클래스로 변경 (AController 대신 APlayerController 사용)
            APlayerController* NewController = GetWorld()->SpawnActor<APlayerController>(
                APlayerController::StaticClass(),
                FVector::ZeroVector,
                FRotator::ZeroRotator,
                SpawnParams
            );
            
            if (NewController)
            {
                OtherCharacter->bUseControllerRotationYaw = false;
                NewController->Possess(OtherCharacter);
                NewController->SetIgnoreMoveInput(true);
                NewController->SetIgnoreLookInput(true);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create controller for other player character"));
            }
        }
        
        // 캐릭터 정보 저장
        FOtherPlayerInfo PlayerInfo;
        PlayerInfo.ClientId = InClientId;
        PlayerInfo.TargetPosition = Position;
        PlayerInfo.TargetRotation = FRotator::ZeroRotator;
        PlayerInfo.PositionInterpolationTime = 0.0f;
        PlayerInfo.RotationInterpolationTime = 0.0f;
        
        OtherPlayers.Add(NewPlayerActor, PlayerInfo);
        
        // 블루프린트 이벤트 호출
        OnOtherPlayerSpawned(NewPlayerActor, InClientId);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player character!"));
    }
    
    return NewPlayerActor;
}

void ASimpleNetworkCharacter::RemoveOtherPlayerCharacter(int32 ClientId)
{
    // 특정 ID의 플레이어만 제거
    AActor* ActorToRemove = nullptr;
    
    for (auto& Pair : OtherPlayers)
    {
        if (Pair.Value.ClientId == ClientId)
        {
            ActorToRemove = Pair.Key;
            
            if (ActorToRemove && IsValid(ActorToRemove))
            {
                ActorToRemove->Destroy();
                OtherPlayers.Remove(ActorToRemove);
                
                // 블루프린트 이벤트 호출
                OnOtherPlayerRemoved(ClientId);
                
                UE_LOG(LogTemp, Display, TEXT("Removed player character for client ID: %d"), ClientId);
            }
            
            break;
        }
    }
}

void ASimpleNetworkCharacter::RemoveAllOtherPlayers()
{
    // 모든 다른 플레이어 캐릭터 제거
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
        {
            int32 ClientId = OtherPlayer.Value.ClientId;
            OtherPlayer.Key->Destroy();
            
            // 블루프린트 이벤트 호출
            OnOtherPlayerRemoved(ClientId);
        }
    }
    
    OtherPlayers.Empty();
    
    UE_LOG(LogTemp, Display, TEXT("All other player characters removed"));
}

void ASimpleNetworkCharacter::UpdateOtherPlayerCharacters(float DeltaTime)
{
    // 다른 플레이어 캐릭터 위치/회전 보간 처리
    TArray<AActor*> InvalidActors;
    
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
        {
            // 위치 보간
            OtherPlayer.Value.PositionInterpolationTime += DeltaTime;
            float PosAlpha = FMath::Clamp(OtherPlayer.Value.PositionInterpolationTime / 0.1f, 0.0f, 1.0f);
            FVector NewPos = FMath::Lerp(OtherPlayer.Key->GetActorLocation(), OtherPlayer.Value.TargetPosition, PosAlpha);
            OtherPlayer.Key->SetActorLocation(NewPos);
            
            // 회전 보간
            OtherPlayer.Value.RotationInterpolationTime += DeltaTime;
            float RotAlpha = FMath::Clamp(OtherPlayer.Value.RotationInterpolationTime / 0.1f, 0.0f, 1.0f);
            FRotator NewRot = FMath::Lerp(OtherPlayer.Key->GetActorRotation(), OtherPlayer.Value.TargetRotation, RotAlpha);
            OtherPlayer.Key->SetActorRotation(NewRot);
            
            // 입력 제어 비활성화 확인 (다른 플레이어 캐릭터는 입력을 받지 않도록)
            if (ACharacter* OtherCharacter = Cast<ACharacter>(OtherPlayer.Key))
            {
                if (APlayerController* PC = Cast<APlayerController>(OtherCharacter->GetController()))
                {
                    PC->DisableInput(PC);
                }
            }
        }
        else
        {
            // 유효하지 않은 액터 표시
            InvalidActors.Add(OtherPlayer.Key);
        }
    }
    
    // 유효하지 않은 액터 제거
    for (AActor* Actor : InvalidActors)
    {
        OtherPlayers.Remove(Actor);
    }
}

// 인터페이스 구현
void ASimpleNetworkCharacter::OnNetworkConnected_Implementation()
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Network connected"));
}

void ASimpleNetworkCharacter::OnNetworkDisconnected_Implementation()
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Network disconnected"));
    
    // 연결 해제 시 다른 플레이어 제거
    RemoveAllOtherPlayers();
    
    // 클라이언트 ID 초기화
    LocalClientId = -1;
}

void ASimpleNetworkCharacter::OnPlayerUpdateReceived_Implementation(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping)
{
    // 자신의 업데이트는 무시
    if (ClientId == LocalClientId)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Ignored update for local player (ID: %d)"), ClientId);
        return;
    }
    
    UE_LOG(LogTemp, Verbose, TEXT("Received update for player ID %d: Pos=(%.1f,%.1f,%.1f), Vel=(%.1f,%.1f,%.1f), Jumping=%s"),
           ClientId, Position.X, Position.Y, Position.Z,
           Velocity.X, Velocity.Y, Velocity.Z,
           IsJumping ? TEXT("true") : TEXT("false"));
    
    // 해당 ID의 플레이어가 이미 존재하는지 확인
    AActor* ExistingPlayerActor = nullptr;
    
    for (auto& Pair : OtherPlayers)
    {
        if (Pair.Value.ClientId == ClientId)
        {
            ExistingPlayerActor = Pair.Key;
            
            // 위치, 회전, 점프 상태 업데이트
            Pair.Value.TargetPosition = Position;
            Pair.Value.TargetRotation = Rotation;
            Pair.Value.PositionInterpolationTime = 0.0f;
            Pair.Value.RotationInterpolationTime = 0.0f;
            Pair.Value.IsJumping = IsJumping;
            
            // 애니메이션을 위한 속도 설정
            if (ACharacter* OtherCharacter = Cast<ACharacter>(ExistingPlayerActor))
            {
                if (UCharacterMovementComponent* MovementComp = OtherCharacter->GetCharacterMovement())
                {
                    // 네트워크로 받은 속도 정보 적용
                    MovementComp->Velocity = Velocity;
                    
                    // 속도가 있으면 걷기 모드로 설정
                    if (Velocity.SizeSquared() > 25.0f && !IsJumping)
                    {
                        MovementComp->SetMovementMode(MOVE_Walking);
                    }
                }
            }
            
            // 점프 상태 처리
            if (IsJumping)
            {
                if (ACharacter* OtherCharacter = Cast<ACharacter>(ExistingPlayerActor))
                {
                    OtherCharacter->Jump();
                }
            }
            
            break;
        }
    }
    
    // 존재하지 않는 경우 새로 생성
    if (!ExistingPlayerActor)
    {
        UE_LOG(LogTemp, Display, TEXT("Spawning new player character for client ID: %d"), ClientId);
        SpawnOtherPlayerCharacterInternal(Position, ClientId);
    }
}

void ASimpleNetworkCharacter::OnClientIdReceived_Implementation(int32 ClientId)
{
    // 로컬 클라이언트 ID 저장
    LocalClientId = ClientId;

    UE_LOG(LogTemp, Display, TEXT("Client ID received: %d"), LocalClientId);
}

void ASimpleNetworkCharacter::OnOtherPlayerSpawned_Implementation(AActor* OtherPlayerActor, int32 ClientId)
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Other player spawned - Client ID: %d"), ClientId);
}

void ASimpleNetworkCharacter::OnOtherPlayerRemoved_Implementation(int32 ClientId)
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Other player removed - Client ID: %d"), ClientId);
}

void ASimpleNetworkCharacter::OnConnectionStatusChanged(bool IsConnected)
{
    if (IsConnected)
    {
        // 연결 성공 시 처리
        OnNetworkConnected();
    }
    else
    {
        // 연결 해제 시 처리
        OnNetworkDisconnected();
    }
}