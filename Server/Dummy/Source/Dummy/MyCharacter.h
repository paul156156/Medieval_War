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

// ���� ���� ��������Ʈ ����
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

    // ���� ����
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EPlayerState CurrentState;

    // ���� ���� �̺�Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Animation")
    FOnCharacterStateChanged OnCharacterStateChanged;

    // �Է� �� ������ (��Ʈ��ũ ���ۿ�)
    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentForwardValue;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentRightValue;

protected:
    // Enhanced Input ���� ������Ʈ
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

    // ī�޶� ������Ʈ
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* FollowCamera;

    // �ִϸ��̼� ��Ÿ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bIsAttacking;

    // �Է� �Լ�
    void Move(const FInputActionValue& Value);
	void StopMoving(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    virtual void Jump() override;
    virtual void StopJumping() override;
    void Attack();

    // ���� ������Ʈ �Լ�
    void UpdateCharacterState();
};