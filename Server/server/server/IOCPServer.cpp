#include "IOCPServer.h"
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include "PacketTypes.h"
#include "Logger.h"

IOCPServer::IOCPServer() : listenSocket(INVALID_SOCKET), completionPort(NULL), nextClientId(1), isRunning(true)
{
    Logger::GetInstance().Initialize();
    LOG_INFO("서버 인스턴스 생성됨");
}

IOCPServer::~IOCPServer() {
    LOG_INFO("서버 소멸자 호출됨");
    CleanUp();
}

bool IOCPServer::Initialize(int port)
{
    LOG_INFO("서버 초기화 시작 (포트: " + std::to_string(port) + ")");

    // 윈속 초기화
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        LOG_ERROR("WSAStartup 실패");
        return false;
    }
    LOG_INFO("윈속 초기화 성공");

    // 소켓 생성
    listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET)
    {
        LOG_ERROR("소켓 생성 실패: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("리스닝 소켓 생성 성공");

    // TCP 소켓 옵션 설정: LINGER 비활성화로 종료 속도 향상
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER 옵션
    if (setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        LOG_WARNING("LINGER 옵션 설정 실패: " + std::to_string(WSAGetLastError()));
    }

    // TCP_NODELAY 활성화 (Nagle 알고리즘 비활성화)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        LOG_WARNING("TCP_NODELAY 옵션 설정 실패: " + std::to_string(WSAGetLastError()));
    }

    // 바인딩
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        LOG_ERROR("Bind 실패: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("소켓 바인딩 성공 (포트: " + std::to_string(port) + ")");

    // 리슨
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        LOG_ERROR("Listen 실패: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("리스닝 시작됨");

    // IOCP 생성
    completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (completionPort == NULL)
    {
        LOG_ERROR("IOCP 생성 실패: " + std::to_string(GetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("IOCP 생성 성공");

    // CPU 개수 확인
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors;
    LOG_INFO("CPU 코어 수: " + std::to_string(sysInfo.dwNumberOfProcessors) + ", 생성할 작업자 스레드: " + std::to_string(threadCount));

    // 작업자 스레드 생성
    for (int i = 0; i < threadCount; i++)
    {
        HANDLE thread = CreateThread(NULL, 0, WorkerThreadProc, this, 0, NULL);
        if (thread == NULL)
        {
            LOG_ERROR("작업자 스레드 생성 실패: " + std::to_string(GetLastError()));
            CleanUp();
            return false;
        }
        LOG_INFO("작업자 스레드 #" + std::to_string(i + 1) + " 생성됨");
        CloseHandle(thread);
    }

    LOG_INFO("서버 초기화 완료");

    return true;
}

void IOCPServer::Run()
{
    LOG_INFO("서버 실행 시작");
    uint64_t LastTickTime = GetTickCount64();
    uint64_t framesCount = 0;
    uint64_t lastFpsTime = GetTickCount64();
    float averageFrameTime = 0;

    u_long mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != NO_ERROR)
    {
        LOG_ERROR("listenSocket 논블로킹 설정 실패 - 에러: " + std::to_string(WSAGetLastError()));
        return;
    }
    else
    {
        LOG_INFO("listenSocket 논블로킹 설정 성공");
    }

    while (isRunning)
    {
        uint64_t frameStartTime = GetTickCount64();

        uint64_t Now = GetTickCount64();
        float DeltaTime = (Now - LastTickTime) / 1000.0f; // 밀리초 → 초
        LastTickTime = Now;

        // FPS 계산 (1초마다)
        framesCount++;
        if (Now - lastFpsTime > 1000) {
            float fps = static_cast<float>(framesCount) * 1000.0f / (Now - lastFpsTime);
            LOG_INFO("서버 FPS: " + std::to_string(fps) + ", 평균 프레임 시간: " +
                std::to_string(averageFrameTime) + "ms, 클라이언트 수: " +
                std::to_string(GetClientCount()));

            framesCount = 0;
            lastFpsTime = Now;
        }

        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, NULL, 0);

        if (clientSocket != INVALID_SOCKET)
        {
            // 연결 요청 있으면 처리
            AcceptClient(clientSocket, clientAddr);
        }

        // 전체 클라이언트 업데이트
        Update(DeltaTime);

        // 프레임 시간 측정 및 조절
        uint64_t frameEndTime = GetTickCount64();
        uint64_t frameTime = frameEndTime - frameStartTime;

        // 지수 이동 평균으로 평균 프레임 시간 계산 (가중치 0.1)
        averageFrameTime = averageFrameTime * 0.9f + frameTime * 0.1f;

        // 목표 프레임 시간 (16.67ms = 약 60 FPS)
        const uint64_t targetFrameTime = 16;

        if (frameTime < targetFrameTime) {
            Sleep(static_cast<DWORD>(targetFrameTime - frameTime));
        }
    }

    LOG_INFO("서버 실행 종료");
}

void IOCPServer::CleanUp()
{
    LOG_INFO("서버 자원 정리 시작");
    isRunning = false;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors;

    // 작업자 스레드 종료 신호
    if (completionPort != NULL)
    {
        LOG_INFO("작업자 스레드에 종료 신호 전송");
        for (int i = 0; i < threadCount; i++)
        {
            PostQueuedCompletionStatus(completionPort, 0, 0, NULL);
        }
    }

    // 클라이언트 연결 정리
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        if (!clients.empty()) {
            LOG_INFO("클라이언트 연결 정리 중 (" + std::to_string(clients.size()) + "개)");
        }

        for (auto& pair : clients)
        {
            closesocket(pair.second->socket);
            delete pair.second;
        }

        clients.clear();
    }

    // 소켓 정리
    if (listenSocket != INVALID_SOCKET)
    {
        LOG_INFO("리스닝 소켓 정리");
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }

    // IOCP 정리
    if (completionPort != NULL)
    {
        LOG_INFO("IOCP 핸들 정리");
        CloseHandle(completionPort);
        completionPort = NULL;
    }

    LOG_INFO("윈속 정리");
    WSACleanup();

    LOG_INFO("서버 자원 정리 완료");
}

std::string IOCPServer::GetSocketErrorString(int error) const
{
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: 연결이 원격 호스트에 의해 재설정됨";
    case WSAECONNABORTED: return "WSAECONNABORTED: 소프트웨어가 연결 중단 발생";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: 연결 시간 초과";
    case WSAENETDOWN: return "WSAENETDOWN: 네트워크가 다운됨";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: 호스트에 도달할 수 없음";
    case WSAEINTR: return "WSAEINTR: 함수 호출이 중단됨";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: 리소스가 일시적으로 사용 불가";
    default: return "알 수 없는 오류: " + std::to_string(error);
    }
}

int IOCPServer::GetClientCount() const
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    return static_cast<int>(clients.size());
}