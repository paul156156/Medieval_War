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

    // ��Ʈ��ũ �Ŵ��� ������
    UFUNCTION(BlueprintCallable, Category = "Networking")
    UNetworkManager* GetNetworkManager() const;

protected:
    // ��Ʈ��ũ �Ŵ��� �ν��Ͻ�
    UPROPERTY()
    UNetworkManager* NetworkManager;

    // ���� IP �ּ�
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    FString ServerIP;

    // ���� ��Ʈ
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    int32 ServerPort;

    // �ڵ� ���� ����
    UPROPERTY(EditDefaultsOnly, Category = "Networking")
    bool bAutoConnect;
};