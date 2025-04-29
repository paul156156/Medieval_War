#include "IOCPServer.h"
#include "Logger.h"

void IOCPServer::AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr)
{
    // 소켓 설정
    SetSocketOptions(clientSocket);

    // ClientSession 객체 생성 및 초기화
    ClientSession* client = CreateSession(clientSocket, clientAddr);
    if (!client) return;

    // IOCP에 등록
    if (!RegisterToIOCP(client))
    {
        closesocket(clientSocket);
        delete client;
        return;
    }
    // clients 맵에 추가
    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients[client->id] = client;
    }

    // 초기 클라이언트 핸드셰이크
    InitializeNewClientSession(client);

    // (비동기 수신 시작
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
        LOG_ERROR("WSARecv 실패: " + GetSocketErrorString(WSAGetLastError()) +
            ", 클라이언트 ID: " + std::to_string(client->id));
        RemoveClient(client->id);
        return false;
    }

    return true;
}

bool IOCPServer::SendPacket(ClientSession* client, const void* data, size_t size, const char* context)
{
    if (!client || size == 0)
    {
        LOG_ERROR("[SendPacket] 잘못된 매개변수. 컨텍스트: " + std::string(context));
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
            LOG_ERROR("[SendPacket] WSASend 실패. 오류: " + GetSocketErrorString(error) +
                ", 컨텍스트: " + std::string(context) +
                ", 클라이언트 ID: " + std::to_string(client->id));

            delete overlapped;
            return false;
        }
    }
    LOG_DEBUG("[SendPacket] WSASend 요청 성공 - 컨텍스트: " + std::string(context) +
        ", 보낸 크기: " + std::to_string(size) +
        ", 클라이언트 ID: " + std::to_string(client->id));

    return true;
}