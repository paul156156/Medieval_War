// Copyright Epic Games, Inc. All Rights Reserved.

#include "dummy_clientGameMode.h"
#include "dummy_clientCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "NetworkManager.h"

Adummy_clientGameMode::Adummy_clientGameMode()
	: NetworkManager(nullptr)
	, ServerIP(TEXT("127.0.0.1"))
	, ServerPort(9000)
	, bAutoConnect(true)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void Adummy_clientGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 네트워크 매니저 생성
    NetworkManager = NewObject<UNetworkManager>(this);

    // 자동 연결 설정된 경우 서버에 연결
    if (bAutoConnect && NetworkManager)
    {
        NetworkManager->ConnectToServer(ServerIP, ServerPort);
    }
}

UNetworkManager* Adummy_clientGameMode::GetNetworkManager() const
{
    return NetworkManager;
}