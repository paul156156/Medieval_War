// MyPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PacketTypes.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERGAME_API AMyPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyPlayerCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    void NotifySpawn();
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
    void InterpolateRemoteMovement(float DeltaTime);

    int32 PlayerId;
    bool bIsLocalPlayer;
public:
    virtual void UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState);

    void SetPlayerId(int32 Id) { PlayerId = Id; }
    int32 GetPlayerId() const { return PlayerId; }

    void SetIsLocalPlayer(bool bLocal) { bIsLocalPlayer = bLocal; }
    bool IsLocalPlayer() const { return bIsLocalPlayer; }

    bool bRunPressed = false;
    bool bCrouchPressed = false;
    bool bAttackPressed = false;
    bool bJumpPressed = false;
    bool bIsAttackPressed = false;
protected:
    UPROPERTY(BlueprintReadOnly)
    bool bIsRemoteControlled = false;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* RunAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* CrouchAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* AttackAction;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    class UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    UPROPERTY(EditAnywhere, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

    // 서버 입력용
    float ForwardInput = 0.f;
    float RightInput = 0.f;
    float ControlRotationPitch = 0.f;
    float ControlRotationYaw = 0.f;
    float ControlRotationRoll = 0.f;

    FTimerHandle AttackResetHandle;

    // 보간 대상
    FVector TargetLocation;
    FRotator TargetRotation;
    bool bInitialPositionSet = false;

    UPROPERTY(EditAnywhere, Category = "Interp")
    float InterpSpeed = 10.f;
};