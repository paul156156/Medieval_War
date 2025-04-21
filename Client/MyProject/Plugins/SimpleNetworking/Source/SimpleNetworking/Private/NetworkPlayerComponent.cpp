// NetworkPlayerComponent.cpp
#include "NetworkPlayerComponent.h"
#include "SimpleNetworkManager.h"
#include "SimpleNetworkCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

UNetworkPlayerComponent::UNetworkPlayerComponent()
    : NetworkManager(nullptr)
    , ServerIP(TEXT("127.0.0.1"))
    , ServerPort(9000)
    , bAutoConnectOnBeginPlay(false)
    , bEnableNetworkUpdates(true)
    , PositionUpdateInterval(0.1f)
    , LocalClientId(-1)
    , LastPositionSentTime(0.0f)
{
    // Tick 함수 활성화
    PrimaryComponentTick.bCanEverTick = true;
}

void UNetworkPlayerComponent::BeginPlay()
{
    Super::BeginPlay();

    // NetworkManager가 없으면 생성
    if (!NetworkManager)
    {
        NetworkManager = NewObject<USimpleNetworkManager>(GetOwner());
    }

    // 네트워크 이벤트 핸들러 바인딩
    BindNetworkEvents();

    // 자동 연결 설정된 경우 서버에 연결
    if (bAutoConnectOnBeginPlay)
    {
        FTimerHandle ConnectTimerHandle;
        FTimerDelegate ConnectDelegate;
        ConnectDelegate.BindUObject(this, &UNetworkPlayerComponent::ConnectToServerWrapper);
        GetWorld()->GetTimerManager().SetTimer(
            ConnectTimerHandle,
            ConnectDelegate,
            1.0f,
            false
        );
    }
}

void UNetworkPlayerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // 서버 연결 해제
    DisconnectFromServer();

    // 네트워크 이벤트 핸들러 해제
    UnbindNetworkEvents();

    Super::EndPlay(EndPlayReason);
}

void UNetworkPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 플레이어가 로컬 컨트롤러를 가지고 있고, 네트워크 업데이트가 활성화된 경우
    if (bEnableNetworkUpdates && NetworkManager && NetworkManager->IsConnected())
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

void UNetworkPlayerComponent::ConnectToServerWrapper()
{
    ConnectToServer();
}

void UNetworkPlayerComponent::SetNetworkManager(USimpleNetworkManager* InNetworkManager)
{
    // 기존 이벤트 핸들러 해제
    if (NetworkManager)
    {
        UnbindNetworkEvents();
    }

    // 새 네트워크 매니저 설정
    NetworkManager = InNetworkManager;

    // 새 이벤트 핸들러 바인딩
    if (NetworkManager)
    {
        BindNetworkEvents();
    }
}

bool UNetworkPlayerComponent::ConnectToServer()
{
    if (!NetworkManager)
    {
        UE_LOG(LogTemp, Error, TEXT("NetworkPlayerComponent: NetworkManager is null"));
        return false;
    }

    // 서버 연결 시도
    bool bConnected = NetworkManager->ConnectToServer(ServerIP, ServerPort);

    if (bConnected)
    {
        UE_LOG(LogTemp, Display, TEXT("Successfully connected to server %s:%d"), *ServerIP, ServerPort);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to connect to server %s:%d"), *ServerIP, ServerPort);
    }

    return bConnected;
}

void UNetworkPlayerComponent::DisconnectFromServer()
{
    if (NetworkManager)
    {
        NetworkManager->DisconnectFromServer();
    }
}

void UNetworkPlayerComponent::SendPositionToServer()
{
    if (!NetworkManager || !NetworkManager->IsConnected())
    {
        return;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return;
    }

    // 현재 위치와 회전값 가져오기
    FVector CurrentLocation = Owner->GetActorLocation();
    FRotator CurrentRotation = Owner->GetActorRotation();

    // 이동 중인지 확인 (속도 체크)
    float ForwardValue = 0.0f;
    float RightValue = 0.0f;

    ACharacter* Character = Cast<ACharacter>(Owner);
    if (Character)
    {
        AController* Controller = Character->GetController();
        if (Controller && Controller->IsLocalPlayerController())
        {
            // Enhanced Input을 사용하는 SimpleNetworkCharacter 확인
            ASimpleNetworkCharacter* NetCharacter = Cast<ASimpleNetworkCharacter>(Character);
            if (NetCharacter)
            {
                // Enhanced Input에서 저장된 값 사용
                ForwardValue = NetCharacter->CurrentForwardValue;
                RightValue = NetCharacter->CurrentRightValue;
            }
            else
            {
                // 기존 방식 유지 (하위 호환성)
                ForwardValue = Character->GetInputAxisValue("MoveForward");
                RightValue = Character->GetInputAxisValue("MoveRight");
            }
        }
    }

    // 이동 패킷 전송
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void UNetworkPlayerComponent::SendJumpState(bool bIsJumping)
{
    if (!NetworkManager || !NetworkManager->IsConnected())
    {
        return;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return;
    }

    // 현재 위치 가져오기
    FVector CurrentLocation = Owner->GetActorLocation();

    // 점프 패킷 전송
    NetworkManager->SendJumpPacket(bIsJumping, CurrentLocation);
}

AActor* UNetworkPlayerComponent::SpawnOtherPlayerCharacter(const FVector& Position, int32 InClientId)
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

void UNetworkPlayerComponent::RemoveOtherPlayerCharacter(int32 ClientId)
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

void UNetworkPlayerComponent::RemoveAllOtherPlayers()
{
    // 모든 다른 플레이어 캐릭터 제거
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
        {
            // 블루프린트 이벤트 호출
            OnOtherPlayerRemoved(OtherPlayer.Value.ClientId);

            // 액터 제거
            OtherPlayer.Key->Destroy();
        }
    }

    OtherPlayers.Empty();

    UE_LOG(LogTemp, Display, TEXT("All other player characters removed"));
}

void UNetworkPlayerComponent::BindNetworkEvents()
{
    if (!NetworkManager)
    {
        return;
    }

    // 이전 델리게이트 바인딩 제거 (안전을 위해)
    UnbindNetworkEvents();

    // 새로운 델리게이트만 바인딩
    NetworkManager->OnPlayerUpdate.AddDynamic(this, &UNetworkPlayerComponent::OnPlayerUpdateReceived);
    NetworkManager->OnClientIdReceived.AddDynamic(this, &UNetworkPlayerComponent::OnClientIdReceived);
    NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &UNetworkPlayerComponent::OnConnectionStatusChanged);

    // 레거시 지원 (호환성)
    NetworkManager->OnPositionUpdate.AddDynamic(this, &UNetworkPlayerComponent::OnPositionUpdateReceived);
    NetworkManager->OnRotationUpdate.AddDynamic(this, &UNetworkPlayerComponent::OnRotationUpdateReceived);
    NetworkManager->OnJumpStateUpdate.AddDynamic(this, &UNetworkPlayerComponent::OnJumpStateUpdateReceived);

    UE_LOG(LogTemp, Display, TEXT("Network event handlers bound"));

    // 이미 ID가 할당되어 있는 경우 적용
    LocalClientId = NetworkManager->GetClientId();
    if (LocalClientId != -1)
    {
        UE_LOG(LogTemp, Display, TEXT("Local Client ID: %d"), LocalClientId);
    }
}

void UNetworkPlayerComponent::UnbindNetworkEvents()
{
    if (!NetworkManager)
    {
        return;
    }

    // 모든 델리게이트 바인딩 제거
    NetworkManager->OnPlayerUpdate.RemoveDynamic(this, &UNetworkPlayerComponent::OnPlayerUpdateReceived);
    NetworkManager->OnClientIdReceived.RemoveDynamic(this, &UNetworkPlayerComponent::OnClientIdReceived);
    NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &UNetworkPlayerComponent::OnConnectionStatusChanged);

    // 레거시 지원 (호환성)
    NetworkManager->OnPositionUpdate.RemoveDynamic(this, &UNetworkPlayerComponent::OnPositionUpdateReceived);
    NetworkManager->OnRotationUpdate.RemoveDynamic(this, &UNetworkPlayerComponent::OnRotationUpdateReceived);
    NetworkManager->OnJumpStateUpdate.RemoveDynamic(this, &UNetworkPlayerComponent::OnJumpStateUpdateReceived);
}

void UNetworkPlayerComponent::UpdateOtherPlayerCharacters(float DeltaTime)
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

// 네트워크 이벤트 함수들
void UNetworkPlayerComponent::OnNetworkConnected()
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Network connected"));
}

void UNetworkPlayerComponent::OnNetworkDisconnected()
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Network disconnected"));

    // 연결 해제 시 다른 플레이어 제거
    RemoveAllOtherPlayers();

    // 클라이언트 ID 초기화
    LocalClientId = -1;
}

void UNetworkPlayerComponent::OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping)
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
        SpawnOtherPlayerCharacter(Position, ClientId);
    }
}

void UNetworkPlayerComponent::OnClientIdReceived(int32 ClientId)
{
    // 로컬 클라이언트 ID 저장
    LocalClientId = ClientId;

    UE_LOG(LogTemp, Display, TEXT("Client ID received: %d"), LocalClientId);
}

void UNetworkPlayerComponent::OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId)
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Other player spawned - Client ID: %d"), ClientId);
}

void UNetworkPlayerComponent::OnOtherPlayerRemoved(int32 ClientId)
{
    // 블루프린트에서 오버라이드 가능
    UE_LOG(LogTemp, Display, TEXT("Other player removed - Client ID: %d"), ClientId);
}

// 레거시 이벤트 핸들러 (호환성 유지)
void UNetworkPlayerComponent::OnPositionUpdateReceived(const FVector& NewPosition)
{
    // 레거시 호환성 유지 - 새로운 OnPlayerUpdateReceived로 대체 예정
    UE_LOG(LogTemp, Warning, TEXT("OnPositionUpdateReceived: Legacy function called. This should be handled by OnPlayerUpdateReceived."));

    // ID 정보가 없으므로 가장 가까운 캐릭터에게 적용 (레거시 동작)
    bool bPlayerExists = false;
    float ClosestDistSq = MAX_FLT;
    AActor* ClosestActor = nullptr;

    for (auto& Pair : OtherPlayers)
    {
        float DistSq = (Pair.Key->GetActorLocation() - NewPosition).SizeSquared();
        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            ClosestActor = Pair.Key;
            bPlayerExists = true;
        }
    }

    if (bPlayerExists && ClosestActor)
    {
        OtherPlayers[ClosestActor].TargetPosition = NewPosition;
        OtherPlayers[ClosestActor].PositionInterpolationTime = 0.0f;
    }
    else
    {
        // ID 정보 없이 새 캐릭터 생성 (임시 ID -1 사용)
        SpawnOtherPlayerCharacter(NewPosition, -1);
    }
}

void UNetworkPlayerComponent::OnRotationUpdateReceived(const FRotator& NewRotation)
{
    // 레거시 호환성 유지 - 새로운 OnPlayerUpdateReceived로 대체 예정
    UE_LOG(LogTemp, Warning, TEXT("OnRotationUpdateReceived: Legacy function called. This should be handled by OnPlayerUpdateReceived."));

    // ID 정보가 없으므로 첫 번째 캐릭터에게 적용 (레거시 동작)
    if (OtherPlayers.Num() > 0)
    {
        auto FirstItem = OtherPlayers.CreateIterator();
        FirstItem.Value().TargetRotation = NewRotation;
        FirstItem.Value().RotationInterpolationTime = 0.0f;
    }
}

void UNetworkPlayerComponent::OnJumpStateUpdateReceived(bool IsJumping)
{
    // 레거시 호환성 유지 - 새로운 OnPlayerUpdateReceived로 대체 예정
    UE_LOG(LogTemp, Warning, TEXT("OnJumpStateUpdateReceived: Legacy function called. This should be handled by OnPlayerUpdateReceived."));

    // ID 정보가 없으므로 첫 번째 캐릭터에게 적용 (레거시 동작)
    if (OtherPlayers.Num() > 0)
    {
        auto FirstItem = OtherPlayers.CreateIterator();
        FirstItem.Value().IsJumping = IsJumping;

        if (IsJumping)
        {
            if (ACharacter* OtherCharacter = Cast<ACharacter>(FirstItem.Key()))
            {
                OtherCharacter->Jump();
            }
        }
    }
}

void UNetworkPlayerComponent::OnConnectionStatusChanged(bool IsConnected)
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