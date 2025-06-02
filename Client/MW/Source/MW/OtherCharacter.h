// OtherCharacter.h - MyCharacter 상속으로 원격 플레이어 구현
#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "OtherCharacter.generated.h"

UCLASS()
class MW_API AOtherCharacter : public AMyCharacter
{
    GENERATED_BODY()

public:
    AOtherCharacter();

    // 로컬 플레이어 여부 오버라이드 (항상 false)
    //virtual bool IsLocalPlayer() const override { return false; }
    //virtual bool IsRemoteControlled() const override { return true; }

    // 네트워크 업데이트 함수 오버라이드
    virtual void UpdateFromNetwork(const FTransform& NewTransform, const FVector& NetworkVelocity, EPlayerState NewState, EPlayerAction NewAction) override;

    // 다른 플레이어의 입력 정보 (시각화용 - 서버로부터 추정)
    float NetworkForwardInput = 0.0f;
    float NetworkRightInput = 0.0f;
    bool bNetworkRunPressed = false;
    bool bNetworkJumpPressed = false;
    bool bNetworkAttackPressed = false;
    bool bNetworkDefendPressed = false;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    // 원격 플레이어 전용 함수들
    void DisplayNetworkDebugInfo();

    // 네트워크 업데이트 추적
    float LastNetworkUpdateTime = 0.0f;
    float NetworkUpdateFrequency = 0.0f;

private:
    // 업데이트 빈도 계산용
    float LastUpdateTime = 0.0f;
    int32 UpdateCount = 0;

    // 원격 플레이어 초기화
    void InitializeAsRemotePlayer();

    // 헬퍼 함수들 (디버그용)
    FString GetPlayerStateString() const;
	FString GetPlayerActionString() const;
    FString GetMovementModeString() const;
    FColor GetNetworkStatusColor() const;
    FColor GetStateCircleColor() const;
	FColor GetActionCircleColor() const;
    void DrawNetworkStatusVisuals(const FVector& Location) const;
};