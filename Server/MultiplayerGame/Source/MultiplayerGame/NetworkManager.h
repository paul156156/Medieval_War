// NetworkManager.h
// 서버와의 통신을 관리하는 클래스

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Networking.h"
#include "Common/TcpSocketBuilder.h"
#include "PacketTypes.h"
#include "NetworkManager.generated.h"

// 게임 상태 변경 시 알림을 받기 위한 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, bIsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeft, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerPositionUpdated, int32, PlayerId, FTransform, NewTransform);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStateChanged, int32, PlayerId, EPlayerState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionError);

/**
 * 게임 인스턴스 서브시스템으로 구현된 네트워크 매니저
 * 서버와의 소켓 통신 및 패킷 처리를 담당
 */
UCLASS()
class MULTIPLAYERGAME_API UNetworkManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // UGameInstanceSubsystem 인터페이스
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    // 서버 연결 종료 함수
    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();
    	
    // 서버에 플레이어 초기화 정보 전송 함수
    void SendPlayerInitInfo(Vec3 Position, Rot3 Rotation);

    void SendPlayerInput(float ForwardValue, float RightValue, float Pitch, float Yaw, float Roll, bool bRunPressed, bool bCrouchPressed, bool bJumpPressed, bool bAttackPressed);

    //// 플레이어 입력 전송 함수
    //void SendPlayerMovement(float ForwardValue, float RightValue, Rot3 Rotation);

    //void SendPlayerEvent(bool bRunPressed, bool bCrouchPressed, bool bJumpPressed, bool bAttackPressed);
    
    // 서버에서 받은 패킷 처리 함수
    void ProcessReceivedData(const TArray<uint8>& Data, int32 BytesRead);

    // 네트워크 업데이트 처리 함수
    void Update();

    // 현재 플레이어 ID 반환
    UFUNCTION(BlueprintPure, Category = "Network")
    int32 GetCurrentPlayerId() const { return CurrentPlayerId; }

    // 연결 상태 확인
    UFUNCTION(BlueprintPure, Category = "Network")
    bool IsConnected() const { return bIsConnected && Socket.IsValid() && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected; }

    // PING 전송 함수
    void SendPing();

public:
    // 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnConnectionStatusChanged OnConnectionStatusChanged;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerJoined OnPlayerJoined;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerLeft OnPlayerLeft;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerPositionUpdated OnPlayerPositionUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerStateChanged OnPlayerStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnConnectionError OnConnectionError;

private:
    // 패킷 전송 함수
    bool SendPacket(const void* Data, int32 Size);

    // 패킷 타입별 처리 함수
    void HandleClientIdPacket(const ClientIdPacket* Packet);
    void HandlePositionPacket(const PositionPacket* Packet);
    void HandleDisconnectPacket(const DisconnectPacket* Packet);
    void HandlePongPacket(const PongPacket* Packet);

    // 네트워크 타이머 델리게이트
    void OnNetworkTimerTick();
    void OnPingTimerTick();

private:
    // 소켓 및 연결 관련 변수
    TSharedPtr<FInternetAddr> ServerAddress;
    TSharedPtr<FSocket> Socket;
    //FSocket* Socket = nullptr;
    bool bIsConnected = false;
    int32 CurrentPlayerId = -1;

    // 수신 버퍼
    TArray<uint8> ReceiveBuffer;

    // 타이머 핸들
    FTimerHandle NetworkTimerHandle;
    FTimerHandle PingTimerHandle;

    // 마지막 핑/퐁 시간
    float LastPingSentTime = 0.0f;
    float LastPongReceivedTime = 0.0f;

    // 패킷 처리를 위한 임시 버퍼
    TArray<uint8> PacketProcessBuffer;
};