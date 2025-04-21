// MyNetworkCharacter.cpp
#include "MyNetworkCharacter.h" // �ݵ�� ù ��° include���� ��
#include "SimpleNetworking/Public/NetworkPlayerComponent.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyNetworkCharacter::AMyNetworkCharacter()
{
    // Tick �Լ� Ȱ��ȭ
    PrimaryActorTick.bCanEverTick = true;

    // ��Ʈ��ũ ������Ʈ ����
    NetworkComponent = CreateDefaultSubobject<UNetworkPlayerComponent>(TEXT("NetworkComponent"));

    // ���� ����
    NetworkComponent->ServerIP = "127.0.0.1";
    NetworkComponent->ServerPort = 9000;
    NetworkComponent->bAutoConnectOnBeginPlay = true;

	// ������ ���� ���� �ʱ�ȭ
	LastJumpState = false;

    //ĸ�� ������Ʈ ����
    GetCapsuleComponent()->InitCapsuleSize(34.f, 88.0f);

    //ĳ���� �����Ʈ ������Ʈ ����
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    //��Ʈ�ѷ��� ĳ������ ��(Yaw) ȸ������ ������ �ֵ��� ����
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    //������ �� ���� (ĳ���Ϳ� ī�޶� ������ �Ÿ� ����)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    //�ȷο� ī�޶� ����
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

}

void AMyNetworkCharacter::BeginPlay()
{
    Super::BeginPlay();

    // �ٸ� �÷��̾� ĳ���� Ŭ���� ����
    if (OtherPlayerCharacterClass && NetworkComponent)
    {
        NetworkComponent->OtherPlayerCharacterClass = OtherPlayerCharacterClass;
    }

}

void AMyNetworkCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void AMyNetworkCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AMyNetworkCharacter::ConnectToServer()
{
    if (NetworkComponent)
    {
        return NetworkComponent->ConnectToServer();
    }
    return false;
}

void AMyNetworkCharacter::DisconnectFromServer()
{
    if (NetworkComponent)
    {
        NetworkComponent->DisconnectFromServer();
    }
}

void AMyNetworkCharacter::OnNetworkConnected()
{
    UE_LOG(LogTemp, Display, TEXT("MyNetworkCharacter: Network connected"));
}

void AMyNetworkCharacter::OnNetworkDisconnected()
{
    UE_LOG(LogTemp, Display, TEXT("MyNetworkCharacter: Network disconnected"));
}

void AMyNetworkCharacter::SendPositionToServer()
{
    if (NetworkComponent && NetworkComponent->NetworkManager && NetworkComponent->NetworkManager->IsConnected())
    {
        // ���� ��ġ, ȸ��, �ӵ� ��������
        FVector CurrentLocation = GetActorLocation();
        FRotator CurrentRotation = GetActorRotation();
        FVector CurrentVelocity = GetVelocity();

        // ��Ʈ��ũ �Ŵ����� ���� �̵� ��Ŷ ����
        NetworkComponent->NetworkManager->SendMovePacket(CurrentForwardValue, CurrentRightValue, CurrentLocation, CurrentRotation);

        // ���� ���µ� �Բ� ����
        bool bIsCurrentlyJumping = GetCharacterMovement()->IsFalling();
        if (bIsCurrentlyJumping != LastJumpState)
        {
            NetworkComponent->NetworkManager->SendJumpPacket(bIsCurrentlyJumping, CurrentLocation);
            LastJumpState = bIsCurrentlyJumping;
        }
    }
}