// PacketTypes.h
// 서버와 클라이언트 간 통신에 사용되는 패킷 구조체 정의

#pragma once

#include "CoreMinimal.h"
#include "PacketTypes.generated.h"

// 서버의 PacketTypes.h와 동일한 구조 유지

// 패킷 타입 정의
UENUM(BlueprintType)
enum class EPacketType : uint8
{
    CLIENT_ID = 0,              // 클라이언트 ID 할당
    CONNECT = 1,                // 연결 요청
    DISCONNECT = 2,             // 연결 해제 요청
    PING = 3,                   // 핑 테스트
    PONG = 4,                   // 핑 응답
    PLAYER_INIT_INFO = 5,       // 플레이어 초기 정보
    PLAYER_UPDATE_INFO = 6,   // 위치 업데이트 (서버->클라이언트)
    PLAYER_INPUT_INFO = 7,       // 입력 정보 (클라이언트->서버)
	PLAYER_STATUS_INFO = 8,      // 플레이어 상태 정보 (서버->클라이언트)
};

// 플레이어 상태 정의
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    IDLE = 0,       // 정지 상태
    WALKING = 1,    // 걷는 상태
    RUNNING = 2,    // 뛰는 상태
    JUMPING = 3,    // 점프 상태
	DEAD = 4,      // 사망 상태
};

// 플레이어 행동 정의
UENUM(BlueprintType)
enum class EPlayerAction : uint8
{
    NONE = 0,       // 아무 행동도 하지 않음
    ATTACK = 1,     // 공격
    DEFEND = 2     // 방어
};

// 메모리 정렬 설정 (1바이트 경계로 정렬)
#pragma pack(push, 1)

// 기본 패킷 헤더
struct PacketHeader
{
    uint16 PacketSize;      // 패킷 전체 크기
    EPacketType PacketType; // 패킷 타입
};

// 3차원 벡터 (위치, 속도 등)
struct Vec3
{
    float X, Y, Z;

    Vec3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    Vec3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

    // UE FVector와 변환
    Vec3(const FVector& Vector) : X(Vector.X), Y(Vector.Y), Z(Vector.Z) {}
    FVector ToFVector() const { return FVector(X, Y, Z); }
};

// 3차원 회전값
struct Rot3
{
    float Pitch, Yaw, Roll;

    Rot3() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {}
    Rot3(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

    // UE FRotator와 변환
    Rot3(const FRotator& Rotator) : Pitch(Rotator.Pitch), Yaw(Rotator.Yaw), Roll(Rotator.Roll) {}
    FRotator ToFRotator() const { return FRotator(Pitch, Yaw, Roll); }
};

// 클라이언트 ID 패킷 (서버 -> 클라이언트)
struct ClientIdPacket
{
    PacketHeader Header;
    int32 ClientId;         // 할당된 클라이언트 ID
};

// 연결 패킷
struct ConnectPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
};

// 연결 해제 패킷
struct DisconnectPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
};

// 핑 패킷
struct PingPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
    uint64 PingTime;        // 핑 시간 (서버와 맞춤 - uint64 사용)
};

// 퐁 패킷
struct PongPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
    uint64 PingTime;        // 핑 시간 (서버와 맞춤 - uint64 사용)
};

// 초기화 패킷
struct InitPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
    Vec3 Position;          // 초기 위치
    Rot3 Rotation;          // 초기 회전값
};

// 입력 패킷 (클라이언트 -> 서버) - 서버 구조와 완전 동일
struct InputPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
    float ForwardValue;     // 전진/후진 입력값 (-1.0 ~ 1.0)
    float RightValue;       // 좌/우 입력값 (-1.0 ~ 1.0)
    float RotationPitch;    // 상하 회전값 (-90.0 ~ 90.0) - 서버와 이름 맞춤
    float RotationYaw;      // 좌우 회전값 (-180.0 ~ 180.0) - 서버와 이름 맞춤
    float RotationRoll;     // 롤 회전값 (-180.0 ~ 180.0) - 서버와 이름 맞춤
    bool bRunPressed;       // 달리기 버튼 눌림 여부
    bool bJumpPressed;      // 점프 버튼 눌림 여부
    bool bAttackPressed;    // 공격 버튼 눌림 여부
	bool bDefendPressed; // 방어 버튼 눌림 여부
};

// 위치 업데이트 패킷 (서버 -> 클라이언트)
struct OutputPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
    Vec3 Position;          // 현재 위치
    Rot3 Rotation;          // 현재 회전값
    Vec3 Velocity;          // 현재 속도
    EPlayerState State;     // 현재 플레이어 상태
	EPlayerAction Action; // 현재 플레이어 행동
};

struct StatusPacket
{
    PacketHeader Header;
    int32 ClientId;         // 클라이언트 ID
	int32 HP;              // 현재 체력
};

// 메모리 정렬 설정 복원
#pragma pack(pop)

// 패킷 검증 함수들 (UE에서 사용하기 위한 헬퍼 함수들)
UCLASS()
class MW_API UPacketHelper : public UObject
{
    GENERATED_BODY()

public:
    // 패킷 생성 헬퍼 함수들
    static InputPacket CreateInputPacket(int32 ClientId, float Forward, float Right,
        float Pitch, float Yaw, float Roll,
        bool bRun, bool bJump, bool bAttack, bool bDefend);

    static InitPacket CreateInitPacket(int32 ClientId, const FVector& Position, const FRotator& Rotation);

    static PingPacket CreatePingPacket(int32 ClientId);

    // 패킷 검증 함수들
    static bool IsValidPacketType(uint8 PacketType);
    static bool IsValidPlayerState(uint8 PlayerState);
	static bool IsValidPlayerAction(uint8 PlayerAction);
    static bool IsValidInputValue(float Value);
    static bool IsValidRotationValue(float Value);

    // UE 타입 변환 헬퍼
    static FVector Vec3ToFVector(const Vec3& Vector);
    static Vec3 FVectorToVec3(const FVector& Vector);
    static FRotator Rot3ToFRotator(const Rot3& Rotation);
    static Rot3 FRotatorToRot3(const FRotator& Rotation);
};

// 블루프린트에서 사용할 수 있는 구조체들 (USTRUCT 버전)
USTRUCT(BlueprintType)
struct FNetworkPlayerState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    int32 ClientId = 0;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    FVector Position = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    FRotator Rotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    FVector Velocity = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    EPlayerState State = EPlayerState::IDLE;

	UPROPERTY(BlueprintReadWrite, Category = "Network")
	EPlayerAction Action = EPlayerAction::NONE;
};

USTRUCT(BlueprintType)
struct FNetworkInputState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    float ForwardValue = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    float RightValue = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    float RotationPitch = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    float RotationYaw = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    float RotationRoll = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    bool bRunPressed = false;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    bool bJumpPressed = false;

    UPROPERTY(BlueprintReadWrite, Category = "Network")
    bool bAttackPressed = false;

	UPROPERTY(BlueprintReadWrite, Category = "Network")
	bool bDefendPressed = false;
};