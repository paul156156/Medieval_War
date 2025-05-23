// AOtherPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "MyPlayerCharacter.h"
#include "OtherPlayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AOtherPlayerCharacter : public AMyPlayerCharacter
{
    GENERATED_BODY()

public:
    AOtherPlayerCharacter();
};