#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "NetworkManager.generated.h"

// ��Ŷ Ÿ�� ���� (������ �����ϰ� ����� ��)
UENUM(BlueprintType)
enum class EPacketType : uint8
{
    MOVE = 0,
    JUMP = 1,
    POSITION_UPDATE = 2,
    CLIENT_ID = 3  // Ŭ���̾�Ʈ ID �Ҵ��� ���� ��Ŷ Ÿ�� �߰�
};

// ��Ŷ ����ü ���� (������ �����ϰ� ����� ��)
#pragma pack(push, 1)
struct FPacketHeader
{
    uint16 PacketSize;
    EPacketType PacketType;
};

struct FMovePacket
{
    FPacketHeader Header;
    float ForwardValue;
    float RightValue;
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
};

struct FJumpPacket
{
    FPacketHeader Header;
    bool IsJumping;
    struct { float X, Y, Z; } Position;
};

struct FPositionUpdatePacket
{
    FPacketHeader Header;
    int32 ClientId;  // Ŭ���̾�Ʈ ID �߰�
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
    bool IsJumping;
};

struct FClientIdPacket
{
    FPacketHeader Header;
    int32 ClientId;
};
#pragma pack(pop)

// ��Ʈ��ũ ��������Ʈ ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPositionUpdate, const FVector&, NewPosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationUpdate, const FRotator&, NewRotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpStateUpdate, bool, IsJumping);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, IsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnPlayerUpdate, int32, ClientId, const FVector&, Position, const FRotator&, Rotation, bool, IsJumping);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClientIdReceived, int32, ClientId);

UCLASS(BlueprintType, Blueprintable)
class DUMMY_CLIENT_API UNetworkManager : public UObject
{
    GENERATED_BODY()
public:
    UNetworkManager();
    virtual ~UNetworkManager();

    // ���� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Networking")
    bool ConnectToServer(const FString& IPAddress, int32 Port);

    // ���� ���� ����
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // �̵� ��Ŷ ����
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendMovePacket(float ForwardValue, float RightValue, const FVector& Position, const FRotator& Rotation);

    // ���� ��Ŷ ����
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendJumpPacket(bool IsJumping, const FVector& Position);

    // ��Ŷ ���� ó��
    void ProcessIncomingPackets();

    // ���� ���� ����
    UFUNCTION(BlueprintPure, Category = "Networking")
    bool IsConnected() const;

    // ������ ���� �ڵ� ��ȯ
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetLastErrorCode() const { return LastErrorCode; }

    // Ŭ���̾�Ʈ ID ��������
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetClientId() const { return LocalClientId; }

    // ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPositionUpdate OnPositionUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnRotationUpdate OnRotationUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnJumpStateUpdate OnJumpStateUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnConnectionStatusChanged OnConnectionStatusChanged;

    // ���� �÷��̾� ������Ʈ ��������Ʈ (��ġ, ȸ��, ���� ���¸� �� ���� ó��)
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPlayerUpdate OnPlayerUpdate;

    // Ŭ���̾�Ʈ ID ���� ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnClientIdReceived OnClientIdReceived;

private:
    // ���� ��ü
    FSocket* Socket;

    // ���� ���� ����
    FIPv4Endpoint ServerEndpoint;

    // ���� ����
    uint8 RecvBuffer[1024];

    // ���� ����
    bool bIsConnected;

    // ������ ���� �ڵ�
    int32 LastErrorCode;

    // ���� Ŭ���̾�Ʈ ID (�������� �Ҵ���� ID)
    int32 LocalClientId;

    // ��Ŷ ó�� �Լ�
    void HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet);
    void HandleClientIdPacket(const FClientIdPacket* Packet);

    // Ÿ�̸� �ڵ� (��Ŷ ���ſ�)
    FTimerHandle PacketReceiverTimerHandle;

    // ���� ���� üũ
    void CheckConnectionStatus();
};