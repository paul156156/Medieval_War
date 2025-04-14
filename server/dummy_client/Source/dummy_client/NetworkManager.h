#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "NetworkManager.generated.h"

// 패킷 타입 정의 (서버와 동일하게 맞춰야 함)
UENUM(BlueprintType)
enum class EPacketType : uint8
{
    MOVE = 0,
    JUMP = 1,
    POSITION_UPDATE = 2
};

// 패킷 구조체 정의 (서버와 동일하게 맞춰야 함)
#pragma pack(push, 1)
struct FPacketHeader
{
    uint16 PacketSize;
    EPacketType PacketType;
};

struct FMovePacket
{
    FPacketHeader Header;
    float ForwardValue;
    float RightValue;
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
};

struct FJumpPacket
{
    FPacketHeader Header;
    bool IsJumping;
    struct { float X, Y, Z; } Position;
};

struct FPositionUpdatePacket
{
    FPacketHeader Header;
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
    bool IsJumping;
};
#pragma pack(pop)

// 네트워크 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPositionUpdate, const FVector&, NewPosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationUpdate, const FRotator&, NewRotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpStateUpdate, bool, IsJumping);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, IsConnected);

UCLASS(BlueprintType, Blueprintable)
class DUMMY_CLIENT_API UNetworkManager : public UObject
{
    GENERATED_BODY()

public:
    UNetworkManager();
    virtual ~UNetworkManager();

    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    bool ConnectToServer(const FString& IPAddress, int32 Port);

    // 서버 연결 해제
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();

    // 이동 패킷 전송
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendMovePacket(float ForwardValue, float RightValue, const FVector& Position, const FRotator& Rotation);

    // 점프 패킷 전송
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendJumpPacket(bool IsJumping, const FVector& Position);

    // 패킷 수신 처리
    void ProcessIncomingPackets();

    // 서버 연결 상태
    UFUNCTION(BlueprintPure, Category = "Networking")
    bool IsConnected() const;

    // 마지막 에러 코드 반환
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetLastErrorCode() const { return LastErrorCode; }

    // 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPositionUpdate OnPositionUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnRotationUpdate OnRotationUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnJumpStateUpdate OnJumpStateUpdate;

    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnConnectionStatusChanged OnConnectionStatusChanged;

private:
    // 소켓 객체
    FSocket* Socket;

    // 서버 접속 정보
    FIPv4Endpoint ServerEndpoint;

    // 수신 버퍼
    uint8 RecvBuffer[1024];

    // 접속 여부
    bool bIsConnected;

    // 마지막 에러 코드
    int32 LastErrorCode;

    // 패킷 처리 함수
    void HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet);

    // 타이머 핸들 (패킷 수신용)
    FTimerHandle PacketReceiverTimerHandle;

    // 연결 상태 체크
    void CheckConnectionStatus();
};