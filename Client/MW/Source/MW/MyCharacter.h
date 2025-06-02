// MyCharacter.h - ������ ���� ����
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "PacketTypes.h"
#include "NetworkManager.h"
#include "MyCharacter.generated.h"

UCLASS()
class MW_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

    // ===== �÷��̾� Ÿ�� ���� =====
    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetIsLocalPlayer(bool bLocal);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetIsRemoteControlled(bool bRemote);

    UFUNCTION(BlueprintPure, Category = "Player")
    virtual bool IsLocalPlayer() const { return bIsLocalPlayer; }

    UFUNCTION(BlueprintPure, Category = "Player")
    virtual bool IsRemoteControlled() const { return bIsRemoteControlled; }

    // ===== �÷��̾� ID ���� =====
    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetPlayerId(int32 Id) { PlayerId = Id; }

    UFUNCTION(BlueprintPure, Category = "Player")
    int32 GetPlayerId() const { return PlayerId; }

    // ===== ��Ʈ��ũ ���� =====
    void NotifySpawn();

    UFUNCTION(BlueprintCallable, Category = "Network")
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction);

    // ===== ī�޶� �� �Է� ���� =====
    UFUNCTION(BlueprintCallable, Category = "Control")
    void DisableCameraAndInput();

    UFUNCTION(BlueprintCallable, Category = "Control")
    void EnableCameraAndInput();

    // ===== �÷��̾� ���� (�ܺο��� �б��) =====
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

    UPROPERTY(BlueprintReadOnly, Category = "Action")
    EPlayerAction CurrentAction = EPlayerAction::NONE;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    // ===== �Է� ó�� �Լ��� =====
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);
    void StartDefend(const FInputActionValue& Value);
    void StopDefend(const FInputActionValue& Value);

    // ===== ��Ʈ��ũ ���� �Լ��� =====
    void SendInputToServer();
    void InterpolateToServerPosition(float DeltaTime);

    // ===== ����� ���� ǥ�� =====
    void DisplayDebugInfo();

    // ===== �÷��̾� ���� ������ =====
    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    bool bIsLocalPlayer = true;  // �⺻���� ���� �÷��̾�

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    bool bIsRemoteControlled = false;

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    int32 PlayerId = -1;

    // ===== Enhanced Input ���� =====
    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* RunAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* AttackAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* DefendAction;

    // ===== ī�޶� ������Ʈ =====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    // ===== �ִϸ��̼� =====
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* DefendMontage;

    // ===== ����/��� Ÿ�̸� =====
    FTimerHandle AttackResetHandle;
    FTimerHandle DefendResetHandle;

    // ===== �Է� ���� (���� ���ۿ�) =====
    float ForwardInput = 0.0f;
    float RightInput = 0.0f;
    float PitchInput = 0.0f;
    float YawInput = 0.0f;
    float RollInput = 0.0f;
    bool bRunPressed = false;
    bool bJumpPressed = false;
    bool bAttackPressed = false;
    bool bDefendPressed = false;

    // ===== ���� �Է°� (���� ������) =====
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
    float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;
    bool bPreviousDefendPressed = false;

    // ===== �̵� ��� ���� �ɼ� =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bAlwaysFaceMovementDirection = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bUseCameraRelativeMovement = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementRotationRate = 500.0f;

    // ===== ��Ʈ��ũ ������Ʈ ���� =====
    UPROPERTY(EditAnywhere, Category = "Network")
    float InputSendRate = 60.0f; // �ʴ� 60ȸ ����

    float LastInputSendTime = 0.0f;

    // ===== ���� ����ȭ�� =====
    UPROPERTY(BlueprintReadOnly, Category = "Network State")
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Network State")
    FRotator TargetRotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadOnly, Category = "Network State")
    FVector TargetVelocity = FVector::ZeroVector;

    bool bInitialPositionSet = false;

    // ===== ��Ʈ��ũ ���� ���� =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Interpolation")
    float InterpSpeed = 12.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Interpolation")
    float VelocityInterpSpeed = 8.0f;

    // ===== ����� ���� =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool bShowDebugInfo = false;

private:
    // ===== ���� �Լ��� =====
    bool HasInputChanged() const;

    // ===== ����� ���� �Լ��� =====
    FString GetStateString(EPlayerState State) const;
    FString GetActionString(EPlayerAction Action) const;
    FString GetPlayerTypeString() const;
    FColor GetDebugColor() const;
    void DrawMovementVectors(const FVector& Location, const FVector& Velocity) const;
};