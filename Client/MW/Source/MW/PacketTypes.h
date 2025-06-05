// PacketTypes.h
// ������ Ŭ���̾�Ʈ �� ��ſ� ���Ǵ� ��Ŷ ����ü ����

#pragma once

#include "CoreMinimal.h"
#include "PacketTypes.generated.h"

// ������ PacketTypes.h�� ������ ���� ����

// ��Ŷ Ÿ�� ����
UENUM(BlueprintType)
enum class EPacketType : uint8
{
    CLIENT_ID = 0,              // Ŭ���̾�Ʈ ID �Ҵ�
    CONNECT = 1,                // ���� ��û
    DISCONNECT = 2,             // ���� ���� ��û
    PING = 3,                   // �� �׽�Ʈ
    PONG = 4,                   // �� ����
    PLAYER_INIT_INFO = 5,       // �÷��̾� �ʱ� ����
    PLAYER_UPDATE_INFO = 6,   // ��ġ ������Ʈ (����->Ŭ���̾�Ʈ)
    PLAYER_INPUT_INFO = 7,       // �Է� ���� (Ŭ���̾�Ʈ->����)
	PLAYER_STATUS_INFO = 8,      // �÷��̾� ���� ���� (����->Ŭ���̾�Ʈ)
};

// �÷��̾� ���� ����
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    IDLE = 0,       // ���� ����
    WALKING = 1,    // �ȴ� ����
    RUNNING = 2,    // �ٴ� ����
    JUMPING = 3,    // ���� ����
	DEAD = 4,      // ��� ����
};

// �÷��̾� �ൿ ����
UENUM(BlueprintType)
enum class EPlayerAction : uint8
{
    NONE = 0,       // �ƹ� �ൿ�� ���� ����
    ATTACK = 1,     // ����
    DEFEND = 2     // ���
};

// �޸� ���� ���� (1����Ʈ ���� ����)
#pragma pack(push, 1)

// �⺻ ��Ŷ ���
struct PacketHeader
{
    uint16 PacketSize;      // ��Ŷ ��ü ũ��
    EPacketType PacketType; // ��Ŷ Ÿ��
};

// 3���� ���� (��ġ, �ӵ� ��)
struct Vec3
{
    float X, Y, Z;

    Vec3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    Vec3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

    // UE FVector�� ��ȯ
    Vec3(const FVector& Vector) : X(Vector.X), Y(Vector.Y), Z(Vector.Z) {}
    FVector ToFVector() const { return FVector(X, Y, Z); }
};

// 3���� ȸ����
struct Rot3
{
    float Pitch, Yaw, Roll;

    Rot3() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {}
    Rot3(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

    // UE FRotator�� ��ȯ
    Rot3(const FRotator& Rotator) : Pitch(Rotator.Pitch), Yaw(Rotator.Yaw), Roll(Rotator.Roll) {}
    FRotator ToFRotator() const { return FRotator(Pitch, Yaw, Roll); }
};

// Ŭ���̾�Ʈ ID ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct ClientIdPacket
{
    PacketHeader Header;
    int32 ClientId;         // �Ҵ�� Ŭ���̾�Ʈ ID
};

// ���� ��Ŷ
struct ConnectPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
};

// ���� ���� ��Ŷ
struct DisconnectPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
};

// �� ��Ŷ
struct PingPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
    uint64 PingTime;        // �� �ð� (������ ���� - uint64 ���)
};

// �� ��Ŷ
struct PongPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
    uint64 PingTime;        // �� �ð� (������ ���� - uint64 ���)
};

// �ʱ�ȭ ��Ŷ
struct InitPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
    Vec3 Position;          // �ʱ� ��ġ
    Rot3 Rotation;          // �ʱ� ȸ����
};

// �Է� ��Ŷ (Ŭ���̾�Ʈ -> ����) - ���� ������ ���� ����
struct InputPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
    float ForwardValue;     // ����/���� �Է°� (-1.0 ~ 1.0)
    float RightValue;       // ��/�� �Է°� (-1.0 ~ 1.0)
    float RotationPitch;    // ���� ȸ���� (-90.0 ~ 90.0) - ������ �̸� ����
    float RotationYaw;      // �¿� ȸ���� (-180.0 ~ 180.0) - ������ �̸� ����
    float RotationRoll;     // �� ȸ���� (-180.0 ~ 180.0) - ������ �̸� ����
    bool bRunPressed;       // �޸��� ��ư ���� ����
    bool bJumpPressed;      // ���� ��ư ���� ����
    bool bAttackPressed;    // ���� ��ư ���� ����
	bool bDefendPressed; // ��� ��ư ���� ����
};

// ��ġ ������Ʈ ��Ŷ (���� -> Ŭ���̾�Ʈ)
struct OutputPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
    Vec3 Position;          // ���� ��ġ
    Rot3 Rotation;          // ���� ȸ����
    Vec3 Velocity;          // ���� �ӵ�
    EPlayerState State;     // ���� �÷��̾� ����
	EPlayerAction Action; // ���� �÷��̾� �ൿ
};

struct StatusPacket
{
    PacketHeader Header;
    int32 ClientId;         // Ŭ���̾�Ʈ ID
	int32 HP;              // ���� ü��
};

// �޸� ���� ���� ����
#pragma pack(pop)

// ��Ŷ ���� �Լ��� (UE���� ����ϱ� ���� ���� �Լ���)
UCLASS()
class MW_API UPacketHelper : public UObject
{
    GENERATED_BODY()

public:
    // ��Ŷ ���� ���� �Լ���
    static InputPacket CreateInputPacket(int32 ClientId, float Forward, float Right,
        float Pitch, float Yaw, float Roll,
        bool bRun, bool bJump, bool bAttack, bool bDefend);

    static InitPacket CreateInitPacket(int32 ClientId, const FVector& Position, const FRotator& Rotation);

    static PingPacket CreatePingPacket(int32 ClientId);

    // ��Ŷ ���� �Լ���
    static bool IsValidPacketType(uint8 PacketType);
    static bool IsValidPlayerState(uint8 PlayerState);
	static bool IsValidPlayerAction(uint8 PlayerAction);
    static bool IsValidInputValue(float Value);
    static bool IsValidRotationValue(float Value);

    // UE Ÿ�� ��ȯ ����
    static FVector Vec3ToFVector(const Vec3& Vector);
    static Vec3 FVectorToVec3(const FVector& Vector);
    static FRotator Rot3ToFRotator(const Rot3& Rotation);
    static Rot3 FRotatorToRot3(const FRotator& Rotation);
};

// �������Ʈ���� ����� �� �ִ� ����ü�� (USTRUCT ����)
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