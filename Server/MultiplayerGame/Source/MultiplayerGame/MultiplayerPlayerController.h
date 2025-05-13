// MultiplayerPlayerController.h
// �÷��̾� ��Ʈ�ѷ� Ŭ����

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerPlayerController.generated.h"

/**
 * �÷��̾� ��Ʈ�ѷ� Ŭ����
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

    // ���� ���� UI ǥ��
    UFUNCTION(BlueprintCallable, Category = "Network")
    void ShowConnectionUI();

    // UI �̺�Ʈ �ڵ鷯
    UFUNCTION(BlueprintCallable, Category = "Network")
    void OnConnectButtonClicked(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void OnDisconnectButtonClicked();

private:
    // ���� UI ����
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> ConnectionWidgetClass;

    UPROPERTY()
    class UUserWidget* ConnectionWidget;

    // ���� ��� ����
    UPROPERTY()
    class AMultiplayerGameMode* GameMode;

    // ESC Ű �Է� ó��
    void OnEscapePressed();
};