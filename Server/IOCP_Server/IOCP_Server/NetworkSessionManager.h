//NetworkSessionManager.h
#pragma once
#include "ClientSession.h"
#include "Logger.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

class NetworkSessionManager
{
public:
    static void SetSocketOptions(SOCKET socket);
    static bool RegisterToIOCP(HANDLE iocpHandle, ClientSession* client);
    static bool PostRecv(ClientSession* client);
    static bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context);
};
