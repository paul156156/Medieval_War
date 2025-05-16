// MultiplayerPlayerController.h
// 플레이어 컨트롤러 클래스

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerPlayerController.generated.h"

/**
 * 플레이어 컨트롤러 클래스
 */
UCLASS()
class MULTIPLAYERGAME_API AMultiplayerPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMultiplayerPlayerController();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupInputComponent() override;

    // 서버 연결 UI 표시
    UFUNCTION(BlueprintCallable, Category = "Network")
    void ShowConnectionUI();

    // UI 이벤트 핸들러
    UFUNCTION(BlueprintCallable, Category = "Network")
    void OnConnectButtonClicked(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void OnDisconnectButtonClicked();

private:
    // 연결 UI 위젯
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> ConnectionWidgetClass;

    UPROPERTY()
    class UUserWidget* ConnectionWidget;

    // 게임 모드 참조
    UPROPERTY()
    class AMultiplayerGameMode* GameMode;

    // ESC 키 입력 처리
    void OnEscapePressed();
};