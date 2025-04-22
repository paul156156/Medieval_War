// MyNetworkGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleNetworking/Public/NetworkTypes.h"
#include "MyNetworkGameMode.generated.h"

class USimpleNetworkManager;
class AMyCharacter;
class AOtherCharacter;

UCLASS()
class MEDIEVAL_WAR_API AMyNetworkGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyNetworkGameMode();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // 플레이어 상태 변경 처리
    UFUNCTION()
    void OnCharacterStateChanged(EPlayerState NewState, const FVector& Position, const FRotator& Rotation);

    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void ConnectToServer();

    // 서버 연결 해제 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // 네트워크 이벤트 (블루프린트에서 오버라이드 가능)
    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnected();

    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerDisconnected();

    UFUNCTION(BlueprintImplementableEvent, Category = "Networking")
    void OnServerConnectionFailed();

protected:
    // 네트워크 매니저
    UPROPERTY()
    USimpleNetworkManager* NetworkManager;

    // 서버 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    FString ServerIP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    int32 ServerPort;

    // 자동 연결 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    bool bAutoConnect;

    // 다른 플레이어 캐릭터 클래스
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Networking")
    TSubclassOf<AOtherCharacter> OtherPlayerCharacterClass;

    // 로컬 클라이언트 ID
    int32 LocalClientId;

    // 다른 플레이어 캐릭터 맵
    //TMap<int32, AOtherCharacter*> OtherPlayers;

    // 네트워크 이벤트 핸들러
    UFUNCTION()
    void OnPlayerUpdateReceived(int32 ClientId, const FVector& Position, const FRotator& Rotation, EPlayerState State);

    UFUNCTION()
    void OnClientIdReceived(int32 ClientId);

    UFUNCTION()
    void OnConnectionStatusChanged(bool IsConnected);

    // 다른 플레이어 생성/제거 함수
    //AOtherCharacter* SpawnOtherPlayerCharacter(int32 ClientId, const FVector& Position);
    //void RemoveOtherPlayerCharacter(int32 ClientId);
    //void RemoveAllOtherPlayers();
};