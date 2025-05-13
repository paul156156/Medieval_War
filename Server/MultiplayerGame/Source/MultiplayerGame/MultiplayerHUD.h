// MultiplayerHUD.h
// ���� HUD Ŭ����

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MultiplayerHUD.generated.h"

/**
 * ���� �� HUD�� �����ϴ� Ŭ����
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

    // ���� ���� �ؽ�Ʈ ǥ�� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowConnectionStatus;

    // FPS ǥ�� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowFPS;

    // �÷��̾� �� ǥ�� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    bool bShowPlayerCount;

    // ���� ���� ������Ʈ
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetConnectionStatus(bool bIsConnected);

    // �÷��̾� �� ������Ʈ
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdatePlayerCount(int32 Count);

    // �޽��� ǥ��
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowMessage(const FString& Message, float Duration = 3.0f);

private:
    // ���� ����
    bool bIsConnected;
    int32 PlayerCount;
    float FPS;

    // �޽��� ���� ����
    FString CurrentMessage;
    float MessageRemainingTime;
    bool bShowMessage;

    // FPS ��� ����
    float LastFPSUpdateTime;
    int32 FrameCount;
};