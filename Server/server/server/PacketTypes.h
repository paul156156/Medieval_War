#pragma once
#include <cstdint>

// 패킷 타입
enum class EPacketType : uint8_t {
	CLIENT_ID,
	POSITION_UPDATE,
	MOVE,
	JUMP,
	ATTACK
};

// 플레이어 상태
enum class EPlayerState : uint8_t {
	IDLE,
	WALKING,
	JUMPING,
	ATTACKING
};

// 구조체 정의
#pragma pack(push, 1)
struct PacketHeader { uint16_t PacketSize; EPacketType PacketType; };
struct Vec3 { float X, Y, Z; };
struct Rot3 { float Pitch, Yaw, Roll; };

struct PositionUpdatePacket {
	PacketHeader Header;
	int32_t ClientId;
	Vec3 Position;
	Rot3 Rotation;
	Vec3 Velocity;
	EPlayerState State;
};

struct MovePacket {
	PacketHeader Header;
	float ForwardValue;
	float RightValue;
	Vec3 Position;
	Rot3 Rotation;
	Vec3 Velocity;
	EPlayerState State;
};

struct JumpPacket {
	PacketHeader Header;
	Vec3 Position;
	EPlayerState State;
};

struct AttackPacket {
	PacketHeader Header;
	Vec3 Position;
	EPlayerState State;
};

struct ClientIdPacket {
	PacketHeader Header;
	int32_t ClientId;
};
#pragma pack(pop)