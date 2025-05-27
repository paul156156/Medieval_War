// MyCharacter.h
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

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    // �Է� ó�� �Լ���
    void NotifySpawn();
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);

    // ��Ʈ��ũ ���� �Լ���
    void SendInputToServer();
    void InterpolateRemoteMovement(float DeltaTime);

    // ����� ���� ǥ�� �Լ� �߰�
    void DisplayDebugInfo();

    // �÷��̾� ID ����
    int32 PlayerId = -1;
    bool bIsLocalPlayer = false;

public:
    // ��Ʈ��ũ���� ������Ʈ �ޱ�
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState);

    // �÷��̾� ID ������
    void SetPlayerId(int32 Id) { PlayerId = Id; }
    int32 GetPlayerId() const { return PlayerId; }

    // ���� �÷��̾� ����
    void SetIsLocalPlayer(bool bLocal) { bIsLocalPlayer = bLocal; }
    bool IsLocalPlayer() const { return bIsLocalPlayer; }

    // ���� ���� ����
    void SetIsRemoteControlled(bool bRemote) { bIsRemoteControlled = bRemote; }
    bool IsRemoteControlled() const { return bIsRemoteControlled; }

    // �Է� ���� (���� ���ۿ�)
    float ForwardInput = 0.0f;
    float RightInput = 0.0f;
    float PitchInput = 0.0f;
    float YawInput = 0.0f;
    float RollInput = 0.0f;
    bool bRunPressed = false;
    bool bJumpPressed = false;
    bool bAttackPressed = false;

    // �Է��� ����Ǿ����� üũ (���ʿ��� ���� ����)
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
	float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;

    // �̵� ��� ���� �ɼ�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bAlwaysFaceMovementDirection = true;  // �׻� �̵� ������ ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bUseCameraRelativeMovement = true;    // ī�޶� ���� �̵�

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementRotationRate = 500.0f;      // ȸ�� �ӵ� ����

    // �÷��̾� ���¸� public���� ����
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

protected:
    // ���� ���� ����
    UPROPERTY(BlueprintReadOnly, Category = "Network")
    bool bIsRemoteControlled = false;

    // Enhanced Input ����
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

    // ī�޶� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    // �ִϸ��̼�
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    // ���� Ÿ�̹�
    FTimerHandle AttackResetHandle;

    // ���� ��� (��Ʈ��ũ ����ȭ��)
    FVector TargetLocation = FVector::ZeroVector;
    FRotator TargetRotation = FRotator::ZeroRotator;
    FVector TargetVelocity = FVector::ZeroVector;
    bool bInitialPositionSet = false;

    // ���� ����
    UPROPERTY(EditAnywhere, Category = "Network")
    float InterpSpeed = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Network")
    float VelocityInterpSpeed = 5.0f;

    // ��Ʈ��ũ ������Ʈ �� ����
    float LastInputSendTime = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Network")
    float InputSendRate = 60.0f; // �ʴ� 60ȸ ����

    // ����� ǥ�� ����
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bShowDebugInfo = true;

private:
    // �Է� ���� ����
    bool HasInputChanged() const;
};