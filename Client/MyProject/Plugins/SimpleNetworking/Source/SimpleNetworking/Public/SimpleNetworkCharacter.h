// SimpleNetworkCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NetworkTypes.h"
#include "ISimpleNetworkInterface.h"
#include "SimpleNetworkCharacter.generated.h"

class USimpleNetworkManager;

UCLASS()
class SIMPLENETWORKING_API ASimpleNetworkCharacter : public ACharacter, public ISimpleNetworkInterface
{
    GENERATED_BODY()
    
public:
    ASimpleNetworkCharacter();
    
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaTime) override;
    
    // 네트워크 매니저 참조
    UPROPERTY()
    USimpleNetworkManager* NetworkManager;
    
    // 네트워크 업데이트 활성화
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    bool bEnableNetworkUpdates;
    
    // 위치 전송 간격 (초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
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
    
    // 위치 전송 함수
    void SendPositionToServer();
    
    // 점프 함수 (오버라이드)
    virtual void Jump() override;
    virtual void StopJumping() override;
    
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
    
    // ISimpleNetworkInterface 구현
    void OnNetworkConnected_Implementation() override;
    void OnNetworkDisconnected_Implementation() override;
    void OnPlayerUpdateReceived_Implementation(int32 ClientId, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, bool IsJumping) override;
    void OnClientIdReceived_Implementation(int32 ClientId) override;
    void OnOtherPlayerSpawned_Implementation(AActor* OtherPlayerActor, int32 ClientId) override;
    void OnOtherPlayerRemoved_Implementation(int32 ClientId) override;
    
private:
    // 마지막 위치 전송 시간
    float LastPositionSentTime;
    
    // 네트워크 매니저 초기화
    void InitializeNetworkManager();
    
    // 네트워크 이벤트 핸들러 바인딩
    void BindNetworkEvents();
    
    // 네트워크 이벤트 핸들러 해제
    void UnbindNetworkEvents();
    
    // 다른 플레이어 캐릭터 업데이트
    void UpdateOtherPlayerCharacters(float DeltaTime);
    
    // 네트워크 이벤트 핸들러 (내부)
    UFUNCTION()
    void OnConnectionStatusChanged(bool IsConnected);
    
    // 다른 플레이어 캐릭터 스폰 내부 구현
    AActor* SpawnOtherPlayerCharacterInternal(const FVector& Position, int32 InClientId = -1);
};