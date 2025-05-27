#pragma once
#include <cstdint>
#include <cmath>

// ��Ŷ Ÿ�� ����
enum class EPacketType : uint8_t {
    CLIENT_ID = 0,           // Ŭ���̾�Ʈ ID �Ҵ�
    CONNECT = 1,             // ���� ��û
    DISCONNECT = 2,          // ���� ���� ��û
    PING = 3,                // �� �׽�Ʈ
    PONG = 4,                // �� ����
    PLAYER_INIT_INFO = 5,    // �÷��̾� �ʱ� ����
    PLAYER_POSITION_INFO = 6,// ��ġ ������Ʈ
    PLAYER_INPUT_INFO = 7    // �Է� ����
};

// �÷��̾� ���� ����
enum class EPlayerState : uint8_t {
    IDLE = 0,       // ���� ����
    WALKING = 1,    // �ȴ� ����
    RUNNING = 2,    // �ٴ� ����
	//CROUCHING = 3,  // ��ũ���� ���� -> ������������Ƽ� �ּ� ó��
    JUMPING = 3,    // ���� ����
    ATTACKING = 4   // ���� ����
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

    Vec3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

// 3���� ȸ����
struct Rot3 {
    float Pitch, Yaw, Roll;

    Rot3() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {}
    Rot3(float pitch, float yaw, float roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}
};

// Ŭ���̾�Ʈ ID ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct ClientIdPacket {
    PacketHeader Header;
    int32_t ClientId;
};

// ���� ��Ŷ
struct ConnectPacket {
    PacketHeader Header;
    int32_t ClientId;
};

// ���� ���� ��Ŷ
struct DisconnectPacket {
    PacketHeader Header;
    int32_t ClientId;
};

// �� ��Ŷ
struct PingPacket {
    PacketHeader Header;
    int32_t ClientId;
    uint64_t PingTime;
};

// �� ��Ŷ
struct PongPacket {
    PacketHeader Header;
    int32_t ClientId;
    uint64_t PingTime;
};

// �ʱ�ȭ ��Ŷ
struct InitPacket {
    PacketHeader Header;
    int32_t ClientId;
    Vec3 Position;
    Rot3 Rotation;
};

// �Է� ��Ŷ (Ŭ���̾�Ʈ -> ����)
struct InputPacket {
    PacketHeader Header;
    int32_t ClientId;
    float ForwardValue;     // ����/���� �Է°� (-1.0 ~ 1.0)
    float RightValue;       // ��/�� �Է°� (-1.0 ~ 1.0)
    float RotationPitch;    // ���� ȸ���� (-90.0 ~ 90.0)
    float RotationYaw;      // �¿� ȸ���� (-180.0 ~ 180.0)
    float RotationRoll;     // �� ȸ���� (-180.0 ~ 180.0)
    bool bJumpPressed;      // ���� ��ư ���� ����
    bool bAttackPressed;    // ���� ��ư ���� ����
    //bool bCrouchPressed;    // ��ũ���� ��ư ���� ����
    bool bRunPressed;       // �޸��� ��ư ���� ����
};

// ��ġ ������Ʈ ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct PositionPacket {
    PacketHeader Header;
    int32_t ClientId;
    Vec3 Position;
    Rot3 Rotation;
    Vec3 Velocity;
    EPlayerState State;
};

// �޸� ���� ���� ����
#pragma pack(pop)

// ��Ŷ ���� �Լ���
inline bool IsValidPacketType(EPacketType type) {
    return static_cast<int>(type) >= 0 && static_cast<int>(type) <= 7;
}

inline bool IsValidPlayerState(EPlayerState state) {
    return static_cast<int>(state) >= 0 && static_cast<int>(state) <= 4;
}

inline bool IsValidInputValue(float value) {
    return value >= -1.0f && value <= 1.0f && !isnan(value) && isfinite(value);
}

inline bool IsValidRotationValue(float value) {
    return value >= -180.0f && value <= 180.0f && !isnan(value) && isfinite(value);
}

inline bool IsValidPacketHeader(const PacketHeader* header, size_t receivedSize) {
    if (!header) return false;
    if (receivedSize < sizeof(PacketHeader)) return false;
    if (header->PacketSize > receivedSize) return false;
    if (!IsValidPacketType(header->PacketType)) return false;
    return true;
}