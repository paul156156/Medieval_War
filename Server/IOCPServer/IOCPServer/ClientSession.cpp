#include "ClientSession.h"
#include <cmath>

ClientSession::ClientSession() {
    SetDefaultValues();
}

ClientSession::~ClientSession() {
    if (socket != INVALID_SOCKET) {
        closesocket(socket);
        socket = INVALID_SOCKET;
    }
}

void ClientSession::Initialize(SOCKET clientSocket, SOCKADDR_IN clientAddr, int clientId) {
    socket = clientSocket;
    addr = clientAddr;
    id = clientId;

    // WSA 버퍼 설정
    wsaBuf.buf = recvBuffer;
    wsaBuf.len = sizeof(recvBuffer);

    // OVERLAPPED 구조체 초기화
    ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));

    // 연결 상태 설정
    ConnectionState = EConnectionState::CONNECTED;

    // 타이밍 초기화
    float currentTime = GetTickCount64() / 1000.0f;
    LastPingTime = currentTime;
    LastPongTime = currentTime;
    LastUpdateTime = currentTime;
    LastInputTime = currentTime;

    // 기본 스폰 위치 설정 (예시)
    Position = Vec3(0.0f, 0.0f, 90.0f);
    PreviousPosition = Position;
}

bool ClientSession::IsConnected() const {
    return socket != INVALID_SOCKET &&
        (ConnectionState == EConnectionState::CONNECTED ||
            ConnectionState == EConnectionState::AUTHENTICATED);
}

bool ClientSession::IsTimedOut(float currentTime) const {
    const float PING_TIMEOUT = 30.0f; // 30초 타임아웃
    return (currentTime - LastPingTime) > PING_TIMEOUT;
}

bool ClientSession::IsValidInput(float forward, float right) const {
    return IsValidInputValue(forward) && IsValidInputValue(right);
}

bool ClientSession::IsValidRotation(float pitch, float yaw, float roll) const {
    // Pitch는 -90 ~ 90도로 제한
    bool validPitch = (pitch >= -90.0f && pitch <= 90.0f && !isnan(pitch) && isfinite(pitch));
    bool validYaw = IsValidRotationValue(yaw);
    bool validRoll = IsValidRotationValue(roll);

    return validPitch && validYaw && validRoll;
}

void ClientSession::Reset() {
    SetDefaultValues();

    if (socket != INVALID_SOCKET) {
        closesocket(socket);
        socket = INVALID_SOCKET;
    }
}

void ClientSession::SetDefaultValues() {
    socket = INVALID_SOCKET;
    id = 0;

    // 위치 및 속도 초기화
    Position = Vec3();
    PreviousPosition = Vec3();
    Velocity = Vec3();
    PreviousVelocity = Vec3();

    // 회전 초기화
    Rotation = Rot3();
    InputPitch = 0.0f;
    InputYaw = 0.0f;
    InputRoll = 0.0f;

    // 상태 초기화
    State = EPlayerState::IDLE;
    PreviousState = EPlayerState::IDLE;
    ConnectionState = EConnectionState::CONNECTING;

    // 입력 초기화
    InputForward = 0.0f;
    InputRight = 0.0f;
    bJumpRequested = false;
    bAttackRequested = false;
    bRunRequested = false;
    //bCrouchRequested = false;

    // 타이밍 초기화
    LastPingTime = 0.0f;
    LastPongTime = 0.0f;
    LastUpdateTime = 0.0f;
    LastInputTime = 0.0f;
    ConnectionTimeout = 30.0f;

    // 안티 치트 초기화
    PacketSequence = 0;
    SpamCount = 0;

    // 버퍼 초기화
    ZeroMemory(recvBuffer, sizeof(recvBuffer));
    ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));
    ZeroMemory(&addr, sizeof(SOCKADDR_IN));
}