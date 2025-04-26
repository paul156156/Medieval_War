// SimpleNetworkManager.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NetworkTypes.h"
#include "Sockets.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "SimpleNetworkManager.generated.h"

// 델리게이트 정의
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPositionUpdate, const FVector&, NewPosition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationUpdate, const FRotator&, NewRotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, bool, IsConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnPlayerUpdate, int32, ClientId, const FVector&, Position, const FRotator&, Rotation, const FVector&, Velocity, EPlayerState, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClientIdReceived, int32, ClientId);

UCLASS(BlueprintType, Blueprintable)
class SIMPLENETWORKING_API USimpleNetworkManager : public UObject
{
    GENERATED_BODY()

public:
    USimpleNetworkManager();
    virtual ~USimpleNetworkManager();

    // 서버 연결 함수
    UFUNCTION(BlueprintCallable, Category = "Networking")
    bool ConnectToServer(const FString& IPAddress, int32 Port);
    
    // 서버 연결 해제
    UFUNCTION(BlueprintCallable, Category = "Networking")
    void DisconnectFromServer();
    
    // 입력 패킷 전송
	UFUNCTION(BlueprintCallable, Category = "Networking")
    void SendInputPacket(float ForwardValue, float RightValue, bool bJumpPressed, bool bAttackPressed);

 //   // 이동 패킷 전송
 //   UFUNCTION(BlueprintCallable, Category = "Networking")
 //   void SendMovePacket(float ForwardValue, float RightValue, const FVector& Position, const FRotator& Rotation, const FVector& Velocity, EPlayerState State);
 //   
 //   // 점프 패킷 전송
 //   UFUNCTION(BlueprintCallable, Category = "Networking")
 //   void SendJumpPacket(bool IsJumping, const FVector& Position, EPlayerState State);
 //   
	//// 공격 패킷 전송
 //   UFUNCTION(BlueprintCallable, Category = "Networking")
	//void SendAttackPacket(const FVector& Position, EPlayerState State);

    // 패킷 수신 처리
    void ProcessIncomingPackets();
    
    // 연결 상태 확인
    UFUNCTION(BlueprintPure, Category = "Networking")
    bool IsConnected() const;
    
    // 마지막 에러 코드 반환
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetLastErrorCode() const { return LastErrorCode; }
    
    // 클라이언트 ID 가져오기
    UFUNCTION(BlueprintPure, Category = "Networking")
    int32 GetClientId() const { return LocalClientId; }
    
    // 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPositionUpdate OnPositionUpdate;
    
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnRotationUpdate OnRotationUpdate;
        
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnConnectionStatusChanged OnConnectionStatusChanged;
    
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnPlayerUpdate OnPlayerUpdate;
    
    UPROPERTY(BlueprintAssignable, Category = "Networking")
    FOnClientIdReceived OnClientIdReceived;

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
    
    // 로컬 클라이언트 ID (서버에서 할당받은 ID)
    int32 LocalClientId;
    
    // 패킷 처리 함수
    void HandlePositionUpdatePacket(const FPositionUpdatePacket* Packet);
    void HandleClientIdPacket(const FClientIdPacket* Packet);
    
    // 타이머 핸들 (패킷 수신용)
    FTimerHandle PacketReceiverTimerHandle;
    
    // 연결 상태 체크
    void CheckConnectionStatus();
};