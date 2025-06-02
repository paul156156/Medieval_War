// OtherCharacter.h - MyCharacter ������� ���� �÷��̾� ����
#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "OtherCharacter.generated.h"

UCLASS()
class MW_API AOtherCharacter : public AMyCharacter
{
    GENERATED_BODY()

public:
    AOtherCharacter();

    // ���� �÷��̾� ���� �������̵� (�׻� false)
    //virtual bool IsLocalPlayer() const override { return false; }
    //virtual bool IsRemoteControlled() const override { return true; }

    // ��Ʈ��ũ ������Ʈ �Լ� �������̵�
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction) override;

    // �ٸ� �÷��̾��� �Է� ���� (�ð�ȭ�� - �����κ��� ����)
    float NetworkForwardInput = 0.0f;
    float NetworkRightInput = 0.0f;
    bool bNetworkRunPressed = false;
    bool bNetworkJumpPressed = false;
    bool bNetworkAttackPressed = false;
    bool bNetworkDefendPressed = false;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    // ���� �÷��̾� ���� �Լ���
    void DisplayNetworkDebugInfo();

    // ��Ʈ��ũ ������Ʈ ����
    float LastNetworkUpdateTime = 0.0f;
    float NetworkUpdateFrequency = 0.0f;

private:
    // ������Ʈ �� ����
    float LastUpdateTime = 0.0f;
    int32 UpdateCount = 0;

    // ���� �÷��̾� �ʱ�ȭ
    void InitializeAsRemotePlayer();

    // ���� �Լ��� (����׿�)
    FString GetPlayerStateString() const;
	FString GetPlayerActionString() const;
    FString GetMovementModeString() const;
    FColor GetNetworkStatusColor() const;
    FColor GetStateCircleColor() const;
	FColor GetActionCircleColor() const;
    void DrawNetworkStatusVisuals(const FVector& Location) const;
};