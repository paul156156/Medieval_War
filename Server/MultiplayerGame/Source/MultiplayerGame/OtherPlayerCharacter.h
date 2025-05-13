// OtherPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "MultiplayerBaseCharacter.h"
#include "OtherPlayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AOtherPlayerCharacter : public AMultiplayerBaseCharacter
{
    GENERATED_BODY()

public:
    AOtherPlayerCharacter();

    virtual void Tick(float DeltaSeconds) override;
    virtual void UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState) override;

protected:
    FVector TargetLocation;
    FRotator TargetRotation;

    bool bInitialPositionSet = false;
    UPROPERTY(EditAnywhere, Category = "Movement")
    float InterpSpeed = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UAnimMontage* AttackMontage;
};