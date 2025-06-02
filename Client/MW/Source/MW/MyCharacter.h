// MyCharacter.h - 수정된 통합 버전
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

    // ===== 플레이어 타입 관리 =====
    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetIsLocalPlayer(bool bLocal);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetIsRemoteControlled(bool bRemote);

    UFUNCTION(BlueprintPure, Category = "Player")
    virtual bool IsLocalPlayer() const { return bIsLocalPlayer; }

    UFUNCTION(BlueprintPure, Category = "Player")
    virtual bool IsRemoteControlled() const { return bIsRemoteControlled; }

    // ===== 플레이어 ID 관리 =====
    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetPlayerId(int32 Id) { PlayerId = Id; }

    UFUNCTION(BlueprintPure, Category = "Player")
    int32 GetPlayerId() const { return PlayerId; }

    // ===== 네트워크 관련 =====
    void NotifySpawn();

    UFUNCTION(BlueprintCallable, Category = "Network")
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction);

    // ===== 카메라 및 입력 제어 =====
    UFUNCTION(BlueprintCallable, Category = "Control")
    void DisableCameraAndInput();

    UFUNCTION(BlueprintCallable, Category = "Control")
    void EnableCameraAndInput();

    // ===== 플레이어 상태 (외부에서 읽기용) =====
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

    UPROPERTY(BlueprintReadOnly, Category = "Action")
    EPlayerAction CurrentAction = EPlayerAction::NONE;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    // ===== 입력 처리 함수들 =====
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);
    void StartDefend(const FInputActionValue& Value);
    void StopDefend(const FInputActionValue& Value);

    // ===== 네트워크 관련 함수들 =====
    void SendInputToServer();
    void InterpolateToServerPosition(float DeltaTime);

    // ===== 디버그 정보 표시 =====
    void DisplayDebugInfo();

    // ===== 플레이어 상태 변수들 =====
    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    bool bIsLocalPlayer = true;  // 기본값은 로컬 플레이어

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    bool bIsRemoteControlled = false;

    UPROPERTY(BlueprintReadOnly, Category = "Player State")
    int32 PlayerId = -1;

    // ===== Enhanced Input 설정 =====
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

    // ===== 카메라 컴포넌트 =====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    // ===== 애니메이션 =====
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* DefendMontage;

    // ===== 공격/방어 타이머 =====
    FTimerHandle AttackResetHandle;
    FTimerHandle DefendResetHandle;

    // ===== 입력 상태 (서버 전송용) =====
    float ForwardInput = 0.0f;
    float RightInput = 0.0f;
    float PitchInput = 0.0f;
    float YawInput = 0.0f;
    float RollInput = 0.0f;
    bool bRunPressed = false;
    bool bJumpPressed = false;
    bool bAttackPressed = false;
    bool bDefendPressed = false;

    // ===== 이전 입력값 (변경 감지용) =====
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
    float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;
    bool bPreviousDefendPressed = false;

    // ===== 이동 방식 설정 옵션 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bAlwaysFaceMovementDirection = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bUseCameraRelativeMovement = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementRotationRate = 500.0f;

    // ===== 네트워크 업데이트 설정 =====
    UPROPERTY(EditAnywhere, Category = "Network")
    float InputSendRate = 60.0f; // 초당 60회 전송

    float LastInputSendTime = 0.0f;

    // ===== 서버 동기화용 =====
    UPROPERTY(BlueprintReadOnly, Category = "Network State")
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Network State")
    FRotator TargetRotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadOnly, Category = "Network State")
    FVector TargetVelocity = FVector::ZeroVector;

    bool bInitialPositionSet = false;

    // ===== 네트워크 보간 설정 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Interpolation")
    float InterpSpeed = 12.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Interpolation")
    float VelocityInterpSpeed = 8.0f;

    // ===== 디버그 설정 =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool bShowDebugInfo = false;

private:
    // ===== 헬퍼 함수들 =====
    bool HasInputChanged() const;

    // ===== 디버그 헬퍼 함수들 =====
    FString GetStateString(EPlayerState State) const;
    FString GetActionString(EPlayerAction Action) const;
    FString GetPlayerTypeString() const;
    FColor GetDebugColor() const;
    void DrawMovementVectors(const FVector& Location, const FVector& Velocity) const;
};