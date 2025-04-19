// ISimpleNetworkInterface.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISimpleNetworkInterface.generated.h"

// 인터페이스 클래스
UINTERFACE(MinimalAPI, Blueprintable)
class USimpleNetworkInterface : public UInterface
{
    GENERATED_BODY()
};

// 인터페이스 함수 정의
class SIMPLENETWORKING_API ISimpleNetworkInterface
{
    GENERATED_BODY()

public:
    // 네트워크 연결됨 이벤트
    UFUNCTION(BlueprintNativeEvent, Category = "Networking")
    void OnNetworkConnected();

    // 네트워크 연결 해제됨 이벤트
    UFUNCTION(BlueprintNativeEvent, Category = "Networking")
    void OnNetworkDisconnected();

    // 플레이어 업데이트 수신 이벤트
    UFUNCTION(BlueprintNativeEvent, Category = "Networking")
    void OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping);

    // 클라이언트 ID 수신 이벤트
    UFUNCTION(BlueprintNativeEvent, Category = "Networking")
    void OnClientIdReceived(int32 ClientId);

    // 다른 플레이어 생성 이벤트
    UFUNCTION(BlueprintNativeEvent, Category = "Networking")
    void OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId);

    // 다른 플레이어 제거 이벤트
    UFUNCTION(BlueprintNativeEvent, Category = "Networking")
    void OnOtherPlayerRemoved(int32 ClientId);
};