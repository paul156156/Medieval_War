#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "PacketTypes.h"

// 연결 상태 정의
enum class EConnectionState : uint8_t {
    CONNECTING = 0,
    CONNECTED = 1,
    AUTHENTICATING = 2,
    AUTHENTICATED = 3,
    DISCONNECTING = 4,
    DISCONNECTED = 5
};

class ClientSession {
public:
    // 네트워크 관련 데이터
    SOCKET socket;                    // 클라이언트 소켓
    SOCKADDR_IN addr;                 // 클라이언트 주소 정보
    int id;                           // 클라이언트 고유 ID

    // 비동기 I/O 구조체
    WSABUF wsaBuf;                    // WSA 버퍼 구조체
    WSAOVERLAPPED overlapped;         // 비동기 I/O 구조체
    char recvBuffer[1024];            // 수신 버퍼

    // 게임 상태 데이터
    Vec3 Position;                    // 현재 위치
    Vec3 PreviousPosition;            // 이전 위치
    Vec3 Velocity;                    // 현재 속도
    Vec3 PreviousVelocity;            // 이전 속도

    // 회전 정보
    Rot3 Rotation;                    // 현재 회전값
    float InputPitch;       // 상하
    float InputYaw;         // 좌우
    float InputRoll;        // 롤

    // 플레이어 상태
    EPlayerState State;               // 현재 플레이어 상태
    EPlayerState PreviousState;       // 이전 플레이어 상태
    EConnectionState ConnectionState; // 연결 상태

    // 입력 데이터
    float InputForward;               // 전/후 입력값
    float InputRight;                 // 좌/우 입력값
    bool bJumpRequested;              // 점프 요청 여부
    bool bAttackRequested;            // 공격 요청 여부
    bool bRunRequested;               // 달리기 요청 여부

    // 타이밍 관련
    float LastPingTime;               // 마지막 Ping 수신 시간
    float LastPongTime;               // 마지막 Pong 발송 시간
    float LastUpdateTime;             // 마지막 업데이트 시간
    float LastInputTime;              // 마지막 입력 시간
    float ConnectionTimeout;          // 연결 타임아웃

    // 안티 치트 관련
    uint32_t PacketSequence;          // 패킷 순서 보장용
    int SpamCount;                    // 스팸 카운트

    // 생성자
    ClientSession();

    // 소멸자
    ~ClientSession();

    // 초기화
    void Initialize(SOCKET clientSocket, SOCKADDR_IN clientAddr, int clientId);

    // 상태 체크
    bool IsConnected() const;
    bool IsTimedOut(float currentTime) const;

    // 입력 검증
    bool IsValidInput(float forward, float right) const;
    bool IsValidRotation(float pitch, float yaw, float roll) const;

    // 리셋
    void Reset();

private:
    void SetDefaultValues();
};