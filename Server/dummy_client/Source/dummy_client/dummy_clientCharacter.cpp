#include "dummy_clientCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "dummy_clientGameMode.h"
#include "NetworkManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

Adummy_clientCharacter::Adummy_clientCharacter()
    : NetworkManager(nullptr)
    , bEnableNetworkUpdates(true)
    , LastPositionSentTime(0.0f)
    , PositionUpdateInterval(0.1f) // 10Hz 업데이트 간격
    , LocalClientId(-1)  // 초기 클라이언트 ID는 -1로 설정
    , OtherPlayerCharacterClass(nullptr)
{
    // 캡슐 컴포넌트 설정
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // 입력 설정
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // 컨트롤러 회전에 따라 캐릭터가 회전하지 않도록 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // 캐릭터 무브먼트 컴포넌트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // 카메라 붐 생성
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // 팔로우 카메라 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Tick 함수 활성화
    PrimaryActorTick.bCanEverTick = true;
}

void Adummy_clientCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 네트워크 매니저 초기화
    InitializeNetworkManager();

    // 디버깅 로그 추가
    UE_LOG(LogTemp, Warning, TEXT("Player Character BeginPlay - Other Player Class: %s"),
        OtherPlayerCharacterClass ? *OtherPlayerCharacterClass->GetName() : TEXT("NULL"));
}

void Adummy_clientCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 디버그 출력
    FVector Velocity = GetVelocity();
    if (Velocity.SizeSquared() > 0.0f)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Character velocity: X=%.2f Y=%.2f Z=%.2f"),
            Velocity.X, Velocity.Y, Velocity.Z);
    }

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

void Adummy_clientCharacter::InitializeNetworkManager()
{
    // 게임 모드에서 네트워크 매니저 가져오기
    if (Adummy_clientGameMode* GameMode = Cast<Adummy_clientGameMode>(GetWorld()->GetAuthGameMode()))
    {
        NetworkManager = GameMode->GetNetworkManager();

        if (NetworkManager)
        {
            // 이전 델리게이트 바인딩 제거 (안전을 위해)
            NetworkManager->OnPositionUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnPositionUpdateReceived);
            NetworkManager->OnRotationUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnRotationUpdateReceived);
            NetworkManager->OnJumpStateUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnJumpStateUpdateReceived);
            NetworkManager->OnPlayerUpdate.RemoveDynamic(this, &Adummy_clientCharacter::OnPlayerUpdateReceived);
            NetworkManager->OnClientIdReceived.RemoveDynamic(this, &Adummy_clientCharacter::OnClientIdReceived);
            NetworkManager->OnConnectionStatusChanged.RemoveDynamic(this, &Adummy_clientCharacter::OnConnectionStatusChanged);

            // 새로운 델리게이트만 바인딩 (레거시는 제외)
            NetworkManager->OnPlayerUpdate.AddDynamic(this, &Adummy_clientCharacter::OnPlayerUpdateReceived);
            NetworkManager->OnClientIdReceived.AddDynamic(this, &Adummy_clientCharacter::OnClientIdReceived);
            NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &Adummy_clientCharacter::OnConnectionStatusChanged);

            UE_LOG(LogTemp, Display, TEXT("Network Manager initialized with new delegate system"));

            // 이미 ID가 할당되어 있는 경우 적용
            LocalClientId = NetworkManager->GetClientId();
            UE_LOG(LogTemp, Display, TEXT("Local Client ID: %d"), LocalClientId);
        }
    }
}

void Adummy_clientCharacter::SendPositionToServer()
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

        // 디버그 출력 추가
        UE_LOG(LogTemp, Verbose, TEXT("Input Values - Forward: %.2f, Right: %.2f"),
            ForwardValue, RightValue);
    }

    // 이동 패킷 전송
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void Adummy_clientCharacter::OnClientIdReceived(int32 ClientId)
{
    // 로컬 클라이언트 ID 저장
    LocalClientId = ClientId;

    UE_LOG(LogTemp, Display, TEXT("Client ID received: %d"), LocalClientId);
}

void Adummy_clientCharacter::OnPlayerUpdateReceived(int32 ClientId, const FVector& NewPosition, const FRotator& NewRotation, bool IsJumping)
{
    // 자신의 업데이트는 무시
    if (ClientId == LocalClientId)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Ignoring update for local player (ID: %d)"), ClientId);
        return;
    }

    UE_LOG(LogTemp, Verbose, TEXT("Received update for player ID %d: Pos=(%.1f,%.1f,%.1f), Yaw=%.1f, Jumping=%s"),
        ClientId, NewPosition.X, NewPosition.Y, NewPosition.Z, NewRotation.Yaw,
        IsJumping ? TEXT("true") : TEXT("false"));

    // 해당 ID의 플레이어가 이미 존재하는지 확인
    AActor* ExistingPlayerActor = nullptr;

    for (auto& Pair : OtherPlayers)
    {
        if (Pair.Value.ClientId == ClientId)
        {
            ExistingPlayerActor = Pair.Key;

            // 위치, 회전, 점프 상태 업데이트
            Pair.Value.TargetPosition = NewPosition;
            Pair.Value.TargetRotation = NewRotation;
            Pair.Value.PositionInterpolationTime = 0.0f;
            Pair.Value.RotationInterpolationTime = 0.0f;
            Pair.Value.IsJumping = IsJumping;

            // 점프 상태 처리
            if (IsJumping && !Pair.Value.IsJumping)
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
        SpawnOtherPlayerCharacterInternal(NewPosition, ClientId);
    }
}

void Adummy_clientCharacter::OnPositionUpdateReceived(const FVector& NewPosition)
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
        SpawnOtherPlayerCharacterInternal(NewPosition, -1);
    }
}

void Adummy_clientCharacter::OnRotationUpdateReceived(const FRotator& NewRotation)
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

void Adummy_clientCharacter::OnJumpStateUpdateReceived(bool IsJumping)
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

void Adummy_clientCharacter::OnConnectionStatusChanged(bool IsConnected)
{
    if (!IsConnected)
    {
        // 연결 해제 시 다른 플레이어 캐릭터 제거
        RemoveAllOtherPlayers();

        // 클라이언트 ID 초기화
        LocalClientId = -1;

        // UI에 연결 해제 표시 등 추가 기능 구현 가능
        OnNetworkDisconnected();
    }
    else
    {
        // 연결 성공 시 처리
        OnNetworkConnected();
    }
}

void Adummy_clientCharacter::RemoveAllOtherPlayers()
{
    // 모든 다른 플레이어 캐릭터 제거
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
        {
            OtherPlayer.Key->Destroy();
        }
    }
    OtherPlayers.Empty();

    UE_LOG(LogTemp, Display, TEXT("All other player characters removed"));
}

void Adummy_clientCharacter::RemoveOtherPlayerCharacter(int32 ClientId)
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

void Adummy_clientCharacter::UpdateOtherPlayerCharacters(float DeltaTime)
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

void Adummy_clientCharacter::Jump()
{
    Super::Jump();

    // 점프 상태 서버에 전송
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(true, GetActorLocation());
    }
}

void Adummy_clientCharacter::StopJumping()
{
    Super::StopJumping();

    // 점프 중단 상태 서버에 전송
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(false, GetActorLocation());
    }
}

AActor* Adummy_clientCharacter::SpawnOtherPlayerCharacterInternal(const FVector& Position, int32 InClientId)
{
    if (!GetWorld() || !OtherPlayerCharacterClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn other player: Invalid World or Character Class"));
        return nullptr;
    }

    // 다른 플레이어 캐릭터 스폰
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AActor* NewPlayerActor = GetWorld()->SpawnActor<AActor>(OtherPlayerCharacterClass, Position, FRotator::ZeroRotator, SpawnParams);

    if (NewPlayerActor)
    {
        UE_LOG(LogTemp, Display, TEXT("Spawned other player character for client ID %d at: X=%.2f Y=%.2f Z=%.2f"),
            InClientId, Position.X, Position.Y, Position.Z);

        // 플레이어 입력 비활성화 - 컨트롤러 생성 부분 수정
        if (ACharacter* OtherCharacter = Cast<ACharacter>(NewPlayerActor))
        {
            // 컨트롤러 클래스를 구체 클래스로 변경 (AController 대신 APlayerController 사용)
            APlayerController* NewController = GetWorld()->SpawnActor<APlayerController>(APlayerController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            if (NewController)
            {
                OtherCharacter->bUseControllerRotationYaw = false;
                NewController->Possess(OtherCharacter);
                NewController->SetIgnoreMoveInput(true);
                NewController->SetIgnoreLookInput(true);
            }
            else
            {
                // 컨트롤러 생성 실패 시 로그
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
// 기본 입력 함수들 구현
void Adummy_clientCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // 현재 카메라가 바라보는 방향 찾기
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 전진 벡터 찾기
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void Adummy_clientCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // 현재 카메라가 바라보는 방향 찾기
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // 오른쪽 벡터 찾기
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void Adummy_clientCharacter::TurnAtRate(float Rate)
{
    // 초당 입력값과 turn rate 기반으로 회전 계산
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Adummy_clientCharacter::LookUpAtRate(float Rate)
{
    // 초당 입력값과 look up/down rate 기반으로 회전 계산
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void Adummy_clientCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    Jump();
}

void Adummy_clientCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    StopJumping();
}

void Adummy_clientCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // 점프
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Adummy_clientCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &Adummy_clientCharacter::StopJumping);

    // 이동
    PlayerInputComponent->BindAxis("MoveForward", this, &Adummy_clientCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &Adummy_clientCharacter::MoveRight);

    // 회전
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &Adummy_clientCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &Adummy_clientCharacter::LookUpAtRate);

    // 터치 기능 설정
    PlayerInputComponent->BindTouch(IE_Pressed, this, &Adummy_clientCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &Adummy_clientCharacter::TouchStopped);
}