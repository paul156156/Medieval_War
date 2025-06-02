#include "IOCPServer.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include <iostream>

IOCPServer::IOCPServer() : isRunning(false), isInitialized(false) {
    Logger::GetInstance().Initialize();
    LOG_INFO("IOCP 서버 인스턴스 생성됨");

    // 컴포넌트 초기화
    networkManager = std::make_unique<NetworkManager>();
    clientManager = std::make_unique<ClientManager>();
    gameUpdater = std::make_unique<GameUpdater>();
}

IOCPServer::~IOCPServer() {
    LOG_INFO("IOCP 서버 소멸자 호출됨");
    CleanUp();
}

bool IOCPServer::Initialize(int port) {
    LOG_INFO("서버 초기화 시작 (포트: " + std::to_string(port) + ")");

    config.port = port;

    // 네트워크 매니저 초기화
    if (!networkManager->InitializeSocket(port)) {
        LOG_ERROR("소켓 초기화 실패");
        return false;
    }

    if (!networkManager->SetupIOCP()) {
        LOG_ERROR("IOCP 설정 실패");
        return false;
    }

    // 워커 스레드 개수 결정
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    config.workerThreadCount = sysInfo.dwNumberOfProcessors;

    LOG_INFO("CPU 코어 수: " + std::to_string(sysInfo.dwNumberOfProcessors) +
        ", 워커 스레드 수: " + std::to_string(config.workerThreadCount));

    LOG_INFO("서버 실행 시작");
    isRunning = true;

    // 워커 스레드 시작
    StartWorkerThreads();

    // 게임 업데이터 설정
    gameUpdater->SetUpdateRate(config.targetFPS);
    gameUpdater->SetPhysicsEnabled(true);

    isInitialized = true;
    LogServerInfo();
    LOG_INFO("서버 초기화 완료");

    return true;
}

void IOCPServer::Run() {
    if (!isInitialized) {
        LOG_ERROR("서버가 초기화되지 않음");
        return;
    }

    //LOG_INFO("서버 실행 시작");
    //isRunning = true;

    SOCKET listenSocket = networkManager->GetListenSocket();
    uint64_t lastTick = GetTickCount64();
    uint64_t lastStatsTime = lastTick;

    // 논블로킹 모드 설정 확인
    u_long mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != NO_ERROR) {
        LOG_ERROR("리슨 소켓 논블로킹 설정 실패");
        return;
    }

    while (isRunning) {
        uint64_t frameStart = GetTickCount64();

        // 새 클라이언트 연결 처리
        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, nullptr, 0);

        if (clientSocket != INVALID_SOCKET) {
            if (clientManager->GetClientCount() < config.maxClients) {
                AcceptClient(clientSocket, clientAddr);
            }
            else {
                LOG_WARNING("최대 클라이언트 수 초과. 연결 거부됨");
                closesocket(clientSocket);
            }
        }

        // 게임 업데이트
        float deltaTime = (GetTickCount64() - lastTick) / 1000.0f;
        lastTick = GetTickCount64();
        Update(deltaTime);

        // 서버 통계 계산
        uint64_t frameEnd = GetTickCount64();
        uint64_t frameTime = frameEnd - frameStart;
        CalculateServerStats(frameTime);

        // 성능 통계 로깅 (5초마다)
        if (config.enableStats && (frameEnd - lastStatsTime) > 5000) {
            LogPerformanceStats();
            lastStatsTime = frameEnd;
        }

        // 프레임 레이트 제한
        const uint64_t targetFrameTime = static_cast<uint64_t>(1000.0f / config.targetFPS);
        if (frameTime < targetFrameTime) {
            Sleep(static_cast<DWORD>(targetFrameTime - frameTime));
        }
    }

    LOG_INFO("서버 메인 루프 종료");
}

void IOCPServer::Stop() {
    LOG_INFO("서버 중지 요청됨");
    isRunning = false;
}

void IOCPServer::CleanUp() {
    LOG_INFO("서버 정리 시작");

    isRunning = false;

    // 워커 스레드 정리
    StopWorkerThreads();

    // 컴포넌트 정리 (순서 중요)
    if (clientManager) {
        clientManager.reset();
        LOG_INFO("클라이언트 매니저 정리 완료");
    }

    if (networkManager) {
        networkManager.reset();
        LOG_INFO("네트워크 매니저 정리 완료");
    }

    if (gameUpdater) {
        gameUpdater.reset();
        LOG_INFO("게임 업데이터 정리 완료");
    }

    isInitialized = false;
    LOG_INFO("서버 정리 완료");
}

void IOCPServer::AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr) {
    // 소켓 옵션 설정
    NetworkSessionManager::SetSocketOptions(clientSocket);

    // 클라이언트 세션 생성
    ClientSession* newClient = clientManager->CreateSession(clientSocket, clientAddr);
    if (!newClient) {
        LOG_ERROR("클라이언트 세션 생성 실패");
        closesocket(clientSocket);
        return;
    }

    // IOCP에 등록
    if (!NetworkSessionManager::RegisterToIOCP(networkManager->GetCompletionPort(), newClient)) {
        LOG_ERROR("IOCP 등록 실패 - 클라이언트 ID: " + std::to_string(newClient->id));
        clientManager->RemoveClient(newClient->id);
        return;
    }

    // 초기 수신 요청
    if (!NetworkSessionManager::PostRecv(newClient)) {
        LOG_ERROR("초기 수신 요청 실패 - 클라이언트 ID: " + std::to_string(newClient->id));
        clientManager->RemoveClient(newClient->id);
        return;
    }

    // 새 클라이언트 초기화
    InitializeNewClient(newClient);

    LOG_INFO("새 클라이언트 연결 완료 - ID: " + std::to_string(newClient->id) +
        ", 총 클라이언트: " + std::to_string(clientManager->GetClientCount()));
}

void IOCPServer::InitializeNewClient(ClientSession* client) {
    if (!client) return;

    // 클라이언트 ID 전송
    PacketDispatcher::SendClientId(client);

    // 초기 위치 전송
    //PacketDispatcher::SendInitialPosition(client);

    // 기존 플레이어들에게 새 플레이어 알림
    auto& clients = clientManager->GetClients();
    {
        std::shared_lock<std::shared_mutex> lock(clientManager->GetClientsMutex());
        if (clients.size() > 1) {
            PacketDispatcher::SendExistingPlayer(client, clients);
            PacketDispatcher::BroadcastNewPlayer(client, clients);
        }
    }
}

void IOCPServer::Update(float deltaTime) {
    // 클라이언트 업데이트
    auto& clients = clientManager->GetClients();
    auto& mutex = clientManager->GetClientsMutex();
    gameUpdater->UpdateClients(deltaTime, clients, mutex);

    // 타임아웃된 클라이언트 정리
    clientManager->CleanupTimedOutClients();
}

void IOCPServer::StartWorkerThreads() {
    LOG_INFO("워커 스레드 시작 - 개수: " + std::to_string(config.workerThreadCount));

    for (int i = 0; i < config.workerThreadCount; ++i) {
        HANDLE hThread = CreateThread(nullptr, 0, WorkerThreadProc, this, 0, nullptr);
        if (hThread == NULL) {
            LOG_ERROR("워커 스레드 생성 실패 - 인덱스: " + std::to_string(i) +
                ", 에러: " + std::to_string(GetLastError()));
            continue;
        }

        CloseHandle(hThread);
        LOG_DEBUG("워커 스레드 #" + std::to_string(i + 1) + " 생성됨");
    }
}

void IOCPServer::StopWorkerThreads() {
    LOG_INFO("워커 스레드 중지 시작");

    HANDLE iocp = networkManager->GetCompletionPort();
    if (iocp) {
        // 워커 스레드에 종료 신호 전송
        for (int i = 0; i < config.workerThreadCount; ++i) {
            PostQueuedCompletionStatus(iocp, 0, 0, nullptr);
        }
    }

    // 잠시 대기하여 스레드들이 정리될 시간을 줌
    Sleep(100);

    LOG_INFO("워커 스레드 중지 완료");
}

DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg) {
    IOCPServer* server = reinterpret_cast<IOCPServer*>(arg);
    server->WorkerThread();
    return 0;
}

void IOCPServer::WorkerThread() {
    DWORD threadId = GetCurrentThreadId();
    LOG_INFO("워커 스레드 시작 - ThreadID: " + std::to_string(threadId));

    HANDLE iocp = networkManager->GetCompletionPort();

    while (isRunning) {
        DWORD bytesTransferred = 0;
        ULONG_PTR completionKey = 0;
        OVERLAPPED* overlapped = nullptr;

        BOOL result = GetQueuedCompletionStatus(
            iocp,
            &bytesTransferred,
            &completionKey,
            &overlapped,
            INFINITE
        );

        // 서버 종료 신호
        if (completionKey == 0 && overlapped == nullptr) {
            LOG_DEBUG("워커 스레드 종료 신호 수신 - ThreadID: " + std::to_string(threadId));
            break;
        }

        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // 연결 종료 또는 에러 처리
        if (!result || bytesTransferred == 0) {
            if (client) {
                LOG_INFO("클라이언트 연결 종료 감지 - ID: " + std::to_string(client->id));
                clientManager->RemoveClient(client->id);
            }

            // 동적 할당된 OVERLAPPED 정리
            if (overlapped && client && overlapped != &client->overlapped) {
                delete overlapped;
            }
            continue;
        }

        // 데이터 수신 처리
        if (client && overlapped == &client->overlapped) {
            // Ping 시간 갱신
            client->LastPingTime = GetTickCount64() / 1000.0f;

            // 패킷 처리
            if (bytesTransferred >= sizeof(PacketHeader)) {
                PacketDispatcher::ProcessReceivedPacket(client, client->recvBuffer, bytesTransferred);
            }

            // 다음 수신 요청
            NetworkSessionManager::PostRecv(client);
        }
        // 전송 완료 처리
        else if (overlapped) {
            delete overlapped;
        }
    }

    LOG_INFO("워커 스레드 종료 - ThreadID: " + std::to_string(threadId));
}

void IOCPServer::CalculateServerStats(uint64_t frameTime) {
    stats.frameCount++;
    stats.averageFrameTime = stats.averageFrameTime * 0.95f + frameTime * 0.05f;

    uint64_t currentTime = GetTickCount64();
    if (currentTime - stats.lastStatsUpdate >= 1000) {
        stats.fps = stats.frameCount * 1000.0f / (currentTime - stats.lastStatsUpdate);
        stats.frameCount = 0;
        stats.lastStatsUpdate = currentTime;
    }
}

int IOCPServer::GetClientCount() const {
    return clientManager ? clientManager->GetClientCount() : 0;
}

float IOCPServer::GetServerFPS() const {
    return stats.fps;
}

bool IOCPServer::IsRunning() const {
    return isRunning.load();
}

void IOCPServer::LogServerInfo() const {
    LOG_INFO("=== 서버 정보 ===");
    LOG_INFO("포트: " + std::to_string(config.port));
    LOG_INFO("워커 스레드: " + std::to_string(config.workerThreadCount));
    LOG_INFO("목표 FPS: " + std::to_string(config.targetFPS));
    LOG_INFO("최대 클라이언트: " + std::to_string(config.maxClients));
    LOG_INFO("================");
}

void IOCPServer::LogPerformanceStats() const {
    int clientCount = GetClientCount();
    int updatedClients = gameUpdater->GetUpdatedClientCount();
    float avgUpdateTime = gameUpdater->GetAverageUpdateTime();

    LOG_INFO("=== 성능 통계 ===");
    LOG_INFO("서버 FPS: " + std::to_string(stats.fps));
    LOG_INFO("평균 프레임 시간: " + std::to_string(stats.averageFrameTime) + "ms");
    LOG_INFO("클라이언트 수: " + std::to_string(clientCount));
    LOG_INFO("업데이트된 클라이언트: " + std::to_string(updatedClients));
    LOG_INFO("평균 게임 업데이트 시간: " + std::to_string(avgUpdateTime) + "ms");
    LOG_INFO("===============");
}

std::string IOCPServer::GetServerStatus() const {
    std::string status = "서버 상태: ";
    status += isRunning ? "실행 중" : "중지됨";
    status += ", 클라이언트: " + std::to_string(GetClientCount());
    status += ", FPS: " + std::to_string(stats.fps);
    return status;
}