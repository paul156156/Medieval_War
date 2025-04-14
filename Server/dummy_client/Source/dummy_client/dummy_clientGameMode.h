#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dummy_clientGameMode.generated.h"

class UNetworkManager;
class UUserWidget;

UCLASS(minimalapi)
class Adummy_clientGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    Adummy_clientGameMode();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // 네트워크 매니저 접근자
    UFUNCTION(BlueprintCallable, Category = "Networking")
    UNetworkManager* GetNetworkManager() const;

    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void ConnectToServer();

    // 서버 연결 해제 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // 서버 연결 성공 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnected();

    // 서버 연결 실패 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnectionFailed();

    // 서버 연결 해제 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerDisconnected();

protected:
    // 네트워크 매니저 인스턴스
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // 서버 IP 주소
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    FString ServerIP;

    // 서버 포트
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    int32 ServerPort;

    // 자동 연결 여부
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    bool bAutoConnect;

    // 연결 실패 시 자동 재연결 여부
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    bool bAutoReconnect;

    // 재연결 간격 (초)
    UPROPERTY(EditDefaultsOnly, Category = "Networking", meta = (EditCondition = "bAutoReconnect"))
    float ReconnectInterval;

    // 연결 상태 UI 위젯 클래스
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ConnectionStatusWidgetClass;

    // 연결 상태 UI 위젯 인스턴스
    UPROPERTY()
    UUserWidget* ConnectionStatusWidget;
};