// NetworkPlayerComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetworkTypes.h"
#include "NetworkPlayerComponent.generated.h"

class USimpleNetworkManager;

UCLASS(ClassGroup=(Networking), meta=(BlueprintSpawnableComponent))
class SIMPLENETWORKING_API UNetworkPlayerComponent : public UActorComponent//, public ISimpleNetworkInterface
{
    GENERATED_BODY()

public:
    UNetworkPlayerComponent();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // 네트워크 매니저 참조
    UPROPERTY()
    USimpleNetworkManager* NetworkManager;

    // 네트워크 매니저 설정
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SetNetworkManager(USimpleNetworkManager* InNetworkManager);

    // 서버 연결 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    FString ServerIP;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    int32 ServerPort;
    
    // 자동 연결 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    bool bAutoConnectOnBeginPlay;
    
    // 네트워크 업데이트 활성화
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    bool bEnableNetworkUpdates;
    
    // 위치 전송 간격 (초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking", meta = (ClampMin = "0.01"))
    float PositionUpdateInterval;
    
    // 로컬 클라이언트 ID
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Networking")
    int32 LocalClientId;
    
    // 다른 플레이어 캐릭터 클래스
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Networking")
    TSubclassOf<AActor> OtherPlayerCharacterClass;
    
    // 다른 플레이어 캐릭터 맵
    UPROPERTY()
    TMap<AActor*, FOtherPlayerInfo> OtherPlayers;
    
    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    bool ConnectToServer();
    
    // 서버 연결 해제 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();
    
    // 위치 전송 함수
    void SendPositionToServer();
    
    // 점프 상태 전송 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendJumpState(bool bIsJumping);
    
    // 다른 플레이어 캐릭터 스폰
    UFUNCTION(BlueprintCallable, Category = "Networking")
    AActor* SpawnOtherPlayerCharacter(const FVector& Position, int32 InClientId = -1);
    
    // 다른 플레이어 캐릭터 제거
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void RemoveOtherPlayerCharacter(int32 ClientId);
    
    // 모든 다른 플레이어 제거
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void RemoveAllOtherPlayers();
    
    // 현재 클라이언트 ID 반환
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetLocalClientId() const { return LocalClientId; }
    
    // 다른 플레이어 캐릭터 개수 반환
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetOtherPlayerCount() const { return OtherPlayers.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void OnNetworkConnected();

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void OnNetworkDisconnected();

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping);

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void OnClientIdReceived(int32 ClientId);

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void OnOtherPlayerSpawned(AActor* OtherPlayerActor, int32 ClientId);

    UFUNCTION(BlueprintCallable, Category = "Networking")
    void OnOtherPlayerRemoved(int32 ClientId);

private:
    // 마지막 위치 전송 시간
    float LastPositionSentTime;
    
    // 타이머용 래퍼 함수 (void 반환)
    void ConnectToServerWrapper();

    // 네트워크 이벤트 핸들러 바인딩
    void BindNetworkEvents();
    
    // 네트워크 이벤트 핸들러 해제
    void UnbindNetworkEvents();
    
    // 다른 플레이어 캐릭터 업데이트
    void UpdateOtherPlayerCharacters(float DeltaTime);
    
    // 레거시 패킷 핸들러 (호환성 유지)
    UFUNCTION()
    void OnPositionUpdateReceived(const FVector& NewPosition);
    
    UFUNCTION()
    void OnRotationUpdateReceived(const FRotator& NewRotation);
    
    UFUNCTION()
    void OnJumpStateUpdateReceived(bool IsJumping);
    
    UFUNCTION()
    void OnConnectionStatusChanged(bool IsConnected);
};