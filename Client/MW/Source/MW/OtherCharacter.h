// OtherCharacter.h - ���� �÷��̾� ���� ĳ���� Ŭ����
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacketTypes.h"
#include "NetworkManager.h"
#include "OtherCharacter.generated.h"

UCLASS()
class MW_API AOtherCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AOtherCharacter();

    // ��Ʈ��ũ���� ������Ʈ �ޱ�
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState);

    // �÷��̾� ID ������
    void SetPlayerId(int32 Id) { PlayerId = Id; }
    int32 GetPlayerId() const { return PlayerId; }

    // ���� ���� ���� (�׻� true)
    void SetIsRemoteControlled(bool bRemote) { bIsRemoteControlled = bRemote; }
    bool IsRemoteControlled() const { return bIsRemoteControlled; }

    // ���� �÷��̾� ���� (�׻� false)
    bool IsLocalPlayer() const { return false; }

    // �÷��̾� ���� (�б� ����)
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

    // �ٸ� �÷��̾��� �Է� ���� (�ð�ȭ��)
    float NetworkForwardInput = 0.0f;
    float NetworkRightInput = 0.0f;
    bool bNetworkRunPressed = false;
    bool bNetworkJumpPressed = false;
    bool bNetworkAttackPressed = false;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // ��Ʈ��ũ ���� �Լ���
    void InterpolateRemoteMovement(float DeltaTime);
    void DisplayNetworkDebugInfo();

    // �÷��̾� ID
    int32 PlayerId = -1;

    // ���� ���� ���� (�׻� true)
    UPROPERTY(BlueprintReadOnly, Category = "Network")
    bool bIsRemoteControlled = true;

    // �ִϸ��̼�
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    // ���� ��� (��Ʈ��ũ ����ȭ��)
    FVector TargetLocation = FVector::ZeroVector;
    FRotator TargetRotation = FRotator::ZeroRotator;
    FVector TargetVelocity = FVector::ZeroVector;
    bool bInitialPositionSet = false;

    // ���� ����
    UPROPERTY(EditAnywhere, Category = "Network")
    float InterpSpeed = 12.0f;  // ���� �÷��̾�� ���� �� ������ ����

    UPROPERTY(EditAnywhere, Category = "Network")
    float VelocityInterpSpeed = 8.0f;

    // ����� ǥ�� ����
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bShowDebugInfo = true;

    // ��Ʈ��ũ ������Ʈ ����
    float LastNetworkUpdateTime = 0.0f;
    float NetworkUpdateFrequency = 0.0f;  // ������Ʈ �� ����

private:
    // ������Ʈ �� ����
    float LastUpdateTime = 0.0f;
    int32 UpdateCount = 0;

    // ���� �Լ���
    FString GetPlayerStateString() const;
    FString GetMovementModeString() const;
    FColor GetDebugTextColor() const;
    FColor GetStateCircleColor() const;
    void DrawNetworkStatusVisuals(const FVector& Location) const;
};