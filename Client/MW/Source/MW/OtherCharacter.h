// OtherCharacter.h - 원격 플레이어 전용 캐릭터 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacketTypes.h"
#include "NetworkManager.h"
#include "OtherCharacter.generated.h"

UCLASS()
class MW_API AOtherCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AOtherCharacter();

    // 네트워크에서 업데이트 받기
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState);

    // 플레이어 ID 접근자
    void SetPlayerId(int32 Id) { PlayerId = Id; }
    int32 GetPlayerId() const { return PlayerId; }

    // 원격 제어 설정 (항상 true)
    void SetIsRemoteControlled(bool bRemote) { bIsRemoteControlled = bRemote; }
    bool IsRemoteControlled() const { return bIsRemoteControlled; }

    // 로컬 플레이어 여부 (항상 false)
    bool IsLocalPlayer() const { return false; }

    // 플레이어 상태 (읽기 전용)
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EPlayerState CurrentState = EPlayerState::IDLE;

    // 다른 플레이어의 입력 정보 (시각화용)
    float NetworkForwardInput = 0.0f;
    float NetworkRightInput = 0.0f;
    bool bNetworkRunPressed = false;
    bool bNetworkJumpPressed = false;
    bool bNetworkAttackPressed = false;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // 네트워크 관련 함수들
    void InterpolateRemoteMovement(float DeltaTime);
    void DisplayNetworkDebugInfo();

    // 플레이어 ID
    int32 PlayerId = -1;

    // 원격 제어 여부 (항상 true)
    UPROPERTY(BlueprintReadOnly, Category = "Network")
    bool bIsRemoteControlled = true;

    // 애니메이션
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere, Category = "Animation")
    float AttackMontageDuration = 1.0f;

    // 보간 대상 (네트워크 동기화용)
    FVector TargetLocation = FVector::ZeroVector;
    FRotator TargetRotation = FRotator::ZeroRotator;
    FVector TargetVelocity = FVector::ZeroVector;
    bool bInitialPositionSet = false;

    // 보간 설정
    UPROPERTY(EditAnywhere, Category = "Network")
    float InterpSpeed = 12.0f;  // 원격 플레이어는 조금 더 빠르게 보간

    UPROPERTY(EditAnywhere, Category = "Network")
    float VelocityInterpSpeed = 8.0f;

    // 디버그 표시 여부
    UPROPERTY(EditAnywhere, Category = "Debug")
    bool bShowDebugInfo = true;

    // 네트워크 업데이트 추적
    float LastNetworkUpdateTime = 0.0f;
    float NetworkUpdateFrequency = 0.0f;  // 업데이트 빈도 추적

private:
    // 업데이트 빈도 계산용
    float LastUpdateTime = 0.0f;
    int32 UpdateCount = 0;

    // 헬퍼 함수들
    FString GetPlayerStateString() const;
    FString GetMovementModeString() const;
    FColor GetDebugTextColor() const;
    FColor GetStateCircleColor() const;
    void DrawNetworkStatusVisuals(const FVector& Location) const;
};