// Copyright Epic Games, Inc. All Rights Reserved.

#include "dummy_clientGameMode.h"
#include "dummy_clientCharacter.h"
#include "UObject/ConstructorHelpers.h"

Adummy_clientGameMode::Adummy_clientGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
