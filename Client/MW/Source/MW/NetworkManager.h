// NetworkManager.h - 개선된 버전
// 서버와의 통신을 관리하는 클래스

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Networking.h"
#include "Common/TcpSocketBuilder.h"
#include "PacketTypes.h"
#include "NetworkManager.generated.h"

// 게임 상태 변경 시 알림을 받기 위한 델리게이트들
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, bIsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeft, int32, PlayerId);
// 델리게이트 이름 통일 (OnPlayerUpdated로 변경)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnPlayerUpdated, int32, PlayerId, FTransform, NewTransform, FVector, Velocity, EPlayerState, State, EPlayerAction, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionError);

// 캐릭터 선택 관련 델리게이트 (향후 확장용)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerJoinedWithModel, int32, PlayerId, int32, CharacterModelId, FTransform, SpawnTransform);

/**
 * 게임 인스턴스 서브시스템으로 구현된 네트워크 매니저
 * 서버와의 소켓 통신 및 패킷 처리를 담당
 */
UCLASS()
class MW_API UNetworkManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // ===== UGameInstanceSubsystem 인터페이스 =====
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ===== 서버 연결 관리 =====
    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void DisconnectFromServer();

    UFUNCTION(BlueprintPure, Category = "Network|Connection")
    bool IsConnected() const { return bIsConnected && Socket.IsValid() && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected; }

    // ===== 패킷 전송 함수들 =====
    void SendPlayerInitInfo(Vec3 Position, Rot3 Rotation);
    void SendPlayerInput(float ForwardValue, float RightValue,
        float RotationPitch, float RotationYaw, float RotationRoll,
        bool bRunPressed, bool bJumpPressed, bool bAttackPressed, bool bDefensePressed);
    void SendPing();

    // 향후 확장용 - 캐릭터 선택 전송
    void SendCharacterSelection(int32 CharacterModelId, const FString& CharacterName = TEXT(""));

    int32 GetKnownPlayerCount() const { return KnownPlayerIds.Num(); }

    // ===== 네트워크 상태 정보 =====
    UFUNCTION(BlueprintPure, Category = "Network|Status")
    int32 GetCurrentPlayerId() const { return CurrentPlayerId; }

    UFUNCTION(BlueprintPure, Category = "Network|Status")
    float GetPingTime() const { return CurrentPingTime; }

    UFUNCTION(BlueprintPure, Category = "Network|Status")
    float GetLastPongTime() const { return static_cast<float>(LastPongReceivedTime); }

    UFUNCTION(BlueprintPure, Category = "Network|Status")
    int32 GetPacketsReceived() const { return PacketsReceived; }

    UFUNCTION(BlueprintPure, Category = "Network|Status")
    int32 GetPacketsSent() const { return PacketsSent; }

    // ===== 네트워크 통계 =====
    UFUNCTION(BlueprintPure, Category = "Network|Stats")
    float GetNetworkUpdateRate() const { return NetworkUpdateRate; }

    UFUNCTION(BlueprintCallable, Category = "Network|Stats")
    void ResetNetworkStats();

public:
    // ===== 델리게이트들 =====
    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnConnectionStatusChanged OnConnectionStatusChanged;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerJoined OnPlayerJoined;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerLeft OnPlayerLeft;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerUpdated OnPlayerUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnConnectionError OnConnectionError;

    // 향후 확장용
    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerJoinedWithModel OnPlayerJoinedWithModel;

private:
    // ===== 핵심 네트워크 함수들 =====
    bool SendPacket(const void* Data, int32 Size);
    void ProcessReceivedData(const TArray<uint8>& Data, int32 BytesRead);
    void Update();

    // ===== 패킷 타입별 처리 함수들 =====
    void HandleClientIdPacket(const ClientIdPacket* Packet);
    void HandleOutputPacket(const OutputPacket* Packet);
	void HandleStatusPacket(const StatusPacket* Packet);
    void HandleDisconnectPacket(const DisconnectPacket* Packet);
    void HandlePongPacket(const PongPacket* Packet);

    // ===== 네트워크 타이밍 콜백들 =====
    void OnNetworkTimerTick();
    void OnPingTimerTick();

    // ===== 검증 함수들 =====
    bool ValidateConnection();
    bool ValidatePacketHeader(const PacketHeader* Header, int32 AvailableBytes);

private:
    // ===== 소켓 및 연결 관련 =====
    TSharedPtr<FInternetAddr> ServerAddress;
    TSharedPtr<FSocket> Socket;
    bool bIsConnected = false;
    int32 CurrentPlayerId = -1;
    TSet<int32> KnownPlayerIds;

    // ===== 버퍼 관리 =====
    TArray<uint8> ReceiveBuffer;
    TArray<uint8> PacketProcessBuffer;

    // ===== 타이밍 핸들들 =====
    FTimerHandle NetworkTimerHandle;
    FTimerHandle PingTimerHandle;

    // ===== 핑/퐁 시간 추적 =====
    uint64 LastPingSentTime = 0;
    uint64 LastPongReceivedTime = 0;
    float CurrentPingTime = 0.0f;

    // ===== 네트워크 통계 =====
    int32 PacketsReceived = 0;
    int32 PacketsSent = 0;
    float LastStatsResetTime = 0.0f;

    // ===== 네트워크 설정 =====
    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float NetworkUpdateRate = 100.0f; // 100Hz 네트워크 업데이트

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float PingInterval = 1.0f; // 1초마다 핑 전송

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float ConnectionTimeout = 30.0f; // 30초 연결 타임아웃

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    uint32 MaxReceiveBufferSize = 65536; // 64KB 최대 수신 버퍼

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    int32 MaxReconnectAttempts = 3; // 최대 재연결 시도 횟수

    // ===== 디버그 설정 =====
    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bEnableNetworkLogging = true;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bLogPacketDetails = true;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bEnableConnectionLogging = true;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bLogNetworkStats = false;

private:
	// ===== 네트워크 상태 관리 =====
    void ConfigureSocket();
    void StartNetworkTimers();
    void ProcessPacketByType(PacketHeader* Header, int32 ProcessedBytes);

    // ===== 내부 상태 변수들 =====
    int32 ReconnectAttempts = 0;
    bool bIsReconnecting = false;
    float LastConnectionAttemptTime = 0.0f;

    // ===== 향후 확장용 변수들 =====
    FString LastConnectedServerIP;
    int32 LastConnectedServerPort = 0;
};