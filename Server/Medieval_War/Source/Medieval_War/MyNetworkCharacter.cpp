// MyNetworkCharacter.cpp
#include "MyNetworkCharacter.h" // 반드시 첫 번째 include여야 함
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
    // Tick 함수 활성화
    PrimaryActorTick.bCanEverTick = true;

    // 네트워크 컴포넌트 생성
    NetworkComponent = CreateDefaultSubobject<UNetworkPlayerComponent>(TEXT("NetworkComponent"));

    // 서버 설정
    NetworkComponent->ServerIP = "127.0.0.1";
    NetworkComponent->ServerPort = 9000;
    NetworkComponent->bAutoConnectOnBeginPlay = true;

	// 마지막 점프 상태 초기화
	LastJumpState = false;

    //캡슐 컴포넌트 설정
    GetCapsuleComponent()->InitCapsuleSize(34.f, 88.0f);

    //캐릭터 무브먼트 컴포넌트 설정
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    //컨트롤러가 캐릭터의 요(Yaw) 회전에만 영향을 주도록 설정
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    //스프링 암 생성 (캐릭터와 카메라 사이의 거리 조절)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    //팔로우 카메라 생성
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

}

void AMyNetworkCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 다른 플레이어 캐릭터 클래스 설정
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
        // 현재 위치, 회전, 속도 가져오기
        FVector CurrentLocation = GetActorLocation();
        FRotator CurrentRotation = GetActorRotation();
        FVector CurrentVelocity = GetVelocity();

        // 네트워크 매니저를 통해 이동 패킷 전송
        NetworkComponent->NetworkManager->SendMovePacket(CurrentForwardValue, CurrentRightValue, CurrentLocation, CurrentRotation);

        // 점프 상태도 함께 전송
        bool bIsCurrentlyJumping = GetCharacterMovement()->IsFalling();
        if (bIsCurrentlyJumping != LastJumpState)
        {
            NetworkComponent->NetworkManager->SendJumpPacket(bIsCurrentlyJumping, CurrentLocation);
            LastJumpState = bIsCurrentlyJumping;
        }
    }
}