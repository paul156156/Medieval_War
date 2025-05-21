// MyPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "MultiplayerBaseCharacter.h"
#include "InputActionValue.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AMyPlayerCharacter : public AMultiplayerBaseCharacter
{
    GENERATED_BODY()

public:
    AMyPlayerCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState) override;

    void Move(const FInputActionValue& Value);
	void StartRun(const FInputActionValue& Value);
	void StopRun(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartCrouch(const FInputActionValue& Value);
	void StopCrouch(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);

    void SendInputToServer();

    float ForwardInput;
    float RightInput;
    float ControlRotationPitch;
    float ControlRotationYaw;
    float ControlRotationRoll;

	bool bRunPressed;
    bool bCrouchPressed;
    bool bAttackPressed;
    bool bJumpPressed;

    FTimerHandle AttackResetHandle;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* RunAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "input")
	class UInputAction* CrouchAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* AttackAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Combat")
    bool bIsAttacked = false;
};