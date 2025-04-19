// Fill out your copyright notice in the Description page of Project Settings.

#include "MyNetworkCharacter.h"
#include "SimpleNetworking/Public/NetworkPlayerComponent.h"
#include "SimpleNetworking/Public/SimpleNetworkManager.h"

// ������
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
}

void AMyNetworkCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �ٸ� �÷��̾� ĳ���� Ŭ���� ����
	if (OtherPlayerCharacterClass && NetworkComponent)
	{
		NetworkComponent->OtherPlayerCharacterClass = OtherPlayerCharacterClass;
	}

	// ��Ʈ��ũ �Ŵ��� �̺�Ʈ ���ε� - �Ŵ����� ���� ���ε�
	if (NetworkComponent && NetworkComponent->NetworkManager)
	{
		// �ùٸ� �������� ��������Ʈ ���ε�
		USimpleNetworkManager* NetManager = NetworkComponent->NetworkManager;
		if (NetManager)
		{
			// ���� ���� ���� ��������Ʈ
			NetManager->OnConnectionStatusChanged.AddDynamic(this, &AMyNetworkCharacter::OnConnectionStatusChanged);

			// �÷��̾� ������Ʈ ��������Ʈ
			NetManager->OnPlayerUpdate.AddDynamic(this, &AMyNetworkCharacter::OnPlayerUpdateReceived);

			// Ŭ���̾�Ʈ ID ���� ��������Ʈ
			NetManager->OnClientIdReceived.AddDynamic(this, &AMyNetworkCharacter::OnClientIdReceived);
		}
	}
}

void AMyNetworkCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ��������Ʈ ���ε� ����
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
	// �⺻ Tick ����
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

// �̺�Ʈ �ڵ鷯 ����
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
	// �ٸ� �÷��̾� ĳ���� ������Ʈ ó��
	UE_LOG(LogTemp, Display, TEXT("Player Update: ClientId=%d Position=%s Rotation=%s Velocity=%s IsJumping=%s"),
		ClientId,
		*Position.ToString(),
		*Rotation.ToString(),
		*Velocity.ToString(),
		IsJumping ? TEXT("true") : TEXT("false"));
}

void AMyNetworkCharacter::OnClientIdReceived(int32 ClientId)
{
	// Ŭ���̾�Ʈ ID ���� ó��
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