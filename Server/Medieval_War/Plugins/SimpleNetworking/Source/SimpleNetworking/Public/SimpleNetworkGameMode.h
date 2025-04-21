// SimpleNetworkGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleNetworkGameMode.generated.h"

class USimpleNetworkManager;
class UUserWidget;

UCLASS()
class SIMPLENETWORKING_API ASimpleNetworkGameMode : public AGameModeBase
{
    GENERATED_BODY()
    
public:
    ASimpleNetworkGameMode();
    
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
    // 네트워크 매니저 접근자
    UFUNCTION(BlueprintCallable, Category = "Networking")
    USimpleNetworkManager* GetNetworkManager() const;
    
    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void ConnectToServer();
    
    // 서버 연결 해제 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();
    
protected:
    // 네트워크 매니저 인스턴스
    UPROPERTY()
    USimpleNetworkManager* NetworkManager;
    
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
};