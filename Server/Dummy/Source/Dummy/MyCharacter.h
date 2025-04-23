// MyCharacter.h
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

// 상태 변경 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCharacterStateChanged, EPlayerState, NewState, const FVector&, Position, const FRotator&, Rotation);

UCLASS()
class DUMMY_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // 현재 상태
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EPlayerState CurrentState;

    // 상태 변경 이벤트
    UPROPERTY(BlueprintAssignable, Category = "Animation")
    FOnCharacterStateChanged OnCharacterStateChanged;

    // 입력 값 접근자 (네트워크 전송용)
    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentForwardValue;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentRightValue;

protected:
    // Enhanced Input 관련 컴포넌트
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* AttackAction;

    // 카메라 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* FollowCamera;

    // 애니메이션 몽타주
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bIsAttacking;

    // 입력 함수
    void Move(const FInputActionValue& Value);
	void StopMoving(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    virtual void Jump() override;
    virtual void StopJumping() override;
    void Attack();

    // 상태 업데이트 함수
    void UpdateCharacterState();
};