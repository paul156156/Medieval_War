#pragma once

#include "CoreMinimal.h"
#include "SimpleNetworking/Public/SimpleNetworkCharacter.h"
#include "MyNetworkCharacter.generated.h"

/**
 * 네트워크 기능이 추가된 캐릭터 클래스
 */
class UNetworkPlayerComponent;

UCLASS()
class MEDIEVAL_WAR_API AMyNetworkCharacter : public ASimpleNetworkCharacter
{
    GENERATED_BODY()

public:
    // 생성자
    AMyNetworkCharacter();

    // 기본 메서드 오버라이드
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaTime) override;

    // 네트워크 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Networking")
    class UNetworkPlayerComponent* NetworkComponent;

    // 서버 연결
    UFUNCTION(BlueprintCallable, Category = "Networking")
    bool ConnectToServer();

    // 서버 연결 해제
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // 네트워크 이벤트 함수 오버라이드
    virtual void OnNetworkConnected() override;
    virtual void OnNetworkDisconnected() override;

	// 위치 전송 함수
	void SendPositionToServer();

    // 마지막 점프 상태
    bool LastJumpState;
};