// MyHUD.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class MW_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    AMyHUD();

    virtual void BeginPlay() override;
    virtual void DrawHUD() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowConnectionStatus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowFPS;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowPlayerCount;

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetConnectionStatus(bool bIsConnected);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdatePlayerCount(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowMessage(const FString& Message, float Duration = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdatePlayerCountFromManager();

    // ?? 델리게이트 바인딩용 UFUNCTION 추가
    UFUNCTION()
    void OnConnectionStatusChanged(bool bConnected);

    UFUNCTION()
    void OnPlayerCountChanged(int32 ClientId);

private:
    bool bIsConnected;
    int32 PlayerCount;
    float FPS;

    FString CurrentMessage;
    float MessageRemainingTime;
    bool bShowMessage;

    float LastFPSUpdateTime;
    int32 FrameCount;
};
