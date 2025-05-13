// MultiplayerCharacter.h
// ���� �� �÷��̾� ĳ���� Ŭ����

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacketTypes.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "MultiplayerCharacter.generated.h"

class UEnhancedInputComponent;

UCLASS()
class MULTIPLAYERGAME_API AMultiplayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // ������
    AMultiplayerCharacter();

protected:
    // ���� ���� �� ȣ��
    virtual void BeginPlay() override;

public:
    // �� ������ ȣ��
    virtual void Tick(float DeltaTime) override;

    // �Է� ������ ���� ȣ��
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // ��Ʈ��ũ ��ġ ������Ʈ �Լ�
    UFUNCTION(BlueprintCallable, Category = "Network")
    void UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState);

    // �÷��̾� ID ����
    UFUNCTION(BlueprintCallable, Category = "Network")
    void SetPlayerId(int32 NewPlayerId) { PlayerId = NewPlayerId; }

    // �÷��̾� ID ��ȯ
    UFUNCTION(BlueprintPure, Category = "Network")
    int32 GetPlayerId() const { return PlayerId; }

    // ���� �÷��̾� ���� ����
    UFUNCTION(BlueprintCallable, Category = "Network")
    void SetIsLocalPlayer(bool bNewIsLocalPlayer) { bIsLocalPlayer = bNewIsLocalPlayer; }

    // ���� �÷��̾� ���� ��ȯ
    UFUNCTION(BlueprintPure, Category = "Network")
    bool IsLocalPlayer() const { return bIsLocalPlayer; }

    // ���� ���� ��ȯ
    UFUNCTION(BlueprintPure, Category = "Character")
    EPlayerState GetCurrentState() const { return CurrentState; }

    // ������ ���� ���� �ð� ��ȯ
    UFUNCTION(BlueprintPure, Category = "Character")
    float GetLastStateChangeTime() const { return LastStateChangeTime; }

    // ��Ʈ�� ȸ�� ����
    UFUNCTION(BlueprintCallable, Category = "Character")
    void SetControlRotationYaw(float NewYaw) { ControlRotationYaw = NewYaw; }

    // ��Ʈ�� ȸ�� ��ȯ
    UFUNCTION(BlueprintPure, Category = "Character")
    float GetControlRotationYaw() const { return ControlRotationYaw; }

protected:
    // Enhanced Input Actions
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    TSoftObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    TSoftObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    TSoftObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    TSoftObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    TSoftObjectPtr<UInputAction> AttackAction;

    // Enhanced Input Functions
    void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);

    // ���� ���� �Լ�
    void SetCurrentState(EPlayerState NewState);

    // ���� �Ϸ� Ÿ�̸� �ݹ�
    void OnAttackFinished();

    // �ִϸ��̼� ����
    void UpdateAnimationState();

private:
    // �÷��̾� ID
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    int32 PlayerId;

    // ���� �÷��̾� ����
    UPROPERTY(BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    bool bIsLocalPlayer;

    // ���� �÷��̾� ����
    UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
    EPlayerState CurrentState;

    // �Է°� ���� ����
    float ForwardInput;
    float RightInput;
    float ControlRotationYaw;

    // ���� ���� ����
    float LastStateChangeTime;
    FTimerHandle AttackTimerHandle;

    // ������ �� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    // ī�޶� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

    // �ִϸ��̼� ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    class UAnimMontage* AttackMontage;

    // ���� �ִϸ��̼� ��� �ð� (��)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float AttackAnimDuration;

public:
    // ���� �Լ�
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE float GetForwardInput() const { return ForwardInput; }
    FORCEINLINE float GetRightInput() const { return RightInput; }
};