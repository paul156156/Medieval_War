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

    // WSA ���� ����
    wsaBuf.buf = recvBuffer;
    wsaBuf.len = sizeof(recvBuffer);

    // OVERLAPPED ����ü �ʱ�ȭ
    ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));

    // ���� ���� ����
    ConnectionState = EConnectionState::CONNECTED;

    // Ÿ�̹� �ʱ�ȭ
    float currentTime = GetTickCount64() / 1000.0f;
    LastPingTime = currentTime;
    LastPongTime = currentTime;
    LastUpdateTime = currentTime;
    LastInputTime = currentTime;

    // �⺻ ���� ��ġ ���� (����)
    Position = Vec3(0.0f, 0.0f, 90.0f);
    PreviousPosition = Position;
}

bool ClientSession::IsConnected() const {
    return socket != INVALID_SOCKET &&
        (ConnectionState == EConnectionState::CONNECTED ||
            ConnectionState == EConnectionState::AUTHENTICATED);
}

bool ClientSession::IsTimedOut(float currentTime) const {
    const float PING_TIMEOUT = 30.0f; // 30�� Ÿ�Ӿƿ�
    return (currentTime - LastPingTime) > PING_TIMEOUT;
}

bool ClientSession::IsValidInput(float forward, float right) const {
    return IsValidInputValue(forward) && IsValidInputValue(right);
}

bool ClientSession::IsValidRotation(float pitch, float yaw, float roll) const {
    // Pitch�� -90 ~ 90���� ����
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

    // ��ġ �� �ӵ� �ʱ�ȭ
    Position = Vec3();
    PreviousPosition = Vec3();
    Velocity = Vec3();
    PreviousVelocity = Vec3();

    // ȸ�� �ʱ�ȭ
    Rotation = Rot3();
    InputPitch = 0.0f;
    InputYaw = 0.0f;
    InputRoll = 0.0f;

    // ���� �ʱ�ȭ
    State = EPlayerState::IDLE;
    PreviousState = EPlayerState::IDLE;
    ConnectionState = EConnectionState::CONNECTING;

    // �Է� �ʱ�ȭ
    InputForward = 0.0f;
    InputRight = 0.0f;
    bJumpRequested = false;
    bAttackRequested = false;
    bRunRequested = false;
    //bCrouchRequested = false;

    // Ÿ�̹� �ʱ�ȭ
    LastPingTime = 0.0f;
    LastPongTime = 0.0f;
    LastUpdateTime = 0.0f;
    LastInputTime = 0.0f;
    ConnectionTimeout = 30.0f;

    // ��Ƽ ġƮ �ʱ�ȭ
    PacketSequence = 0;
    SpamCount = 0;

    // ���� �ʱ�ȭ
    ZeroMemory(recvBuffer, sizeof(recvBuffer));
    ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));
    ZeroMemory(&addr, sizeof(SOCKADDR_IN));
}