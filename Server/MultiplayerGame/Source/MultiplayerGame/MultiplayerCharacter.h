// MultiplayerCharacter.h
// 게임 내 플레이어 캐릭터 클래스

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
    // 생성자
    AMultiplayerCharacter();

protected:
    // 게임 시작 시 호출
    virtual void BeginPlay() override;

public:
    // 매 프레임 호출
    virtual void Tick(float DeltaTime) override;

    // 입력 설정을 위해 호출
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 네트워크 위치 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "Network")
    void UpdateFromNetwork(const FTransform& NewTransform, EPlayerState NewState);

    // 플레이어 ID 설정
    UFUNCTION(BlueprintCallable, Category = "Network")
    void SetPlayerId(int32 NewPlayerId) { PlayerId = NewPlayerId; }

    // 플레이어 ID 반환
    UFUNCTION(BlueprintPure, Category = "Network")
    int32 GetPlayerId() const { return PlayerId; }

    // 로컬 플레이어 여부 설정
    UFUNCTION(BlueprintCallable, Category = "Network")
    void SetIsLocalPlayer(bool bNewIsLocalPlayer) { bIsLocalPlayer = bNewIsLocalPlayer; }

    // 로컬 플레이어 여부 반환
    UFUNCTION(BlueprintPure, Category = "Network")
    bool IsLocalPlayer() const { return bIsLocalPlayer; }

    // 현재 상태 반환
    UFUNCTION(BlueprintPure, Category = "Character")
    EPlayerState GetCurrentState() const { return CurrentState; }

    // 마지막 상태 변경 시간 반환
    UFUNCTION(BlueprintPure, Category = "Character")
    float GetLastStateChangeTime() const { return LastStateChangeTime; }

    // 컨트롤 회전 설정
    UFUNCTION(BlueprintCallable, Category = "Character")
    void SetControlRotationYaw(float NewYaw) { ControlRotationYaw = NewYaw; }

    // 컨트롤 회전 반환
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

    // 상태 변경 함수
    void SetCurrentState(EPlayerState NewState);

    // 공격 완료 타이머 콜백
    void OnAttackFinished();

    // 애니메이션 세팅
    void UpdateAnimationState();

private:
    // 플레이어 ID
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    int32 PlayerId;

    // 로컬 플레이어 여부
    UPROPERTY(BlueprintReadOnly, Category = "Network", meta = (AllowPrivateAccess = "true"))
    bool bIsLocalPlayer;

    // 현재 플레이어 상태
    UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
    EPlayerState CurrentState;

    // 입력값 저장 변수
    float ForwardInput;
    float RightInput;
    float ControlRotationYaw;

    // 상태 관련 변수
    float LastStateChangeTime;
    FTimerHandle AttackTimerHandle;

    // 스프링 암 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    // 카메라 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;

    // 애니메이션 관련 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    class UAnimMontage* AttackMontage;

    // 공격 애니메이션 재생 시간 (초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float AttackAnimDuration;

public:
    // 게터 함수
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE float GetForwardInput() const { return ForwardInput; }
    FORCEINLINE float GetRightInput() const { return RightInput; }
};