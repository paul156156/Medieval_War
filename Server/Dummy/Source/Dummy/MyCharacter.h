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

// ���� ���� ��������Ʈ
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

    /** ���� ĳ���� ���� */
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState;

    /** ĳ���� ���� ���� ��������Ʈ */
    UPROPERTY(BlueprintAssignable, Category = "State")
    FOnCharacterStateChanged OnCharacterStateChanged;

    /** �Է°� (��Ʈ��ũ ���ۿ�) */
    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentForwardValue;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentRightValue;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    float CurrentControlRotationYaw;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    bool bJumpPressed;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    bool bAttackPressed;

protected:
    /** ��Ʈ��ũ �Ŵ��� ���� */
    UPROPERTY()
    class USimpleNetworkManager* NetworkManager;

    /** Enhanced Input ���� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* AttackAction;

    /** ī�޶� ���� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    /** ���� ���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    bool bIsAttacking;

    /** �Է� ó�� �Լ� */
    void Move(const FInputActionValue& Value);
    void StopMoving(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    virtual void Jump() override;
    virtual void StopJumping() override;
    void Attack();
};
