#include "NetworkManager.h"

NetworkManager::NetworkManager()
    : listenSocket(INVALID_SOCKET), completionPort(NULL), initialized(false) {
}

NetworkManager::~NetworkManager() {
    Shutdown();
}

bool NetworkManager::InitializeSocket(int port) {
    LOG_INFO("��Ʈ��ũ �ʱ�ȭ ���� (��Ʈ: " + std::to_string(port) + ")");

    // ���� �ʱ�ȭ
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        LOG_ERROR("WSAStartup ����");
        return false;
    }
    LOG_INFO("���� �ʱ�ȭ ����");

    // ���� ����
    listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET) {
        int error = WSAGetLastError();
        LogSocketError("���� ����", error);
        WSACleanup();
        return false;
    }
    LOG_INFO("���� ���� ���� ����");

    // ���� �ɼ� ����
    if (!SetListenSocketOptions()) {
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        WSACleanup();
        return false;
    }

    // ���ε�
    SOCKADDR_IN serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LogSocketError("Bind", error);
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        WSACleanup();
        return false;
    }
    LOG_INFO("���� ���ε� ���� (��Ʈ: " + std::to_string(port) + ")");

    // ����
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LogSocketError("Listen", error);
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        WSACleanup();
        return false;
    }
    LOG_INFO("������ ���۵�");

    // ����ŷ ��� ����
    u_long mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != NO_ERROR) {
        int error = WSAGetLastError();
        LogSocketError("����ŷ ����", error);
        // ����ŷ ���д� ġ�������� �����Ƿ� ��� ����
    }
    else {
        LOG_INFO("����ŷ ��� ���� ����");
    }

    initialized = true;
    return true;
}

bool NetworkManager::SetupIOCP() {
    LOG_INFO("IOCP ���� ����");

    completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (completionPort == NULL) {
        DWORD error = GetLastError();
        LOG_ERROR("IOCP ���� ����: " + std::to_string(error));
        return false;
    }

    LOG_INFO("IOCP ���� ����");
    return true;
}

void NetworkManager::Shutdown() {
    LOG_INFO("��Ʈ��ũ �Ŵ��� ���� ����");

    if (listenSocket != INVALID_SOCKET) {
        LOG_INFO("���� ���� ����");
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }

    if (completionPort != NULL) {
        LOG_INFO("IOCP �ڵ� ����");
        CloseHandle(completionPort);
        completionPort = NULL;
    }

    if (initialized) {
        LOG_INFO("���� ����");
        WSACleanup();
        initialized = false;
    }

    LOG_INFO("��Ʈ��ũ �Ŵ��� ���� �Ϸ�");
}

SOCKET NetworkManager::GetListenSocket() const {
    return listenSocket;
}

HANDLE NetworkManager::GetCompletionPort() const {
    return completionPort;
}

bool NetworkManager::IsValidSocket(SOCKET socket) const {
    return socket != INVALID_SOCKET;
}

bool NetworkManager::SetListenSocketOptions() {
    // TCP ���� �ɼ� ����: LINGER ��Ȱ��ȭ�� ���� �ӵ� ���
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER �ɼ�
    if (setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("LINGER �ɼ� ���� ����: " + GetSocketErrorString(error));
        // LINGER ���� ���д� ġ�������� ����
    }

    // TCP_NODELAY Ȱ��ȭ (Nagle �˰��� ��Ȱ��ȭ)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("TCP_NODELAY �ɼ� ���� ����: " + GetSocketErrorString(error));
        // TCP_NODELAY ���� ���д� ġ�������� ����
    }

    // SO_REUSEADDR �ɼ� ���� (��Ʈ ���� ���)
    BOOL reuseAddr = TRUE;
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseAddr, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("SO_REUSEADDR �ɼ� ���� ����: " + GetSocketErrorString(error));
    }

    LOG_INFO("���� �ɼ� ���� �Ϸ�");
    return true;
}

std::string NetworkManager::GetSocketErrorString(int error) const {
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: ������ ���� ȣ��Ʈ�� ���� ���������";
    case WSAECONNABORTED: return "WSAECONNABORTED: ����Ʈ��� ���� �ߴ� �߱�";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: ���� �ð� �ʰ�";
    case WSAENETDOWN: return "WSAENETDOWN: ��Ʈ��ũ�� �ٿ��";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: ȣ��Ʈ�� ������ �� ����";
    case WSAEINTR: return "WSAEINTR: �Լ� ȣ���� �ߴܵ�";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: ���ҽ��� �Ͻ������� ��� �Ұ�";
    case WSAEADDRINUSE: return "WSAEADDRINUSE: �ּҰ� �̹� ��� ��";
    case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL: �ּҸ� ����� �� ����";
    case WSAENETUNREACH: return "WSAENETUNREACH: ��Ʈ��ũ�� ������ �� ����";
    default: return "�� �� ���� ����: " + std::to_string(error);
    }
}

void NetworkManager::LogSocketError(const std::string& operation, int error) const {
    LOG_ERROR("[" + operation + "] ����: " + GetSocketErrorString(error));
}