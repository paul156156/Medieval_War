// MyCharacter.h - 로컬 플레이어 전용으로 정리
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

    void NotifySpawn();

    // 플레이어 ID 접근자
    //void SetPlayerId(int32 Id) { PlayerId = Id; }
    //int32 GetPlayerId() const { return PlayerId; }

    // 로컬 플레이어 여부 (항상 true)
    //virtual bool IsLocalPlayer() const { return true; }
    //virtual bool IsRemoteControlled() const { return false; }

    // 추가: GameMode에서 호출할 수 있도록 더미 함수들 (호환성 유지)
    //void SetIsLocalPlayer(bool bLocal) { /* MyCharacter는 항상 로컬 플레이어 */ }
    //void SetIsRemoteControlled(bool bRemote) { /* MyCharacter는 항상 로컬 플레이어 */ }

    // 네트워크에서 업데이트 받기 (GameMode에서 접근 가능하도록 public)
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction);

    // 플레이어 상태 (외부에서 읽기용)
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

    UPROPERTY(BlueprintReadOnly, Category = "Action")
    EPlayerAction CurrentAction = EPlayerAction::NONE;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    // 입력 처리 함수들 (로컬 플레이어 전용)
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);
    void StartDefend(const FInputActionValue& Value);
    void StopDefend(const FInputActionValue& Value);

    // 네트워크 관련 함수들
    void SendInputToServer();
    void InterpolateToServerPosition(float DeltaTime);

    // 디버그 정보 표시
    void DisplayDebugInfo();

    // 플레이어 ID
    int32 PlayerId = -1;

    // Enhanced Input 설정
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

    // 카메라 컴포넌트 (로컬 플레이어만)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    // 애니메이션
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* DefendMontage;

    //UPROPERTY(EditAnywhere, Category = "Animation")
    //float DefendMontageDuration = 1.0f;

    // 공격/방어 타이머
    FTimerHandle AttackResetHandle;
    FTimerHandle DefendResetHandle;

    // 입력 상태 (서버 전송용)
    float ForwardInput = 0.0f;
    float RightInput = 0.0f;
    float PitchInput = 0.0f;
    float YawInput = 0.0f;
    float RollInput = 0.0f;
    bool bRunPressed = false;
    bool bJumpPressed = false;
    bool bAttackPressed = false;
    bool bDefendPressed = false;

    // 입력이 변경되었는지 체크 (불필요한 전송 방지)
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
    float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;
    bool bPreviousDefendPressed = false;

    // 이동 방식 설정 옵션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bAlwaysFaceMovementDirection = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bUseCameraRelativeMovement = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementRotationRate = 500.0f;

    // 네트워크 업데이트 빈도 제한
    float LastInputSendTime = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Network")
    float InputSendRate = 60.0f; // 초당 60회 전송

    // 서버 동기화용 (로컬 플레이어도 서버 위치로만 이동)
    FVector TargetLocation = FVector::ZeroVector;
    FRotator TargetRotation = FRotator::ZeroRotator;
    FVector TargetVelocity = FVector::ZeroVector;
    bool bInitialPositionSet = false;

    UPROPERTY(EditAnywhere, Category = "Network")
    float InterpSpeed = 10.0f;  // 서버 위치로 보간 속도

    UPROPERTY(EditAnywhere, Category = "Network")
    float VelocityInterpSpeed = 10.0f;  // 속도 보간 속도

    // 디버그 표시 여부
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bShowDebugInfo = false;

private:
    // 입력 변경 감지
    bool HasInputChanged() const;

    // 디버그 헬퍼 함수들
    FString GetStateString(EPlayerState State) const;
	FString GetActionString(EPlayerAction Action) const;
    FString GetPlayerTypeString() const;
    FColor GetDebugColor() const;
    void DrawMovementVectors(const FVector& Location, const FVector& Velocity) const;
};