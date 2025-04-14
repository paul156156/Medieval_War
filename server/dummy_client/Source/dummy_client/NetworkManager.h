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
    POSITION_UPDATE = 2
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
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
    bool IsJumping;
};
#pragma pack(pop)

// ��ġ ������Ʈ ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPositionUpdate, const FVector&, NewPosition);

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

    // ��ġ ������Ʈ ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPositionUpdate OnPositionUpdate;

private:
    // ���� ��ü
    FSocket* Socket;

    // ���� ���� ����
    FIPv4Endpoint ServerEndpoint;

    // ���� ����
    uint8 RecvBuffer[1024];

    // ���� ����
    bool bIsConnected;

    // ��Ŷ ó�� �Լ�
    void HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet);

    // Ÿ�̸� �ڵ� (��Ŷ ���ſ�)
    FTimerHandle PacketReceiverTimerHandle;
};