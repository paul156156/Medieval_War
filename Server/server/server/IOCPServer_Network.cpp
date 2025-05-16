#include "IOCPServer.h"
#include "Logger.h"

void IOCPServer::AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr)
{
    // ���� ����
    SetSocketOptions(clientSocket);

    // ClientSession ��ü ���� �� �ʱ�ȭ
    ClientSession* client = CreateSession(clientSocket, clientAddr);
    if (!client) return;

    // IOCP�� ���
    if (!RegisterToIOCP(client))
    {
        closesocket(clientSocket);
        delete client;
        return;
    }
    // clients �ʿ� �߰�
    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients[client->id] = client;
    }

    // �ʱ� Ŭ���̾�Ʈ �ڵ����ũ
    InitializeNewClientSession(client);

    // (�񵿱� ���� ����
    PostRecv(client);
}

void IOCPServer::SetSocketOptions(SOCKET socket)
{
    LINGER lingerOpt = { 0, 0 };
    setsockopt(socket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER));

    BOOL tcpNoDelay = TRUE;
    setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL));
}

bool IOCPServer::RegisterToIOCP(ClientSession* client)
{
    HANDLE result = CreateIoCompletionPort((HANDLE)client->socket, completionPort, (ULONG_PTR)client, 0);
    return result != NULL;
}

bool IOCPServer::PostRecv(ClientSession* client)
{
    DWORD recvBytes = 0;
    DWORD flags = 0;

    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);
    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    int result = WSARecv(client->socket, &client->wsaBuf, 1, &recvBytes, &flags, &client->overlapped, NULL);

    if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
    {
        LOG_ERROR("WSARecv ����: " + GetSocketErrorString(WSAGetLastError()) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        RemoveClient(client->id);
        return false;
    }

    return true;
}

bool IOCPServer::SendPacket(ClientSession* client, const void* data, size_t size, const char* context)
{
    if (!client || size == 0)
    {
        LOG_ERROR("[SendPacket] �߸��� �Ű�����. ���ؽ�Ʈ: " + std::string(context));
        return false;
    }

    WSABUF wsaBuf;
    wsaBuf.buf = (CHAR*)data;
    wsaBuf.len = (ULONG)size;

    WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
    ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

    DWORD sendBytes = 0;
    int result = WSASend(client->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL);

    if (result == SOCKET_ERROR)
    {
        int error = WSAGetLastError();
        if (error != WSA_IO_PENDING)
        {
            LOG_ERROR("[SendPacket] WSASend ����. ����: " + GetSocketErrorString(error) +
                ", ���ؽ�Ʈ: " + std::string(context) +
                ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));

            delete overlapped;
            return false;
        }
    }
    LOG_DEBUG("[SendPacket] WSASend ��û ���� - ���ؽ�Ʈ: " + std::string(context) +
        ", ���� ũ��: " + std::to_string(size) +
        ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));

    return true;
}