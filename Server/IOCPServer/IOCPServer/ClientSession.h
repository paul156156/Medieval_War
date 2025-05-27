#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "PacketTypes.h"

// ���� ���� ����
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
    // ��Ʈ��ũ ���� ������
    SOCKET socket;                    // Ŭ���̾�Ʈ ����
    SOCKADDR_IN addr;                 // Ŭ���̾�Ʈ �ּ� ����
    int id;                           // Ŭ���̾�Ʈ ���� ID

    // �񵿱� I/O ����ü
    WSABUF wsaBuf;                    // WSA ���� ����ü
    WSAOVERLAPPED overlapped;         // �񵿱� I/O ����ü
    char recvBuffer[1024];            // ���� ����

    // ���� ���� ������
    Vec3 Position;                    // ���� ��ġ
    Vec3 PreviousPosition;            // ���� ��ġ
    Vec3 Velocity;                    // ���� �ӵ�
    Vec3 PreviousVelocity;            // ���� �ӵ�

    // ȸ�� ����
    Rot3 Rotation;                    // ���� ȸ����
    float InputPitch;       // ����
    float InputYaw;         // �¿�
    float InputRoll;        // ��

    // �÷��̾� ����
    EPlayerState State;               // ���� �÷��̾� ����
    EPlayerState PreviousState;       // ���� �÷��̾� ����
    EConnectionState ConnectionState; // ���� ����

    // �Է� ������
    float InputForward;               // ��/�� �Է°�
    float InputRight;                 // ��/�� �Է°�
    bool bJumpRequested;              // ���� ��û ����
    bool bAttackRequested;            // ���� ��û ����
    bool bRunRequested;               // �޸��� ��û ����

    // Ÿ�̹� ����
    float LastPingTime;               // ������ Ping ���� �ð�
    float LastPongTime;               // ������ Pong �߼� �ð�
    float LastUpdateTime;             // ������ ������Ʈ �ð�
    float LastInputTime;              // ������ �Է� �ð�
    float ConnectionTimeout;          // ���� Ÿ�Ӿƿ�

    // ��Ƽ ġƮ ����
    uint32_t PacketSequence;          // ��Ŷ ���� �����
    int SpamCount;                    // ���� ī��Ʈ

    // ������
    ClientSession();

    // �Ҹ���
    ~ClientSession();

    // �ʱ�ȭ
    void Initialize(SOCKET clientSocket, SOCKADDR_IN clientAddr, int clientId);

    // ���� üũ
    bool IsConnected() const;
    bool IsTimedOut(float currentTime) const;

    // �Է� ����
    bool IsValidInput(float forward, float right) const;
    bool IsValidRotation(float pitch, float yaw, float roll) const;

    // ����
    void Reset();

private:
    void SetDefaultValues();
};