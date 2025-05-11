// NetworkSessionManager.cpp
#include "NetworkSessionManager.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

void NetworkSessionManager::SetSocketOptions(SOCKET socket)
{
    LINGER lingerOpt = { 0, 0 };
    setsockopt(socket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER));

    BOOL tcpNoDelay = TRUE;
    setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL));
}

bool NetworkSessionManager::RegisterToIOCP(HANDLE iocpHandle, ClientSession* client)
{
    HANDLE result = CreateIoCompletionPort((HANDLE)client->socket, iocpHandle, (ULONG_PTR)client, 0);
    return result != NULL;
}

bool NetworkSessionManager::PostRecv(ClientSession* client)
{
    DWORD recvBytes = 0;
    DWORD flags = 0;

    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);
    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    int result = WSARecv(client->socket, &client->wsaBuf, 1, &recvBytes, &flags, &client->overlapped, NULL);

    if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
    {
        LOG_ERROR("WSARecv 실패: 클라이언트 ID: " + std::to_string(client->id));
        return false;
    }

    return true;
}

bool NetworkSessionManager::SendPacket(ClientSession* client, const void* data, size_t size, const char* context)
{
    if (!client || size == 0)
    {
        LOG_ERROR(std::string("[SendPacket] 잘못된 매개변수. 컨텍스트: ") + context);
        return false;
    }

    WSABUF wsaBuf;
    wsaBuf.buf = (CHAR*)data;
    wsaBuf.len = (ULONG)size;

    WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
    ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

    DWORD sendBytes = 0;
    int result = WSASend(client->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL);

    if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
    {
        LOG_ERROR(std::string("[SendPacket] WSASend 실패. 컨텍스트: ") + context +
            ", 클라이언트 ID: " + std::to_string(client->id));
        delete overlapped;
        return false;
    }

    return true;
}