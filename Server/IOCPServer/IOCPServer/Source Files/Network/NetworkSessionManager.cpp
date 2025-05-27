#include "NetworkSessionManager.h"

void NetworkSessionManager::SetSocketOptions(SOCKET socket) {
    // LINGER 옵션 설정 (빠른 소켓 종료)
    LINGER lingerOpt = { 0, 0 };
    if (setsockopt(socket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("클라이언트 소켓 LINGER 옵션 설정 실패: " + GetNetworkErrorString(error));
    }

    // TCP_NODELAY 옵션 설정 (Nagle 알고리즘 비활성화)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("클라이언트 소켓 TCP_NODELAY 옵션 설정 실패: " + GetNetworkErrorString(error));
    }

    // SO_KEEPALIVE 옵션 설정 (연결 상태 감지)
    BOOL keepAlive = TRUE;
    if (setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&keepAlive, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("클라이언트 소켓 SO_KEEPALIVE 옵션 설정 실패: " + GetNetworkErrorString(error));
    }
}

bool NetworkSessionManager::RegisterToIOCP(HANDLE iocpHandle, ClientSession* client) {
    if (!client || client->socket == INVALID_SOCKET) {
        LOG_ERROR("IOCP 등록 실패: 유효하지 않은 클라이언트 세션");
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
        LOG_ERROR("IOCP 등록 실패 - 클라이언트 ID: " + std::to_string(client->id) +
            ", 에러: " + std::to_string(error));
        return false;
    }

    LOG_DEBUG("IOCP 등록 성공 - 클라이언트 ID: " + std::to_string(client->id));
    return true;
}

bool NetworkSessionManager::PostRecv(ClientSession* client) {
    if (!client || client->socket == INVALID_SOCKET) {
        LOG_ERROR("PostRecv 실패: 유효하지 않은 클라이언트");
        return false;
    }

    DWORD recvBytes = 0;
    DWORD flags = 0;

    // WSA 버퍼 설정
    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);

    // OVERLAPPED 구조체 초기화
    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    // 비동기 수신 시작
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

    LOG_DEBUG("비동기 수신 요청 성공 - 클라이언트 ID: " + std::to_string(client->id));
    return true;
}

bool NetworkSessionManager::SendPacket(ClientSession* client, const void* data, size_t size, const char* context) {
    if (!client || !data || size == 0) {
        LOG_ERROR("[SendPacket] 유효하지 않은 매개변수. 컨텍스트: " + std::string(context ? context : "Unknown"));
        return false;
    }

    if (client->socket == INVALID_SOCKET) {
        LOG_ERROR("[SendPacket] 유효하지 않은 소켓. 클라이언트 ID: " + std::to_string(client->id));
        return false;
    }

    // WSA 버퍼 설정
    WSABUF wsaBuf;
    wsaBuf.buf = (CHAR*)data;
    wsaBuf.len = (ULONG)size;

    // OVERLAPPED 구조체 동적 할당 (전송 완료 후 워커 스레드에서 해제)
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
            LOG_ERROR("[SendPacket] WSASend 실패. 에러: " + GetNetworkErrorString(error) +
                ", 컨텍스트: " + std::string(context ? context : "Unknown") +
                ", 클라이언트 ID: " + std::to_string(client->id));
            delete overlapped;
            return false;
        }
    }

    LOG_DEBUG("[SendPacket] 전송 요청 성공 - 컨텍스트: " + std::string(context ? context : "Unknown") +
        ", 크기: " + std::to_string(size) +
        ", 클라이언트 ID: " + std::to_string(client->id));

    return true;
}

bool NetworkSessionManager::SendPacketSafe(ClientSession* client, const void* data, size_t size, const char* context) {
    // 패킷 크기 검증
    if (size > 65536) { // 64KB 제한
        LOG_ERROR("[SendPacketSafe] 패킷 크기가 너무 큼: " + std::to_string(size) + " bytes");
        return false;
    }

    // 연결 상태 확인
    if (!IsSocketConnected(client->socket)) {
        LOG_WARNING("[SendPacketSafe] 클라이언트 연결이 끊어짐 - ID: " + std::to_string(client->id));
        return false;
    }

    return SendPacket(client, data, size, context);
}

bool NetworkSessionManager::IsSocketConnected(SOCKET socket) {
    if (socket == INVALID_SOCKET) {
        return false;
    }

    // TCP 연결 상태 확인을 위한 더미 데이터 전송 시도
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

    LOG_INFO("클라이언트 연결 종료 시작 - ID: " + std::to_string(client->id));

    // Graceful shutdown 시도
    int result = shutdown(client->socket, SD_BOTH);
    if (result == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("Shutdown 실패: " + GetNetworkErrorString(error) +
            ", 클라이언트 ID: " + std::to_string(client->id));
    }

    // 소켓 닫기
    closesocket(client->socket);
    client->socket = INVALID_SOCKET;

    // 연결 상태 업데이트
    client->ConnectionState = EConnectionState::DISCONNECTED;

    LOG_INFO("클라이언트 연결 종료 완료 - ID: " + std::to_string(client->id));
}

std::string NetworkSessionManager::GetNetworkErrorString(int error) {
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: 연결이 원격 호스트에 의해 재설정됨";
    case WSAECONNABORTED: return "WSAECONNABORTED: 소프트웨어가 연결 중단 야기";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: 연결 시간 초과";
    case WSAENETDOWN: return "WSAENETDOWN: 네트워크가 다운됨";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: 호스트에 도달할 수 없음";
    case WSAEINTR: return "WSAEINTR: 함수 호출이 중단됨";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: 리소스가 일시적으로 사용 불가";
    case WSAENOTCONN: return "WSAENOTCONN: 소켓이 연결되지 않음";
    case WSAESHUTDOWN: return "WSAESHUTDOWN: 소켓이 종료됨";
    case WSAEMSGSIZE: return "WSAEMSGSIZE: 메시지가 너무 큼";
    case WSA_IO_PENDING: return "WSA_IO_PENDING: 비동기 작업이 진행 중";
    default: return "알 수 없는 네트워크 오류: " + std::to_string(error);
    }
}

void NetworkSessionManager::LogNetworkError(const std::string& operation, int error, int clientId) {
    std::string message = "[" + operation + "] 네트워크 오류: " + GetNetworkErrorString(error);
    if (clientId != -1) {
        message += ", 클라이언트 ID: " + std::to_string(clientId);
    }
    LOG_ERROR(message);
}