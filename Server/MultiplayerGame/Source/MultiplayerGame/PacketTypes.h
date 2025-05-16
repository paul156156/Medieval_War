// PacketTypes.h
// ������ Ŭ���̾�Ʈ �� ��ſ� ���Ǵ� ��Ŷ ����ü ����

#pragma once

#include "CoreMinimal.h"
#include "PacketTypes.generated.h"

// ������ PacketTypes.h�� ������ ���� ����

// ��Ŷ Ÿ�� ����
UENUM(BlueprintType)
enum class EPacketType : uint8
{
    CLIENT_ID = 0,          // Ŭ���̾�Ʈ ID �Ҵ�
    CONNECT = 1,            // ���� ��û
    DISCONNECT = 2,         // ���� ���� ��û
    PING = 3,               // �� �׽�Ʈ
    PONG = 4,               // �� ����
    PLAYER_INIT_INFO = 5,   // �÷��̾� �ʱ� ����
    PLAYER_POSITION_INFO = 6, // ��ġ ������Ʈ
    PLAYER_INPUT_INFO = 7   // �Է� ����
};

// �÷��̾� ���� ����
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    IDLE = 0,       // ���� ����
    WALKING = 1,    // �ȴ� ����
    JUMPING = 2,    // ���� ����
    ATTACKING = 3   // ���� ����
};

// �޸� ���� ���� (1����Ʈ ���� ����)
#pragma pack(push, 1)

// �⺻ ��Ŷ ���
struct PacketHeader
{
    uint16 PacketSize;    // ��Ŷ ��ü ũ��
    EPacketType PacketType; // ��Ŷ Ÿ��
};

// 3���� ���� (��ġ, �ӵ� ��)
struct Vec3
{
    float X, Y, Z;
};

// 3���� ȸ����
struct Rot3
{
    float Pitch, Yaw, Roll;
};

// Ŭ���̾�Ʈ ID ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct ClientIdPacket
{
    PacketHeader Header;  // ��Ŷ ���
    int32 ClientId;     // �Ҵ�� Ŭ���̾�Ʈ ID
};

// ���� ��Ŷ
struct ConnectPacket
{
    PacketHeader Header;  // ��Ŷ ���
    int32 ClientId;     // Ŭ���̾�Ʈ ID
};

// ���� ���� ��Ŷ
struct DisconnectPacket
{
    PacketHeader Header;  // ��Ŷ ���
    int32 ClientId;     // Ŭ���̾�Ʈ ID
};

// �� ��Ŷ
struct PingPacket
{
    PacketHeader Header;    // ��Ŷ ���
    int32 ClientId;       // Ŭ���̾�Ʈ ID
    float PingTime;         // �� �ð�
};

// �� ��Ŷ
struct PongPacket
{
    PacketHeader Header;    // ��Ŷ ���
    int32 ClientId;       // Ŭ���̾�Ʈ ID
    float PingTime;         // �� �ð�
};

// �Է� ��Ŷ (Ŭ���̾�Ʈ -> ����)
struct InputPacket
{
    PacketHeader Header;    // ��Ŷ ���
    int32 ClientId;       // Ŭ���̾�Ʈ ID
    float ForwardValue;     // ����/���� �Է°� (-1.0 ~ 1.0)
    float RightValue;       // ��/�� �Է°� (-1.0 ~ 1.0)
    float ControlRotationYaw; // ȸ���� (-180.0 ~ 180.0)
    float ControlRotationPitch; // ȸ���� (-180.0 ~ 180.0)
    bool bJumpPressed;      // ���� ��ư ���� ����
    bool bAttackPressed;    // ���� ��ư ���� ����
	bool bCrouchPressed;   // �ޱ׸��� ��ư ���� ����
};

// ��ġ ������Ʈ ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct PositionPacket
{
    PacketHeader Header;    // ��Ŷ ���
    int32 ClientId;       // Ŭ���̾�Ʈ ID
    Vec3 Position;          // ���� ��ġ
    Rot3 Rotation;          // ���� ȸ����
    Vec3 Velocity;          // ���� �ӵ�
    EPlayerState State;     // ���� �÷��̾� ����
};

// �޸� ���� ���� ����
#pragma pack(pop)