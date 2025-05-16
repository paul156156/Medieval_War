// MultiplayerHUD.h
// 게임 HUD 클래스

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MultiplayerHUD.generated.h"

/**
 * 게임 내 HUD를 관리하는 클래스
 */
UCLASS()
class MULTIPLAYERGAME_API AMultiplayerHUD : public AHUD
{
    GENERATED_BODY()

public:
    AMultiplayerHUD();

    virtual void BeginPlay() override;
    virtual void DrawHUD() override;
    virtual void Tick(float DeltaSeconds) override;

    // 연결 상태 텍스트 표시 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowConnectionStatus;

    // FPS 표시 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowFPS;

    // 플레이어 수 표시 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowPlayerCount;

    // 연결 상태 업데이트
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetConnectionStatus(bool bIsConnected);

    // 플레이어 수 업데이트
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdatePlayerCount(int32 Count);

    // 메시지 표시
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowMessage(const FString& Message, float Duration = 3.0f);

private:
    // 상태 변수
    bool bIsConnected;
    int32 PlayerCount;
    float FPS;

    // 메시지 관련 변수
    FString CurrentMessage;
    float MessageRemainingTime;
    bool bShowMessage;

    // FPS 계산 변수
    float LastFPSUpdateTime;
    int32 FrameCount;
};