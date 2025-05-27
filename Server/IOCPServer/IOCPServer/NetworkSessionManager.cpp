#include "NetworkSessionManager.h"

void NetworkSessionManager::SetSocketOptions(SOCKET socket) {
    // LINGER �ɼ� ���� (���� ���� ����)
    LINGER lingerOpt = { 0, 0 };
    if (setsockopt(socket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("Ŭ���̾�Ʈ ���� LINGER �ɼ� ���� ����: " + GetNetworkErrorString(error));
    }

    // TCP_NODELAY �ɼ� ���� (Nagle �˰��� ��Ȱ��ȭ)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("Ŭ���̾�Ʈ ���� TCP_NODELAY �ɼ� ���� ����: " + GetNetworkErrorString(error));
    }

    // SO_KEEPALIVE �ɼ� ���� (���� ���� ����)
    BOOL keepAlive = TRUE;
    if (setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&keepAlive, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("Ŭ���̾�Ʈ ���� SO_KEEPALIVE �ɼ� ���� ����: " + GetNetworkErrorString(error));
    }
}

bool NetworkSessionManager::RegisterToIOCP(HANDLE iocpHandle, ClientSession* client) {
    if (!client || client->socket == INVALID_SOCKET) {
        LOG_ERROR("IOCP ��� ����: ��ȿ���� ���� Ŭ���̾�Ʈ ����");
        return false;
    }

    HANDLE result = CreateIoCompletionPort(
        (HANDLE)client->socket,
        iocpHandle,
        (ULONG_PTR)client,
        0
    );

    if (result == NULL) {
        DWORD error = GetLastError();
        LOG_ERROR("IOCP ��� ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
            ", ����: " + std::to_string(error));
        return false;
    }

    LOG_DEBUG("IOCP ��� ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    return true;
}

bool NetworkSessionManager::PostRecv(ClientSession* client) {
    if (!client || client->socket == INVALID_SOCKET) {
        LOG_ERROR("PostRecv ����: ��ȿ���� ���� Ŭ���̾�Ʈ");
        return false;
    }

    DWORD recvBytes = 0;
    DWORD flags = 0;

    // WSA ���� ����
    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);

    // OVERLAPPED ����ü �ʱ�ȭ
    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    // �񵿱� ���� ����
    int result = WSARecv(
        client->socket,
        &client->wsaBuf,
        1,
        &recvBytes,
        &flags,
        &client->overlapped,
        NULL
    );

    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if (error != WSA_IO_PENDING) {
            LogNetworkError("WSARecv", error, client->id);
            return false;
        }
    }

    LOG_DEBUG("�񵿱� ���� ��û ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    return true;
}

bool NetworkSessionManager::SendPacket(ClientSession* client, const void* data, size_t size, const char* context) {
    if (!client || !data || size == 0) {
        LOG_ERROR("[SendPacket] ��ȿ���� ���� �Ű�����. ���ؽ�Ʈ: " + std::string(context ? context : "Unknown"));
        return false;
    }

    if (client->socket == INVALID_SOCKET) {
        LOG_ERROR("[SendPacket] ��ȿ���� ���� ����. Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return false;
    }

    // WSA ���� ����
    WSABUF wsaBuf;
    wsaBuf.buf = (CHAR*)data;
    wsaBuf.len = (ULONG)size;

    // OVERLAPPED ����ü ���� �Ҵ� (���� �Ϸ� �� ��Ŀ �����忡�� ����)
    WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
    ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

    DWORD sendBytes = 0;
    int result = WSASend(
        client->socket,
        &wsaBuf,
        1,
        &sendBytes,
        0,
        overlapped,
        NULL
    );

    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if (error != WSA_IO_PENDING) {
            LOG_ERROR("[SendPacket] WSASend ����. ����: " + GetNetworkErrorString(error) +
                ", ���ؽ�Ʈ: " + std::string(context ? context : "Unknown") +
                ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
            delete overlapped;
            return false;
        }
    }

    LOG_DEBUG("[SendPacket] ���� ��û ���� - ���ؽ�Ʈ: " + std::string(context ? context : "Unknown") +
        ", ũ��: " + std::to_string(size) +
        ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));

    return true;
}

bool NetworkSessionManager::SendPacketSafe(ClientSession* client, const void* data, size_t size, const char* context) {
    // ��Ŷ ũ�� ����
    if (size > 65536) { // 64KB ����
        LOG_ERROR("[SendPacketSafe] ��Ŷ ũ�Ⱑ �ʹ� ŭ: " + std::to_string(size) + " bytes");
        return false;
    }

    // ���� ���� Ȯ��
    if (!IsSocketConnected(client->socket)) {
        LOG_WARNING("[SendPacketSafe] Ŭ���̾�Ʈ ������ ������ - ID: " + std::to_string(client->id));
        return false;
    }

    return SendPacket(client, data, size, context);
}

bool NetworkSessionManager::IsSocketConnected(SOCKET socket) {
    if (socket == INVALID_SOCKET) {
        return false;
    }

    // TCP ���� ���� Ȯ���� ���� ���� ������ ���� �õ�
    char testByte = 0;
    int result = send(socket, &testByte, 0, 0);

    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if (error == WSAECONNRESET || error == WSAECONNABORTED || error == WSAENOTCONN) {
            return false;
        }
    }

    return true;
}

void NetworkSessionManager::DisconnectClient(ClientSession* client) {
    if (!client || client->socket == INVALID_SOCKET) {
        return;
    }

    LOG_INFO("Ŭ���̾�Ʈ ���� ���� ���� - ID: " + std::to_string(client->id));

    // Graceful shutdown �õ�
    int result = shutdown(client->socket, SD_BOTH);
    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("Shutdown ����: " + GetNetworkErrorString(error) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    }

    // ���� �ݱ�
    closesocket(client->socket);
    client->socket = INVALID_SOCKET;

    // ���� ���� ������Ʈ
    client->ConnectionState = EConnectionState::DISCONNECTED;

    LOG_INFO("Ŭ���̾�Ʈ ���� ���� �Ϸ� - ID: " + std::to_string(client->id));
}

std::string NetworkSessionManager::GetNetworkErrorString(int error) {
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: ������ ���� ȣ��Ʈ�� ���� �缳����";
    case WSAECONNABORTED: return "WSAECONNABORTED: ����Ʈ��� ���� �ߴ� �߱�";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: ���� �ð� �ʰ�";
    case WSAENETDOWN: return "WSAENETDOWN: ��Ʈ��ũ�� �ٿ��";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: ȣ��Ʈ�� ������ �� ����";
    case WSAEINTR: return "WSAEINTR: �Լ� ȣ���� �ߴܵ�";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: ���ҽ��� �Ͻ������� ��� �Ұ�";
    case WSAENOTCONN: return "WSAENOTCONN: ������ ������� ����";
    case WSAESHUTDOWN: return "WSAESHUTDOWN: ������ �����";
    case WSAEMSGSIZE: return "WSAEMSGSIZE: �޽����� �ʹ� ŭ";
    case WSA_IO_PENDING: return "WSA_IO_PENDING: �񵿱� �۾��� ���� ��";
    default: return "�� �� ���� ��Ʈ��ũ ����: " + std::to_string(error);
    }
}

void NetworkSessionManager::LogNetworkError(const std::string& operation, int error, int clientId) {
    std::string message = "[" + operation + "] ��Ʈ��ũ ����: " + GetNetworkErrorString(error);
    if (clientId != -1) {
        message += ", Ŭ���̾�Ʈ ID: " + std::to_string(clientId);
    }
    LOG_ERROR(message);
}