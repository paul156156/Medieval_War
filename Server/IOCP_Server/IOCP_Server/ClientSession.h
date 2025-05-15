//ClientSession.h
#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "PacketTypes.h"

class ClientSession
{
public:
    SOCKET socket;
    SOCKADDR_IN addr;
    int id;

    WSABUF wsaBuf;
    WSAOVERLAPPED overlapped;
    char recvBuffer[1024];

    Vec3 Position;
    Vec3 LastPosition;
    Vec3 Velocity;
    Vec3 PreviousVelocity;

	Rot3 Rotation;
    float ControlRotationYaw;

    EPlayerState State;
    EPlayerState PreviousState;

    float InputForward = 0.0f;
    float InputRight = 0.0f;
    bool bJumpRequested = false;
    bool bAttackRequested = false;

    float LastPingTime = 0.0f;
    float LastPongTime = 0.0f;
    float LastUpdateTime = 0.0f;
};
