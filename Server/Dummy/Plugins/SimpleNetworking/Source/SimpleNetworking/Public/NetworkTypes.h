// NetworkTypes.h
#pragma once

#include "CoreMinimal.h"
#include "NetworkTypes.generated.h"

// 패킷 타입 정의 (서버와 동일하게 맞춰야 함)
UENUM(BlueprintType)
enum class EPacketType : uint8
{
	CLIENT_ID = 0,
    POSITION_UPDATE = 1,
    MOVE = 2,
    JUMP = 3,
	ATTACK = 4,
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

struct FMovePacket
{
    FPacketHeader Header;
    float ForwardValue;
    float RightValue;
    FVec3 Position;
    FRot3 Rotation;
    FVec3 Velocity;
    EPlayerState State;
};

struct FJumpPacket
{
    FPacketHeader Header;
    FVec3 Position;
    EPlayerState State;
};

struct FAttackPacket
{
	FPacketHeader Header;
	FVec3 Position;
	EPlayerState State;
};

struct FPositionUpdatePacket
{
    FPacketHeader Header;
    int32 ClientId;
    FVec3 Position;
    FRot3 Rotation;
    FVec3 Velocity;
    EPlayerState State;
};

struct FClientIdPacket
{
    FPacketHeader Header;
    int32 ClientId;
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
    FRotator TargetRotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    float PositionInterpolationTime = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    float RotationInterpolationTime = 0.0f;
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