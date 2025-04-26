#pragma once
#include <cstdint>

// 패킷 타입 정의 (순서대로 0, 1, 2)
enum class EPacketType : uint8_t {
    CLIENT_ID = 0,       // 클라이언트 ID 할당
    POSITION_UPDATE = 1, // 위치 업데이트
    INPUT = 2            // 입력 정보
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

// 입력 패킷 (클라이언트 -> 서버)
struct InputPacket {
    PacketHeader Header;    // 패킷 헤더
    int32_t ClientId;       // 클라이언트 ID
    float ForwardValue;     // 전진/후진 입력값 (-1.0 ~ 1.0)
    float RightValue;       // 좌/우 입력값 (-1.0 ~ 1.0)
    bool bJumpPressed;      // 점프 버튼 눌림 여부
    bool bAttackPressed;    // 공격 버튼 눌림 여부
};

// 위치 업데이트 패킷 (서버 -> 클라이언트)
struct PositionUpdatePacket {
    PacketHeader Header;    // 패킷 헤더
    int32_t ClientId;       // 클라이언트 ID
    Vec3 Position;          // 현재 위치
    Rot3 Rotation;          // 현재 회전값
    Vec3 Velocity;          // 현재 속도
    EPlayerState State;     // 현재 플레이어 상태
};

// 메모리 정렬 설정 복원
#pragma pack(pop)