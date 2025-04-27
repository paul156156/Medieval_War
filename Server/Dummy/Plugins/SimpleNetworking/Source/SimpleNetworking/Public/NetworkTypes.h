// NetworkTypes.h
#pragma once

#include "CoreMinimal.h"
#include "NetworkTypes.generated.h"

// 패킷 타입 정의 (서버와 동일하게 맞춰야 함)
UENUM(BlueprintType)
enum class EPacketType : uint8
{
    CLIENT_ID = 0,
    CONNECT = 1,
    DISCONNECT = 2,
    PING = 3,
    PONG = 4,
    POSITION_UPDATE = 5,
    INPUT = 6
};

// 상태 정의 (서버와 동일하게 맞춰야 함)
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    IDLE = 0,
    WALKING = 1,
    JUMPING = 2,
    ATTACKING =3
};

// 패킷 구조체 정의 (서버와 동일하게 맞춰야 함)
#pragma pack(push, 1)
struct FPacketHeader
{
    uint16 PacketSize;
    EPacketType PacketType;
};

struct FVec3
{
    float X, Y, Z;
};

struct FRot3
{
    float Pitch, Yaw, Roll;
};

struct FClientIdPacket
{
    FPacketHeader Header;
    int32 ClientId;
};

struct FConnectPacekt
{
    FPacketHeader Header;
    int32 ClientId;
};

struct FDisconnectPacket
{
	FPacketHeader Header;
	int32 ClientId;
};

struct FPingPacket
{
	FPacketHeader Header;
	int32 ClientId;
	float PingTime;
};

struct FInputPacket
{
    FPacketHeader Header;
    int32_t ClientId;
    float ForwardValue; // W/S
    float RightValue;   // A/D
    float ControlRotationYaw;   // 좌우 회전
    bool bJumpPressed;  // 스페이스바
    bool bAttackPressed; // 공격(왼쪽 마우스 클릭)
};

struct FPositionUpdatePacket
{
    FPacketHeader Header;
    int32 ClientId;
    FVec3 Position;
    FVec3 Velocity;
    EPlayerState State;
};

#pragma pack(pop)

// 다른 플레이어 정보 저장 구조체
USTRUCT(BlueprintType)
struct SIMPLENETWORKING_API FOtherPlayerInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    int32 ClientId = -1;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    EPlayerState State = EPlayerState::IDLE;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    FVector TargetPosition = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    float PositionInterpolationTime = 0.0f;
};

inline FString PlayerStateToString(EPlayerState State)
{
    switch (State)
    {
    case EPlayerState::IDLE: return TEXT("Idle");
    case EPlayerState::WALKING: return TEXT("Walking");
    case EPlayerState::JUMPING: return TEXT("Jumping");
    case EPlayerState::ATTACKING: return TEXT("Attacking");
    default: return TEXT("Unknown");
    }
}