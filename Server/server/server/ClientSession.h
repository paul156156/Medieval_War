#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "PacketTypes.h"

struct ClientSession {
    SOCKET socket;
    SOCKADDR_IN addr;
    char recvBuffer[1024];
    WSAOVERLAPPED overlapped;
    WSABUF wsaBuf;
    int id;

    EPlayerState State;
    Vec3 Position, LastPosition;
    Rot3 Rotation;
    float LastUpdateTime;
};
