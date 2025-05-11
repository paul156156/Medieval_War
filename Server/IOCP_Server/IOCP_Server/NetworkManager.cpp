// NetworkManager.cpp
#include "NetworkManager.h"
#include <WinSock2.h>
#include <WS2tcpip.h>


NetworkManager::NetworkManager() : listenSocket(INVALID_SOCKET), completionPort(NULL) {}

NetworkManager::~NetworkManager() {
    Shutdown();
}

bool NetworkManager::InitializeSocket(int port)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        LOG_ERROR("WSAStartup 실패");
        return false;
    }

    listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET)
    {
        LOG_ERROR("소켓 생성 실패");
        return false;
    }

    LINGER lingerOpt = { 0, 0 };
    setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(lingerOpt));

    BOOL tcpNoDelay = TRUE;
    setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL));

    SOCKADDR_IN addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        LOG_ERROR("Bind 실패");
        return false;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        LOG_ERROR("Listen 실패");
        return false;
    }

    u_long mode = 1;
    ioctlsocket(listenSocket, FIONBIO, &mode);

    return true;
}

bool NetworkManager::SetupIOCP()
{
    completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    return completionPort != NULL;
}

void NetworkManager::Shutdown()
{
    if (listenSocket != INVALID_SOCKET) {
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }

    if (completionPort) {
        CloseHandle(completionPort);
        completionPort = NULL;
    }

    WSACleanup();
}

SOCKET NetworkManager::GetListenSocket() const {
    return listenSocket;
}

HANDLE NetworkManager::GetCompletionPort() const {
    return completionPort;
}