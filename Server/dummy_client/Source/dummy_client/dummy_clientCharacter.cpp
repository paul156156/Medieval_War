#include "dummy_clientCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "dummy_clientGameMode.h"
#include "NetworkManager.h"

Adummy_clientCharacter::Adummy_clientCharacter()
    : NetworkManager(nullptr)
    , bEnableNetworkUpdates(true)
    , LastPositionSentTime(0.0f)
    , PositionUpdateInterval(0.1f) // 10Hz 업데이트 간격
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
}

void Adummy_clientCharacter::InitializeNetworkManager()
{
    // 게임 모드에서 네트워크 매니저 가져오기
    if (Adummy_clientGameMode* GameMode = Cast<Adummy_clientGameMode>(GetWorld()->GetAuthGameMode()))
    {
        NetworkManager = GameMode->GetNetworkManager();

        // 위치 업데이트 델리게이트 바인딩
        if (NetworkManager)
        {
            NetworkManager->OnPositionUpdate.AddDynamic(this, &Adummy_clientCharacter::OnPositionUpdateReceived);
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
    float ForwardValue = GetInputAxisValue("MoveForward");
    float RightValue = GetInputAxisValue("MoveRight");

    // 이동 패킷 전송
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void Adummy_clientCharacter::OnPositionUpdateReceived(const FVector& NewPosition)
{
    // 다른 플레이어의 위치 정보 수신
    // 블루프린트에서 구현할 함수 호출
    SpawnOtherPlayerCharacter(NewPosition);
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