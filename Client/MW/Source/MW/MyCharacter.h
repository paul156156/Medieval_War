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

    // 입력 처리 함수들
    void NotifySpawn();
    void Move(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void StopRun(const FInputActionValue& Value);
    void StartJump(const FInputActionValue& Value);
    void StopJump(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Attack(const FInputActionValue& Value);

    // 네트워크 관련 함수들
    void SendInputToServer();
    void InterpolateRemoteMovement(float DeltaTime);

    // 디버그 정보 표시 함수 추가
    void DisplayDebugInfo();

    // 플레이어 ID 관리
    int32 PlayerId = -1;
    bool bIsLocalPlayer = false;

public:
    // 네트워크에서 업데이트 받기
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState);

    // 플레이어 ID 접근자
    void SetPlayerId(int32 Id) { PlayerId = Id; }
    int32 GetPlayerId() const { return PlayerId; }

    // 로컬 플레이어 여부
    void SetIsLocalPlayer(bool bLocal) { bIsLocalPlayer = bLocal; }
    bool IsLocalPlayer() const { return bIsLocalPlayer; }

    // 원격 제어 설정
    void SetIsRemoteControlled(bool bRemote) { bIsRemoteControlled = bRemote; }
    bool IsRemoteControlled() const { return bIsRemoteControlled; }

    // 입력 상태 (서버 전송용)
    float ForwardInput = 0.0f;
    float RightInput = 0.0f;
    float PitchInput = 0.0f;
    float YawInput = 0.0f;
    float RollInput = 0.0f;
    bool bRunPressed = false;
    bool bJumpPressed = false;
    bool bAttackPressed = false;

    // 입력이 변경되었는지 체크 (불필요한 전송 방지)
    float PreviousForwardInput = 0.0f;
    float PreviousRightInput = 0.0f;
    float PreviousPitchInput = 0.0f;
    float PreviousYawInput = 0.0f;
	float PreviousRollInput = 0.0f;
    bool bPreviousRunPressed = false;
    bool bPreviousJumpPressed = false;
    bool bPreviousAttackPressed = false;

    // 이동 방식 설정 옵션
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bAlwaysFaceMovementDirection = true;  // 항상 이동 방향을 향함

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bUseCameraRelativeMovement = true;    // 카메라 기준 이동

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementRotationRate = 500.0f;      // 회전 속도 조절

    // 플레이어 상태를 public으로 변경
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

protected:
    // 원격 제어 여부
    UPROPERTY(BlueprintReadOnly, Category = "Network")
    bool bIsRemoteControlled = false;

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

    // 카메라 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

    // 애니메이션
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    // 공격 타이밍
    FTimerHandle AttackResetHandle;

    // 보간 대상 (네트워크 동기화용)
    FVector TargetLocation = FVector::ZeroVector;
    FRotator TargetRotation = FRotator::ZeroRotator;
    FVector TargetVelocity = FVector::ZeroVector;
    bool bInitialPositionSet = false;

    // 보간 설정
    UPROPERTY(EditAnywhere, Category = "Network")
    float InterpSpeed = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Network")
    float VelocityInterpSpeed = 5.0f;

    // 네트워크 업데이트 빈도 제한
    float LastInputSendTime = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Network")
    float InputSendRate = 60.0f; // 초당 60회 전송

    // 디버그 표시 여부
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bShowDebugInfo = true;

private:
    // 입력 변경 감지
    bool HasInputChanged() const;
};