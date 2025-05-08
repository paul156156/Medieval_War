#pragma once
#include <cstdint>

// 패킷 타입 정의 (순서대로 0, 1, 2)
enum class EPacketType : uint8_t {
    CLIENT_ID =0,       // 클라이언트 ID 할당
	CONNECT = 1,        // 연결 요청
	DISCONNECT = 2,     // 연결 해제 요청
	PING = 3,           // 핑 테스트
	PONG = 4,           // 핑 응답
	PLAYER_INIT_INFO = 5,    // 플레이어 정보
    PLAYER_POSITION_INFO = 6,// 위치 업데이트
    PLAYER_INPUT_INFO = 7           // 입력 정보
};

// 플레이어 상태 정의
enum class EPlayerState : uint8_t {
    IDLE = 0,       // 정지 상태
    WALKING = 1,    // 걷는 상태
    JUMPING = 2,    // 점프 상태
    ATTACKING = 3   // 공격 상태
};

// 메모리 정렬 설정 (1바이트 경계로 정렬)
#pragma pack(push, 1)

// 기본 패킷 헤더
struct PacketHeader {
    uint16_t PacketSize;    // 패킷 전체 크기
    EPacketType PacketType; // 패킷 타입
};

// 3차원 벡터 (위치, 속도 등)
struct Vec3 {
    float X, Y, Z;
};

// 3차원 회전값
struct Rot3 {
    float Pitch, Yaw, Roll;
};

// 클라이언트 ID 패킷 (서버 -> 클라이언트)
struct ClientIdPacket {
    PacketHeader Header;  // 패킷 헤더
    int32_t ClientId;     // 할당된 클라이언트 ID
};

struct ConnectPacket {
	PacketHeader Header;  // 패킷 헤더
	int32_t ClientId;     // 클라이언트 ID
};

struct DisconnectPacket {
	PacketHeader Header;  // 패킷 헤더
	int32_t ClientId;     // 클라이언트 ID
};

struct PingPacket {
	PacketHeader Header;    // 패킷 헤더
	int32_t ClientId;       // 클라이언트 ID
	float PingTime;         // 핑 시간
};

struct PongPacket {
	PacketHeader Header;    // 패킷 헤더
	int32_t ClientId;       // 클라이언트 ID
	float PingTime;         // 핑 시간
};

// 입력 패킷 (클라이언트 -> 서버)
struct InputPacket {
    PacketHeader Header;    // 패킷 헤더
    int32_t ClientId;       // 클라이언트 ID
    float ForwardValue;     // 전진/후진 입력값 (-1.0 ~ 1.0)
    float RightValue;       // 좌/우 입력값 (-1.0 ~ 1.0)
	float ControlRotationYaw; // 회전값 (-180.0 ~ 180.0)
    float ControlRotationPitch; // 회전값 (-180.0 ~ 180.0)
    bool bJumpPressed;      // 점프 버튼 눌림 여부
    bool bAttackPressed;    // 공격 버튼 눌림 여부
};

// 위치 업데이트 패킷 (서버 -> 클라이언트)
struct PositionPacket {
    PacketHeader Header;    // 패킷 헤더
    int32_t ClientId;       // 클라이언트 ID
    Vec3 Position;          // 현재 위치
	Rot3 Rotation;          // 현재 회전값
    Vec3 Velocity;          // 현재 속도
    EPlayerState State;     // 현재 플레이어 상태
};

// 메모리 정렬 설정 복원
#pragma pack(pop)