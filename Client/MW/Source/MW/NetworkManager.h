// NetworkManager.h - ������ ����
// �������� ����� �����ϴ� Ŭ����

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Networking.h"
#include "Common/TcpSocketBuilder.h"
#include "PacketTypes.h"
#include "NetworkManager.generated.h"

// ���� ���� ���� �� �˸��� �ޱ� ���� ��������Ʈ��
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, bIsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeft, int32, PlayerId);
// ��������Ʈ �̸� ���� (OnPlayerUpdated�� ����)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnPlayerUpdated, int32, PlayerId, FTransform, NewTransform, FVector, Velocity, EPlayerState, State, EPlayerAction, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionError);

// ĳ���� ���� ���� ��������Ʈ (���� Ȯ���)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayerJoinedWithModel, int32, PlayerId, int32, CharacterModelId, FTransform, SpawnTransform);

/**
 * ���� �ν��Ͻ� ����ý������� ������ ��Ʈ��ũ �Ŵ���
 * �������� ���� ��� �� ��Ŷ ó���� ���
 */
UCLASS()
class MW_API UNetworkManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // ===== UGameInstanceSubsystem �������̽� =====
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ===== ���� ���� ���� =====
    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void DisconnectFromServer();

    UFUNCTION(BlueprintPure, Category = "Network|Connection")
    bool IsConnected() const { return bIsConnected && Socket.IsValid() && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected; }

    // ===== ��Ŷ ���� �Լ��� =====
    void SendPlayerInitInfo(Vec3 Position, Rot3 Rotation);
    void SendPlayerInput(float ForwardValue, float RightValue,
        float RotationPitch, float RotationYaw, float RotationRoll,
        bool bRunPressed, bool bJumpPressed, bool bAttackPressed, bool bDefensePressed);
    void SendPing();

    // ���� Ȯ��� - ĳ���� ���� ����
    void SendCharacterSelection(int32 CharacterModelId, const FString& CharacterName = TEXT(""));

    int32 GetKnownPlayerCount() const { return KnownPlayerIds.Num(); }

    // ===== ��Ʈ��ũ ���� ���� =====
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

    // ===== ��Ʈ��ũ ��� =====
    UFUNCTION(BlueprintPure, Category = "Network|Stats")
    float GetNetworkUpdateRate() const { return NetworkUpdateRate; }

    UFUNCTION(BlueprintCallable, Category = "Network|Stats")
    void ResetNetworkStats();

public:
    // ===== ��������Ʈ�� =====
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

    // ���� Ȯ���
    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerJoinedWithModel OnPlayerJoinedWithModel;

private:
    // ===== �ٽ� ��Ʈ��ũ �Լ��� =====
    bool SendPacket(const void* Data, int32 Size);
    void ProcessReceivedData(const TArray<uint8>& Data, int32 BytesRead);
    void Update();

    // ===== ��Ŷ Ÿ�Ժ� ó�� �Լ��� =====
    void HandleClientIdPacket(const ClientIdPacket* Packet);
    void HandleOutputPacket(const OutputPacket* Packet);
	void HandleStatusPacket(const StatusPacket* Packet);
    void HandleDisconnectPacket(const DisconnectPacket* Packet);
    void HandlePongPacket(const PongPacket* Packet);

    // ===== ��Ʈ��ũ Ÿ�̹� �ݹ�� =====
    void OnNetworkTimerTick();
    void OnPingTimerTick();

    // ===== ���� �Լ��� =====
    bool ValidateConnection();
    bool ValidatePacketHeader(const PacketHeader* Header, int32 AvailableBytes);

private:
    // ===== ���� �� ���� ���� =====
    TSharedPtr<FInternetAddr> ServerAddress;
    TSharedPtr<FSocket> Socket;
    bool bIsConnected = false;
    int32 CurrentPlayerId = -1;
    TSet<int32> KnownPlayerIds;

    // ===== ���� ���� =====
    TArray<uint8> ReceiveBuffer;
    TArray<uint8> PacketProcessBuffer;

    // ===== Ÿ�̹� �ڵ�� =====
    FTimerHandle NetworkTimerHandle;
    FTimerHandle PingTimerHandle;

    // ===== ��/�� �ð� ���� =====
    uint64 LastPingSentTime = 0;
    uint64 LastPongReceivedTime = 0;
    float CurrentPingTime = 0.0f;

    // ===== ��Ʈ��ũ ��� =====
    int32 PacketsReceived = 0;
    int32 PacketsSent = 0;
    float LastStatsResetTime = 0.0f;

    // ===== ��Ʈ��ũ ���� =====
    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float NetworkUpdateRate = 100.0f; // 100Hz ��Ʈ��ũ ������Ʈ

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float PingInterval = 1.0f; // 1�ʸ��� �� ����

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float ConnectionTimeout = 30.0f; // 30�� ���� Ÿ�Ӿƿ�

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    uint32 MaxReceiveBufferSize = 65536; // 64KB �ִ� ���� ����

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    int32 MaxReconnectAttempts = 3; // �ִ� �翬�� �õ� Ƚ��

    // ===== ����� ���� =====
    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bEnableNetworkLogging = true;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bLogPacketDetails = true;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bEnableConnectionLogging = true;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bLogNetworkStats = false;

private:
	// ===== ��Ʈ��ũ ���� ���� =====
    void ConfigureSocket();
    void StartNetworkTimers();
    void ProcessPacketByType(PacketHeader* Header, int32 ProcessedBytes);

    // ===== ���� ���� ������ =====
    int32 ReconnectAttempts = 0;
    bool bIsReconnecting = false;
    float LastConnectionAttemptTime = 0.0f;

    // ===== ���� Ȯ��� ������ =====
    FString LastConnectedServerIP;
    int32 LastConnectedServerPort = 0;
};