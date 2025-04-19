// Fill out your copyright notice in the Description page of Project Settings.

#include "MyNetworkCharacter.h"
#include "SimpleNetworking/Public/NetworkPlayerComponent.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"

// 생성자
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
}

void AMyNetworkCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 다른 플레이어 캐릭터 클래스 설정
	if (OtherPlayerCharacterClass && NetworkComponent)
	{
		NetworkComponent->OtherPlayerCharacterClass = OtherPlayerCharacterClass;
	}

	// 네트워크 매니저 이벤트 바인딩 - 매니저에 직접 바인딩
	if (NetworkComponent && NetworkComponent->NetworkManager)
	{
		// 올바른 형식으로 델리게이트 바인딩
		USimpleNetworkManager* NetManager = NetworkComponent->NetworkManager;
		if (NetManager)
		{
			// 연결 상태 변경 델리게이트
			NetManager->OnConnectionStatusChanged.AddDynamic(this, &AMyNetworkCharacter::OnConnectionStatusChanged);

			// 플레이어 업데이트 델리게이트
			NetManager->OnPlayerUpdate.AddDynamic(this, &AMyNetworkCharacter::OnPlayerUpdateReceived);

			// 클라이언트 ID 수신 델리게이트
			NetManager->OnClientIdReceived.AddDynamic(this, &AMyNetworkCharacter::OnClientIdReceived);
		}
	}
}

void AMyNetworkCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 델리게이트 바인딩 해제
	if (NetworkComponent && NetworkComponent->NetworkManager)
	{
		USimpleNetworkManager* NetManager = NetworkComponent->NetworkManager;
		if (NetManager)
		{
			NetManager->OnConnectionStatusChanged.RemoveDynamic(this, &AMyNetworkCharacter::OnConnectionStatusChanged);

			NetManager->OnPlayerUpdate.RemoveDynamic(this, &AMyNetworkCharacter::OnPlayerUpdateReceived);

			NetManager->OnClientIdReceived.RemoveDynamic(this, &AMyNetworkCharacter::OnClientIdReceived);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AMyNetworkCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 기본 Tick 동작
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

// 이벤트 핸들러 구현
void AMyNetworkCharacter::OnConnectionStatusChanged(bool IsConnected)
{
	if (IsConnected)
	{
		OnNetworkConnected();
	}
	else
	{
		OnNetworkDisconnected();
	}
}

void AMyNetworkCharacter::OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping)
{
	// 다른 플레이어 캐릭터 업데이트 처리
	UE_LOG(LogTemp, Display, TEXT("Player Update: ClientId=%d Position=%s Rotation=%s Velocity=%s IsJumping=%s"),
		ClientId,
		*Position.ToString(),
		*Rotation.ToString(),
		*Velocity.ToString(),
		IsJumping ? TEXT("true") : TEXT("false"));
}

void AMyNetworkCharacter::OnClientIdReceived(int32 ClientId)
{
	// 클라이언트 ID 수신 처리
	UE_LOG(LogTemp, Display, TEXT("Client ID received: %d"), ClientId);
}

void AMyNetworkCharacter::OnNetworkConnected()
{
	UE_LOG(LogTemp, Display, TEXT("Network connected"));
}

void AMyNetworkCharacter::OnNetworkDisconnected()
{
	UE_LOG(LogTemp, Display, TEXT("Network disconnected"));
}