// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dummy_clientGameMode.generated.h"

class UNetworkManager;

UCLASS(minimalapi)
class Adummy_clientGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Adummy_clientGameMode();

    virtual void BeginPlay() override;

    // 네트워크 매니저 접근자
    UFUNCTION(BlueprintCallable, Category = "Networking")
    UNetworkManager* GetNetworkManager() const;

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
};