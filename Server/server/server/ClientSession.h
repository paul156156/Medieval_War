#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "PacketTypes.h"

struct ClientSession {
    // 네트워크 관련 데이터
    SOCKET socket;                // 클라이언트 소켓
    SOCKADDR_IN addr;             // 클라이언트 주소 정보
    char recvBuffer[1024];        // 수신 버퍼
    WSAOVERLAPPED overlapped;     // 비동기 I/O 구조체
    WSABUF wsaBuf;                // WSA 버퍼 구조체

    // 클라이언트 식별 정보
    int id;                       // 클라이언트 고유 ID

    // 게임 상태 데이터
    EPlayerState State;           // 현재 플레이어 상태
    EPlayerState PreviousState = EPlayerState::IDLE; // 이전 플레이어 상태
    Vec3 Position;                // 현재 위치
    Vec3 LastPosition;            // 이전 위치
    Rot3 Rotation;                // 현재 회전값
    Vec3 Velocity;                // 현재 속도
    float LastUpdateTime;         // 마지막 업데이트 시간

    // 입력 데이터
    float InputForward = 0.0f;    // 전/후 입력값
    float InputRight = 0.0f;      // 좌/우 입력값
    bool bJumpRequested = false;  // 점프 요청 여부
    bool bAttackRequested = false;// 공격 요청 여부
};