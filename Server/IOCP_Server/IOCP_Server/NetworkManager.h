// NetworkSessionManager.h
#pragma once
#include "Logger.h"
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    bool InitializeSocket(int port);
    bool SetupIOCP();
    void Shutdown();

    SOCKET GetListenSocket() const;
    HANDLE GetCompletionPort() const;

private:
    SOCKET listenSocket;
    HANDLE completionPort;
};