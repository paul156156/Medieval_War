#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "PacketTypes.h"

struct ClientSession {
    // ��Ʈ��ũ ���� ������
    SOCKET socket;                // Ŭ���̾�Ʈ ����
    SOCKADDR_IN addr;             // Ŭ���̾�Ʈ �ּ� ����
    char recvBuffer[1024];        // ���� ����
    WSAOVERLAPPED overlapped;     // �񵿱� I/O ����ü
    WSABUF wsaBuf;                // WSA ���� ����ü

    // Ŭ���̾�Ʈ �ĺ� ����
    int id;                       // Ŭ���̾�Ʈ ���� ID

    // ���� ���� ������
    EPlayerState State;           // ���� �÷��̾� ����
    EPlayerState PreviousState;   // ���� �÷��̾� ����
    Vec3 Position;                // ���� ��ġ
    Vec3 LastPosition;            // ���� ��ġ
    Rot3 Rotation;                // ���� ȸ����
    Vec3 Velocity;                // ���� �ӵ�

    float LastUpdateTime;         // ������ ������Ʈ �ð�
	float LastPingTime;           // ������ Ping ���� �ð�
    float LastPongTime;           // ���������� Pong ���� �ð�

    // �Է� ������
    float InputForward = 0.0f;    // ��/�� �Է°�
    float InputRight = 0.0f;      // ��/�� �Է°�
	float Pitch = 0.0f;   // ��ġ��
	float Yaw = 0.0f; // ȸ����
	float Roll = 0.0f; // �Ѱ�

	bool bRunRequested = false;   // �̵� ��û ����
	bool bCrouchRequested = false; // �ޱ׸��� ��û ����
    bool bJumpRequested = false;  // ���� ��û ����
    bool bAttackRequested = false;// ���� ��û ����
};