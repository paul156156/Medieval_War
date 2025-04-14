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
    , PositionUpdateInterval(0.1f) // 10Hz ������Ʈ ����
{
    // ĸ�� ������Ʈ ����
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // �Է� ����
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // ��Ʈ�ѷ� ȸ���� ���� ĳ���Ͱ� ȸ������ �ʵ��� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // ĳ���� �����Ʈ ������Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // ī�޶� �� ����
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // �ȷο� ī�޶� ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Tick �Լ� Ȱ��ȭ
    PrimaryActorTick.bCanEverTick = true;
}

void Adummy_clientCharacter::BeginPlay()
{
    Super::BeginPlay();

    // ��Ʈ��ũ �Ŵ��� �ʱ�ȭ
    InitializeNetworkManager();
}

void Adummy_clientCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // �÷��̾ ���� ��Ʈ�ѷ��� ������ �ְ�, ��Ʈ��ũ ������Ʈ�� Ȱ��ȭ�� ���
    if (IsLocallyControlled() && bEnableNetworkUpdates && NetworkManager && NetworkManager->IsConnected())
    {
        // ��ġ ������Ʈ ���� üũ
        float CurrentTime = GetWorld()->GetTimeSeconds();
        if (CurrentTime - LastPositionSentTime >= PositionUpdateInterval)
        {
            // ������ ��ġ ���� ����
            SendPositionToServer();
            LastPositionSentTime = CurrentTime;
        }
    }
}

void Adummy_clientCharacter::InitializeNetworkManager()
{
    // ���� ��忡�� ��Ʈ��ũ �Ŵ��� ��������
    if (Adummy_clientGameMode* GameMode = Cast<Adummy_clientGameMode>(GetWorld()->GetAuthGameMode()))
    {
        NetworkManager = GameMode->GetNetworkManager();

        // ��ġ ������Ʈ ��������Ʈ ���ε�
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

    // ���� ��ġ�� ȸ���� ��������
    FVector CurrentLocation = GetActorLocation();
    FRotator CurrentRotation = GetActorRotation();

    // �̵� ������ Ȯ�� (�ӵ� üũ)
    float ForwardValue = GetInputAxisValue("MoveForward");
    float RightValue = GetInputAxisValue("MoveRight");

    // �̵� ��Ŷ ����
    NetworkManager->SendMovePacket(ForwardValue, RightValue, CurrentLocation, CurrentRotation);
}

void Adummy_clientCharacter::OnPositionUpdateReceived(const FVector& NewPosition)
{
    // �ٸ� �÷��̾��� ��ġ ���� ����
    // �������Ʈ���� ������ �Լ� ȣ��
    SpawnOtherPlayerCharacter(NewPosition);
}

void Adummy_clientCharacter::Jump()
{
    Super::Jump();

    // ���� ���� ������ ����
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(true, GetActorLocation());
    }
}

void Adummy_clientCharacter::StopJumping()
{
    Super::StopJumping();

    // ���� �ߴ� ���� ������ ����
    if (NetworkManager && NetworkManager->IsConnected())
    {
        NetworkManager->SendJumpPacket(false, GetActorLocation());
    }
}

// �⺻ �Է� �Լ��� ����
void Adummy_clientCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // ���� ī�޶� �ٶ󺸴� ���� ã��
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // ���� ���� ã��
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void Adummy_clientCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // ���� ī�޶� �ٶ󺸴� ���� ã��
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // ������ ���� ã��
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void Adummy_clientCharacter::TurnAtRate(float Rate)
{
    // �ʴ� �Է°��� turn rate ������� ȸ�� ���
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void Adummy_clientCharacter::LookUpAtRate(float Rate)
{
    // �ʴ� �Է°��� look up/down rate ������� ȸ�� ���
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
    // ����
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &Adummy_clientCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &Adummy_clientCharacter::StopJumping);

    // �̵�
    PlayerInputComponent->BindAxis("MoveForward", this, &Adummy_clientCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &Adummy_clientCharacter::MoveRight);

    // ȸ��
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &Adummy_clientCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &Adummy_clientCharacter::LookUpAtRate);

    // ��ġ ��� ����
    PlayerInputComponent->BindTouch(IE_Pressed, this, &Adummy_clientCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &Adummy_clientCharacter::TouchStopped);
}