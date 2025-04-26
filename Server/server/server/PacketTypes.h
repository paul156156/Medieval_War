#pragma once
#include <cstdint>

// ��Ŷ Ÿ�� ���� (������� 0, 1, 2)
enum class EPacketType : uint8_t {
    CLIENT_ID = 0,       // Ŭ���̾�Ʈ ID �Ҵ�
    POSITION_UPDATE = 1, // ��ġ ������Ʈ
    INPUT = 2            // �Է� ����
};

// �÷��̾� ���� ����
enum class EPlayerState : uint8_t {
    IDLE = 0,       // ���� ����
    WALKING = 1,    // �ȴ� ����
    JUMPING = 2,    // ���� ����
    ATTACKING = 3   // ���� ����
};

// �޸� ���� ���� (1����Ʈ ���� ����)
#pragma pack(push, 1)

// �⺻ ��Ŷ ���
struct PacketHeader {
    uint16_t PacketSize;    // ��Ŷ ��ü ũ��
    EPacketType PacketType; // ��Ŷ Ÿ��
};

// 3���� ���� (��ġ, �ӵ� ��)
struct Vec3 {
    float X, Y, Z;
};

// 3���� ȸ����
struct Rot3 {
    float Pitch, Yaw, Roll;
};

// Ŭ���̾�Ʈ ID ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct ClientIdPacket {
    PacketHeader Header;  // ��Ŷ ���
    int32_t ClientId;     // �Ҵ�� Ŭ���̾�Ʈ ID
};

// �Է� ��Ŷ (Ŭ���̾�Ʈ -> ����)
struct InputPacket {
    PacketHeader Header;    // ��Ŷ ���
    int32_t ClientId;       // Ŭ���̾�Ʈ ID
    float ForwardValue;     // ����/���� �Է°� (-1.0 ~ 1.0)
    float RightValue;       // ��/�� �Է°� (-1.0 ~ 1.0)
    bool bJumpPressed;      // ���� ��ư ���� ����
    bool bAttackPressed;    // ���� ��ư ���� ����
};

// ��ġ ������Ʈ ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct PositionUpdatePacket {
    PacketHeader Header;    // ��Ŷ ���
    int32_t ClientId;       // Ŭ���̾�Ʈ ID
    Vec3 Position;          // ���� ��ġ
    Rot3 Rotation;          // ���� ȸ����
    Vec3 Velocity;          // ���� �ӵ�
    EPlayerState State;     // ���� �÷��̾� ����
};

// �޸� ���� ���� ����
#pragma pack(pop)