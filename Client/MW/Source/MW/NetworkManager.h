// NetworkManager.h
// �������� ����� �����ϴ� Ŭ����

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Networking.h"
#include "Common/TcpSocketBuilder.h"
#include "PacketTypes.h"
#include "NetworkManager.generated.h"

// ���� ���� ���� �� �˸��� �ޱ� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, bIsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeft, int32, PlayerId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnPlayerPositionUpdated, int32, PlayerId, FTransform, NewTransform, FVector, Velocity, EPlayerState, State, EPlayerAction, Action);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStateChanged, int32, PlayerId, EPlayerState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionError);

/**
 * ���� �ν��Ͻ� ����ý������� ������ ��Ʈ��ũ �Ŵ���
 * �������� ���� ��� �� ��Ŷ ó���� ���
 */
UCLASS()
class MW_API UNetworkManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // UGameInstanceSubsystem �������̽�
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Network")
    bool ConnectToServer(const FString& IpAddress, int32 Port);

    // ���� ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromServer();

    // ������ �÷��̾� �ʱ�ȭ ���� ���� �Լ�
    void SendPlayerInitInfo(Vec3 Position, Rot3 Rotation);

    // �÷��̾� �Է� ���� �Լ� (�� ���� ������ ����)
    void SendPlayerInput(float ForwardValue, float RightValue,
        float RotationPitch, float RotationYaw, float RotationRoll,
        bool bRunPressed, bool bJumpPressed, bool bAttackPressed, bool bDefensePressed);

    // �������� ���� ��Ŷ ó�� �Լ�
    void ProcessReceivedData(const TArray<uint8>& Data, int32 BytesRead);

    // ��Ʈ��ũ ������Ʈ ó�� �Լ�
    void Update();

    // ���� �÷��̾� ID ��ȯ
    UFUNCTION(BlueprintPure, Category = "Network")
    int32 GetCurrentPlayerId() const { return CurrentPlayerId; }

    // ���� ���� Ȯ��
    UFUNCTION(BlueprintPure, Category = "Network")
    bool IsConnected() const { return bIsConnected && Socket.IsValid() && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected; }

    // PING ���� �Լ�
    void SendPing();

    // ���� ���
    UFUNCTION(BlueprintPure, Category = "Network")
    float GetPingTime() const { return CurrentPingTime; }

    UFUNCTION(BlueprintPure, Category = "Network")
    float GetLastPongTime() const { return LastPongReceivedTime; }

public:
    // ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnConnectionStatusChanged OnConnectionStatusChanged;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerJoined OnPlayerJoined;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerLeft OnPlayerLeft;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnPlayerPositionUpdated OnPlayerUpdated;

    //UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    //FOnPlayerStateChanged OnPlayerStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Network|Events")
    FOnConnectionError OnConnectionError;

private:
    // ��Ŷ ���� �Լ�
    bool SendPacket(const void* Data, int32 Size);

    // ��Ŷ Ÿ�Ժ� ó�� �Լ�
    void HandleClientIdPacket(const ClientIdPacket* Packet);
    void HandleOutputPacket(const OutputPacket* Packet);
    void HandleDisconnectPacket(const DisconnectPacket* Packet);
    void HandlePongPacket(const PongPacket* Packet);

    // ��Ʈ��ũ Ÿ�̹� �ݹ�
    void OnNetworkTimerTick();
    void OnPingTimerTick();

    // ���� ���� ����
    bool ValidateConnection();

    // ��Ŷ ����
    bool ValidatePacketHeader(const PacketHeader* Header, int32 AvailableBytes);

private:
    // ���� �� ���� ���� ����
    TSharedPtr<FInternetAddr> ServerAddress;
    TSharedPtr<FSocket> Socket;
    bool bIsConnected = false;
    int32 CurrentPlayerId = -1;

    // ���� ����
    TArray<uint8> ReceiveBuffer;

    // Ÿ�̹� �ڵ�
    FTimerHandle NetworkTimerHandle;
    FTimerHandle PingTimerHandle;

    // ������ ��/�� �ð� (�� ���� uint64 Ÿ�Կ� ����)
    uint64 LastPingSentTime = 0;
    uint64 LastPongReceivedTime = 0;
    float CurrentPingTime = 0.0f;

    // ��Ŷ ó���� ���� �ӽ� ����
    TArray<uint8> PacketProcessBuffer;

    // ��Ʈ��ũ ���
    // ��Ʈ��ũ ����
    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float NetworkUpdateRate = 100.0f; // 100Hz ��Ʈ��ũ ������Ʈ

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float PingInterval = 1.0f; // 1�ʸ��� �� ����

    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    float ConnectionTimeout = 30.0f; // 30�� ���� Ÿ�Ӿƿ�

    // int32 ��� uint32�� �����Ͽ� Ÿ�� ��ġ��Ű��
    UPROPERTY(EditAnywhere, Category = "Network|Settings")
    uint32 MaxReceiveBufferSize = 65536; // 64KB �ִ� ���� ����

    // ����� ����
    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bEnableNetworkLogging = false;

    UPROPERTY(EditAnywhere, Category = "Network|Debug")
    bool bLogPacketDetails = false;
};