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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerPositionUpdated, int32, PlayerId, FTransform, NewTransform);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStateChanged, int32, PlayerId, EPlayerState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnectionError);

/**
 * ���� �ν��Ͻ� ����ý������� ������ ��Ʈ��ũ �Ŵ���
 * �������� ���� ��� �� ��Ŷ ó���� ���
 */
UCLASS()
class MULTIPLAYERGAME_API UNetworkManager : public UGameInstanceSubsystem
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

    void SendPlayerInput(float ForwardValue, float RightValue, float Pitch, float Yaw, float Roll, bool bRunPressed, bool bCrouchPressed, bool bJumpPressed, bool bAttackPressed);

    //// �÷��̾� �Է� ���� �Լ�
    //void SendPlayerMovement(float ForwardValue, float RightValue, Rot3 Rotation);

    //void SendPlayerEvent(bool bRunPressed, bool bCrouchPressed, bool bJumpPressed, bool bAttackPressed);
    
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

public:
    // ��������Ʈ
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
    // ��Ŷ ���� �Լ�
    bool SendPacket(const void* Data, int32 Size);

    // ��Ŷ Ÿ�Ժ� ó�� �Լ�
    void HandleClientIdPacket(const ClientIdPacket* Packet);
    void HandlePositionPacket(const PositionPacket* Packet);
    void HandleDisconnectPacket(const DisconnectPacket* Packet);
    void HandlePongPacket(const PongPacket* Packet);

    // ��Ʈ��ũ Ÿ�̸� ��������Ʈ
    void OnNetworkTimerTick();
    void OnPingTimerTick();

private:
    // ���� �� ���� ���� ����
    TSharedPtr<FInternetAddr> ServerAddress;
    TSharedPtr<FSocket> Socket;
    //FSocket* Socket = nullptr;
    bool bIsConnected = false;
    int32 CurrentPlayerId = -1;

    // ���� ����
    TArray<uint8> ReceiveBuffer;

    // Ÿ�̸� �ڵ�
    FTimerHandle NetworkTimerHandle;
    FTimerHandle PingTimerHandle;

    // ������ ��/�� �ð�
    float LastPingSentTime = 0.0f;
    float LastPongReceivedTime = 0.0f;

    // ��Ŷ ó���� ���� �ӽ� ����
    TArray<uint8> PacketProcessBuffer;
};