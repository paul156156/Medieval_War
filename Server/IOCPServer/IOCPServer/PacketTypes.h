#pragma once
#include <cstdint>
#include <cmath>

// 패킷 타입 정의
enum class EPacketType : uint8_t {
    CLIENT_ID = 0,           // 클라이언트 ID 할당
    CONNECT = 1,             // 연결 요청
    DISCONNECT = 2,          // 연결 해제 요청
    PING = 3,                // 핑 테스트
    PONG = 4,                // 핑 응답
    PLAYER_INIT_INFO = 5,    // 플레이어 초기 정보
    PLAYER_UPDATE_INFO = 6,// 위치 업데이트
    PLAYER_INPUT_INFO = 7    // 입력 정보
};

// 플레이어 상태 정의
enum class EPlayerState : uint8_t {
    IDLE = 0,       // 정지 상태
    WALKING = 1,    // 걷는 상태
    RUNNING = 2,    // 뛰는 상태
    JUMPING = 3,    // 점프 상태
	DEAD = 4        // 사망 상태
};

// 플레이어 액션 정의
enum class EPlayerAction : uint8_t {
    NONE = 0,       // 아무 액션도 없음
    ATTACK = 1,     // 공격
    DEFEND = 2      // 방어
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

    Vec3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

// 3차원 회전값
struct Rot3 {
    float Pitch, Yaw, Roll;

    Rot3() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {}
    Rot3(float pitch, float yaw, float roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}
};

// 클라이언트 ID 패킷 (서버 -> 클라이언트)
struct ClientIdPacket {
    PacketHeader Header;
    int32_t ClientId;
};

// 연결 패킷
struct ConnectPacket {
    PacketHeader Header;
    int32_t ClientId;
};

// 연결 해제 패킷
struct DisconnectPacket {
    PacketHeader Header;
    int32_t ClientId;
};

// 핑 패킷
struct PingPacket {
    PacketHeader Header;
    int32_t ClientId;
    uint64_t PingTime;
};

// 퐁 패킷
struct PongPacket {
    PacketHeader Header;
    int32_t ClientId;
    uint64_t PingTime;
};

// 초기화 패킷
struct InitPacket {
    PacketHeader Header;
    int32_t ClientId;
    Vec3 Position;
    Rot3 Rotation;
};

// 입력 패킷 (클라이언트 -> 서버)
struct InputPacket {
    PacketHeader Header;
    int32_t ClientId;
    float ForwardValue;     // 전진/후진 입력값 (-1.0 ~ 1.0)
    float RightValue;       // 좌/우 입력값 (-1.0 ~ 1.0)
    float RotationPitch;    // 상하 회전값 (-90.0 ~ 90.0)
    float RotationYaw;      // 좌우 회전값 (-180.0 ~ 180.0)
    float RotationRoll;     // 롤 회전값 (-180.0 ~ 180.0)
    bool bRunPressed;       // 달리기 버튼 눌림 여부
    bool bJumpPressed;      // 점프 버튼 눌림 여부
    bool bAttackPressed;    // 공격 버튼 눌림 여부
	bool bDefendPressed;    // 방어 버튼 눌림 여부
};

// 위치 업데이트 패킷 (서버 -> 클라이언트)
struct OutputPacket {
    PacketHeader Header;
    int32_t ClientId;
    Vec3 Position;
    Rot3 Rotation;
    Vec3 Velocity;
    EPlayerState State;
	EPlayerAction Action;
};

// 메모리 정렬 설정 복원
#pragma pack(pop)

// 패킷 검증 함수들
inline bool IsValidPacketType(EPacketType type) {
    return static_cast<int>(type) >= 0 && static_cast<int>(type) <= 7;
}

inline bool IsValidPlayerState(EPlayerState state) {
    return static_cast<int>(state) >= 0 && static_cast<int>(state) <= 4;
}

inline bool IsValidPlayerAction(EPlayerAction action) {
    return static_cast<int>(action) >= 0 && static_cast<int>(action) <= 2;
}

inline bool IsValidInputValue(float value) {
    return value >= -1.0f && value <= 1.0f && !isnan(value) && isfinite(value);
}

inline bool IsValidRotationValue(float value) {
    //return value >= -180.0f && value <= 180.0f && !isnan(value) && isfinite(value);
    return value >= 0.0f && value <= 360.0f && !isnan(value) && isfinite(value);
}

inline bool IsValidPacketHeader(const PacketHeader* header, size_t receivedSize) {
    if (!header) return false;
    if (receivedSize < sizeof(PacketHeader)) return false;
    if (header->PacketSize > receivedSize) return false;
    if (!IsValidPacketType(header->PacketType)) return false;
    return true;
}