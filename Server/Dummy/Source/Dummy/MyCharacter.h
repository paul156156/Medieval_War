#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
#include "MyCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

// 상태 변경 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCharacterStateChanged, EPlayerState, NewState, const FVector&, Position, const FRotator&, Rotation, const FVector&, Velocity);

UCLASS()
class DUMMY_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    /** 현재 캐릭터 상태 */
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState;

    /** 캐릭터 상태 변경 델리게이트 */
    UPROPERTY(BlueprintAssignable, Category = "State")
    FOnCharacterStateChanged OnCharacterStateChanged;

    /** 입력값 (네트워크 전송용) */
    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentForwardValue;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentRightValue;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentControlRotationYaw;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CurrentControlRotationPitch;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    bool bJumpPressed;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    bool bAttackPressed;

protected:
    /** 네트워크 매니저 참조 */
    UPROPERTY()
    class USimpleNetworkManager* NetworkManager;

    /** Enhanced Input 설정 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* JumpAction;

    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    //UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LeftAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* RightAttackAction;


    /** 카메라 설정 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    /** 전투 관련 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    UAnimMontage* AttackMontage_1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")

    UAnimMontage* AttackMontage_2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")

	UAnimMontage* AttackMontage_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")

    bool bIsAttacking;

    /** 입력 처리 함수 */
    void Move(const FInputActionValue& Value);
    void StopMoving(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    virtual void Jump() override;
    virtual void StopJumping() override;
    void Attack();

    float LogTimer;

    float PrevForwardValue = 0.0f;
    float PrevRightValue = 0.0f;
	float PrevControlRotationYaw = 0.0f;
	float PrevControlRotationPitch = 0.0f;

    bool bLeftMousePressed = false;
    bool bRightMousePressed = false;
	void TryAttack();
	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void OnRightMousePressed();
	void OnRightMouseReleased();
};
