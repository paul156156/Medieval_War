// PacketHelper.cpp
#include "PacketTypes.h"

// 패킷 생성 헬퍼 함수들
InputPacket UPacketHelper::CreateInputPacket(int32 ClientId, float Forward, float Right,
    float Pitch, float Yaw, float Roll,
    bool bRun, bool bJump, bool bAttack, bool bDefense)
{
    InputPacket Packet;
    Packet.Header.PacketType = EPacketType::PLAYER_INPUT_INFO;
    Packet.Header.PacketSize = sizeof(InputPacket);
    Packet.ClientId = ClientId;
    Packet.ForwardValue = Forward;
    Packet.RightValue = Right;
    Packet.RotationPitch = Pitch;
    Packet.RotationYaw = Yaw;
    Packet.RotationRoll = Roll;
    Packet.bRunPressed = bRun;
    Packet.bJumpPressed = bJump;
    Packet.bAttackPressed = bAttack;
	Packet.bDefensePressed = bDefense;

    return Packet;
}

InitPacket UPacketHelper::CreateInitPacket(int32 ClientId, const FVector& Position, const FRotator& Rotation)
{
    InitPacket Packet;
    Packet.Header.PacketType = EPacketType::PLAYER_INIT_INFO;
    Packet.Header.PacketSize = sizeof(InitPacket);
    Packet.ClientId = ClientId;
    Packet.Position = FVectorToVec3(Position);
    Packet.Rotation = FRotatorToRot3(Rotation);

    return Packet;
}

PingPacket UPacketHelper::CreatePingPacket(int32 ClientId)
{
    PingPacket Packet;
    Packet.Header.PacketType = EPacketType::PING;
    Packet.Header.PacketSize = sizeof(PingPacket);
    Packet.ClientId = ClientId;
    Packet.PingTime = FPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());

    return Packet;
}

// 패킷 검증 함수들
bool UPacketHelper::IsValidPacketType(uint8 PacketType)
{
    return PacketType >= 0 && PacketType <= 7;
}

bool UPacketHelper::IsValidPlayerState(uint8 PlayerState)
{
    return PlayerState >= 0 && PlayerState <= 5;
}

bool UPacketHelper::IsValidInputValue(float Value)
{
    return Value >= -1.0f && Value <= 1.0f && FMath::IsFinite(Value);
}

bool UPacketHelper::IsValidRotationValue(float Value)
{
    return Value >= -180.0f && Value <= 180.0f && FMath::IsFinite(Value);
}

// UE 타입 변환 헬퍼
FVector UPacketHelper::Vec3ToFVector(const Vec3& Vector)
{
    return FVector(Vector.X, Vector.Y, Vector.Z);
}

Vec3 UPacketHelper::FVectorToVec3(const FVector& Vector)
{
    return Vec3(Vector.X, Vector.Y, Vector.Z);
}

FRotator UPacketHelper::Rot3ToFRotator(const Rot3& Rotation)
{
    return FRotator(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
}

Rot3 UPacketHelper::FRotatorToRot3(const FRotator& Rotation)
{
    return Rot3(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
}