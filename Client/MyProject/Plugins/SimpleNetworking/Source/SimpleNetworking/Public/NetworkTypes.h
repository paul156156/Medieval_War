// NetworkTypes.h
#pragma once

#include "CoreMinimal.h"
#include "NetworkTypes.generated.h"

// 패킷 타입 정의 (서버와 동일하게 맞춰야 함)
UENUM(BlueprintType)
enum class EPacketType : uint8
{
	CLIENT_ID = 3,
    MOVE = 0,
    JUMP = 1,
    POSITION_UPDATE = 2,
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
};

struct FJumpPacket
{
    FPacketHeader Header;
    bool IsJumping;
    FVec3 Position;
    FVec3 Velocity;
};

struct FPositionUpdatePacket
{
    FPacketHeader Header;
    int32 ClientId;
    FVec3 Position;
    FRot3 Rotation;
    FVec3 Velocity;
    bool IsJumping;
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
    FVector TargetPosition = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    FRotator TargetRotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    float PositionInterpolationTime = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    float RotationInterpolationTime = 0.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Networking")
    bool IsJumping = false;
};