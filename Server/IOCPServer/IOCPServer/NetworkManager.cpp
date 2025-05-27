#include "NetworkManager.h"

NetworkManager::NetworkManager()
    : listenSocket(INVALID_SOCKET), completionPort(NULL), initialized(false) {
}

NetworkManager::~NetworkManager() {
    Shutdown();
}

bool NetworkManager::InitializeSocket(int port) {
    LOG_INFO("네트워크 초기화 시작 (포트: " + std::to_string(port) + ")");

    // 윈속 초기화
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        LOG_ERROR("WSAStartup 실패");
        return false;
    }
    LOG_INFO("윈속 초기화 성공");

    // 소켓 생성
    listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET) {
        int error = WSAGetLastError();
        LogSocketError("소켓 생성", error);
        WSACleanup();
        return false;
    }
    LOG_INFO("리슨 소켓 생성 성공");

    // 소켓 옵션 설정
    if (!SetListenSocketOptions()) {
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        WSACleanup();
        return false;
    }

    // 바인딩
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
    LOG_INFO("소켓 바인딩 성공 (포트: " + std::to_string(port) + ")");

    // 리슨
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LogSocketError("Listen", error);
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        WSACleanup();
        return false;
    }
    LOG_INFO("리스닝 시작됨");

    // 논블로킹 모드 설정
    u_long mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != NO_ERROR) {
        int error = WSAGetLastError();
        LogSocketError("논블로킹 설정", error);
        // 논블로킹 실패는 치명적이지 않으므로 계속 진행
    }
    else {
        LOG_INFO("논블로킹 모드 설정 성공");
    }

    initialized = true;
    return true;
}

bool NetworkManager::SetupIOCP() {
    LOG_INFO("IOCP 생성 시작");

    completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (completionPort == NULL) {
        DWORD error = GetLastError();
        LOG_ERROR("IOCP 생성 실패: " + std::to_string(error));
        return false;
    }

    LOG_INFO("IOCP 생성 성공");
    return true;
}

void NetworkManager::Shutdown() {
    LOG_INFO("네트워크 매니저 종료 시작");

    if (listenSocket != INVALID_SOCKET) {
        LOG_INFO("리슨 소켓 정리");
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }

    if (completionPort != NULL) {
        LOG_INFO("IOCP 핸들 정리");
        CloseHandle(completionPort);
        completionPort = NULL;
    }

    if (initialized) {
        LOG_INFO("윈속 정리");
        WSACleanup();
        initialized = false;
    }

    LOG_INFO("네트워크 매니저 종료 완료");
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
    // TCP 소켓 옵션 설정: LINGER 비활성화로 종료 속도 향상
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER 옵션
    if (setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("LINGER 옵션 설정 실패: " + GetSocketErrorString(error));
        // LINGER 설정 실패는 치명적이지 않음
    }

    // TCP_NODELAY 활성화 (Nagle 알고리즘 비활성화)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("TCP_NODELAY 옵션 설정 실패: " + GetSocketErrorString(error));
        // TCP_NODELAY 설정 실패는 치명적이지 않음
    }

    // SO_REUSEADDR 옵션 설정 (포트 재사용 허용)
    BOOL reuseAddr = TRUE;
    if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseAddr, sizeof(BOOL)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        LOG_WARNING("SO_REUSEADDR 옵션 설정 실패: " + GetSocketErrorString(error));
    }

    LOG_INFO("소켓 옵션 설정 완료");
    return true;
}

std::string NetworkManager::GetSocketErrorString(int error) const {
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: 연결이 원격 호스트에 의해 강제종료됨";
    case WSAECONNABORTED: return "WSAECONNABORTED: 소프트웨어가 연결 중단 야기";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: 연결 시간 초과";
    case WSAENETDOWN: return "WSAENETDOWN: 네트워크가 다운됨";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: 호스트에 도달할 수 없음";
    case WSAEINTR: return "WSAEINTR: 함수 호출이 중단됨";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: 리소스가 일시적으로 사용 불가";
    case WSAEADDRINUSE: return "WSAEADDRINUSE: 주소가 이미 사용 중";
    case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL: 주소를 사용할 수 없음";
    case WSAENETUNREACH: return "WSAENETUNREACH: 네트워크에 도달할 수 없음";
    default: return "알 수 없는 오류: " + std::to_string(error);
    }
}

void NetworkManager::LogSocketError(const std::string& operation, int error) const {
    LOG_ERROR("[" + operation + "] 실패: " + GetSocketErrorString(error));
}