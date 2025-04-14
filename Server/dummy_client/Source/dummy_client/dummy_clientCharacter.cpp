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
            // 델리게이트 바인딩
            NetworkManager->OnPositionUpdate.AddDynamic(this, &Adummy_clientCharacter::OnPositionUpdateReceived);
            NetworkManager->OnRotationUpdate.AddDynamic(this, &Adummy_clientCharacter::OnRotationUpdateReceived);
            NetworkManager->OnJumpStateUpdate.AddDynamic(this, &Adummy_clientCharacter::OnJumpStateUpdateReceived);
            NetworkManager->OnConnectionStatusChanged.AddDynamic(this, &Adummy_clientCharacter::OnConnectionStatusChanged);
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
        UE_LOG(LogTemp, Display, TEXT("Input Values - Forward: %.2f, Right: %.2f"),
            ForwardValue, RightValue);
    }

    // 이동 패킷 전송
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void Adummy_clientCharacter::OnPositionUpdateReceived(const FVector& NewPosition)
{
    // 다른 플레이어가 존재하는지 확인
    bool bPlayerExists = false;
    for (auto& OtherPlayer : OtherPlayers)
    {
        // 가장 가까운 플레이어를 찾아 위치 업데이트
        // 실제 구현에서는 플레이어 ID 등을 사용해야 함
        if (!bPlayerExists || (OtherPlayer.Key->GetActorLocation() - NewPosition).SizeSquared() < 100000.0f)
        {
            OtherPlayer.Value.TargetPosition = NewPosition;
            OtherPlayer.Value.PositionInterpolationTime = 0.0f;
            bPlayerExists = true;
            break;
        }
    }

    // 존재하지 않는 경우 새로 생성
    if (!bPlayerExists)
    {
        SpawnOtherPlayerCharacterInternal(NewPosition);
    }
}

void Adummy_clientCharacter::OnRotationUpdateReceived(const FRotator& NewRotation)
{
    // 가장 최근에 업데이트된 플레이어의 회전값 설정
    for (auto& OtherPlayer : OtherPlayers)
    {
        OtherPlayer.Value.TargetRotation = NewRotation;
        OtherPlayer.Value.RotationInterpolationTime = 0.0f;
        break; // 현재는 단순히 첫 번째 플레이어에게만 적용
    }
}

void Adummy_clientCharacter::OnJumpStateUpdateReceived(bool IsJumping)
{
    // 가장 최근에 업데이트된 플레이어의 점프 상태 설정
    for (auto& OtherPlayer : OtherPlayers)
    {
        if (IsJumping)
        {
            // 캐릭터가 ACharacter 클래스의 인스턴스인지 확인
            if (ACharacter* OtherCharacter = Cast<ACharacter>(OtherPlayer.Key))
            {
                OtherCharacter->Jump();
            }
        }
        break; // 현재는 단순히 첫 번째 플레이어에게만 적용
    }
}

void Adummy_clientCharacter::OnConnectionStatusChanged(bool IsConnected)
{
    if (!IsConnected)
    {
        // 연결 해제 시 다른 플레이어 캐릭터 제거
        for (auto& OtherPlayer : OtherPlayers)
        {
            if (OtherPlayer.Key && IsValid(OtherPlayer.Key))
            {
                OtherPlayer.Key->Destroy();
            }
        }
        OtherPlayers.Empty();

        // UI에 연결 해제 표시 등 추가 기능 구현 가능
        OnNetworkDisconnected();
    }
    else
    {
        // 연결 성공 시 처리
        OnNetworkConnected();
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

AActor* Adummy_clientCharacter::SpawnOtherPlayerCharacterInternal(const FVector& Position)
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
        UE_LOG(LogTemp, Display, TEXT("Spawned other player character at: X=%.2f Y=%.2f Z=%.2f"),
            Position.X, Position.Y, Position.Z);

        // 플레이어 입력 비활성화
        if (ACharacter* OtherCharacter = Cast<ACharacter>(NewPlayerActor))
        {
            // AI 컨트롤러 대신 기본 컨트롤러 사용
            AController* NewController = GetWorld()->SpawnActor<AController>(AController::StaticClass());
            if (NewController)
            {
                OtherCharacter->AIControllerClass = nullptr;
                OtherCharacter->bUseControllerRotationYaw = false;
                NewController->Possess(OtherCharacter);
                NewController->SetIgnoreMoveInput(true);
            }
        }

        // 캐릭터 정보 저장
        FOtherPlayerInfo PlayerInfo;
        PlayerInfo.TargetPosition = Position;
        PlayerInfo.TargetRotation = FRotator::ZeroRotator;
        PlayerInfo.PositionInterpolationTime = 0.0f;
        PlayerInfo.RotationInterpolationTime = 0.0f;

        OtherPlayers.Add(NewPlayerActor, PlayerInfo);

        // 블루프린트 이벤트 호출
        OnOtherPlayerSpawned(NewPlayerActor);
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