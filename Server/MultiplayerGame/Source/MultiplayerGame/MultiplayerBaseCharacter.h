// MultiplayerBaseCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacketTypes.h"
#include "MultiplayerBaseCharacter.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AMultiplayerBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly)
    int32 PlayerId;

    UPROPERTY(BlueprintReadOnly)
    bool bIsLocalPlayer;

    UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
    EPlayerState CurrentState = EPlayerState::IDLE;

    virtual void UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState);

    void SetPlayerId(int32 Id) { PlayerId = Id; }
    void SetIsLocalPlayer(bool bLocal) { bIsLocalPlayer = bLocal; }
    bool IsLocalPlayer() const { return bIsLocalPlayer; }
};