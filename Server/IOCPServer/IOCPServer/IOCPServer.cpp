#include "IOCPServer.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include <iostream>

IOCPServer::IOCPServer() : isRunning(false), isInitialized(false) {
    Logger::GetInstance().Initialize();
    LOG_INFO("IOCP ���� �ν��Ͻ� ������");

    // ������Ʈ �ʱ�ȭ
    networkManager = std::make_unique<NetworkManager>();
    clientManager = std::make_unique<ClientManager>();
    gameUpdater = std::make_unique<GameUpdater>();
}

IOCPServer::~IOCPServer() {
    LOG_INFO("IOCP ���� �Ҹ��� ȣ���");
    CleanUp();
}

bool IOCPServer::Initialize(int port) {
    LOG_INFO("���� �ʱ�ȭ ���� (��Ʈ: " + std::to_string(port) + ")");

    config.port = port;

    // ��Ʈ��ũ �Ŵ��� �ʱ�ȭ
    if (!networkManager->InitializeSocket(port)) {
        LOG_ERROR("���� �ʱ�ȭ ����");
        return false;
    }

    if (!networkManager->SetupIOCP()) {
        LOG_ERROR("IOCP ���� ����");
        return false;
    }

    // ��Ŀ ������ ���� ����
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    config.workerThreadCount = sysInfo.dwNumberOfProcessors;

    LOG_INFO("CPU �ھ� ��: " + std::to_string(sysInfo.dwNumberOfProcessors) +
        ", ��Ŀ ������ ��: " + std::to_string(config.workerThreadCount));

    LOG_INFO("���� ���� ����");
    isRunning = true;

    // ��Ŀ ������ ����
    StartWorkerThreads();

    // ���� �������� ����
    gameUpdater->SetUpdateRate(config.targetFPS);
    gameUpdater->SetPhysicsEnabled(true);

    isInitialized = true;
    LogServerInfo();
    LOG_INFO("���� �ʱ�ȭ �Ϸ�");

    return true;
}

void IOCPServer::Run() {
    if (!isInitialized) {
        LOG_ERROR("������ �ʱ�ȭ���� ����");
        return;
    }

    //LOG_INFO("���� ���� ����");
    //isRunning = true;

    SOCKET listenSocket = networkManager->GetListenSocket();
    uint64_t lastTick = GetTickCount64();
    uint64_t lastStatsTime = lastTick;

    // ����ŷ ��� ���� Ȯ��
    u_long mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != NO_ERROR) {
        LOG_ERROR("���� ���� ����ŷ ���� ����");
        return;
    }

    while (isRunning) {
        uint64_t frameStart = GetTickCount64();

        // �� Ŭ���̾�Ʈ ���� ó��
        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, nullptr, 0);

        if (clientSocket != INVALID_SOCKET) {
            if (clientManager->GetClientCount() < config.maxClients) {
                AcceptClient(clientSocket, clientAddr);
            }
            else {
                LOG_WARNING("�ִ� Ŭ���̾�Ʈ �� �ʰ�. ���� �źε�");
                closesocket(clientSocket);
            }
        }

        // ���� ������Ʈ
        float deltaTime = (GetTickCount64() - lastTick) / 1000.0f;
        lastTick = GetTickCount64();
        Update(deltaTime);

        // ���� ��� ���
        uint64_t frameEnd = GetTickCount64();
        uint64_t frameTime = frameEnd - frameStart;
        CalculateServerStats(frameTime);

        // ���� ��� �α� (5�ʸ���)
        if (config.enableStats && (frameEnd - lastStatsTime) > 5000) {
            LogPerformanceStats();
            lastStatsTime = frameEnd;
        }

        // ������ ����Ʈ ����
        const uint64_t targetFrameTime = static_cast<uint64_t>(1000.0f / config.targetFPS);
        if (frameTime < targetFrameTime) {
            Sleep(static_cast<DWORD>(targetFrameTime - frameTime));
        }
    }

    LOG_INFO("���� ���� ���� ����");
}

void IOCPServer::Stop() {
    LOG_INFO("���� ���� ��û��");
    isRunning = false;
}

void IOCPServer::CleanUp() {
    LOG_INFO("���� ���� ����");

    isRunning = false;

    // ��Ŀ ������ ����
    StopWorkerThreads();

    // ������Ʈ ���� (���� �߿�)
    if (clientManager) {
        clientManager.reset();
        LOG_INFO("Ŭ���̾�Ʈ �Ŵ��� ���� �Ϸ�");
    }

    if (networkManager) {
        networkManager.reset();
        LOG_INFO("��Ʈ��ũ �Ŵ��� ���� �Ϸ�");
    }

    if (gameUpdater) {
        gameUpdater.reset();
        LOG_INFO("���� �������� ���� �Ϸ�");
    }

    isInitialized = false;
    LOG_INFO("���� ���� �Ϸ�");
}

void IOCPServer::AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr) {
    // ���� �ɼ� ����
    NetworkSessionManager::SetSocketOptions(clientSocket);

    // Ŭ���̾�Ʈ ���� ����
    ClientSession* newClient = clientManager->CreateSession(clientSocket, clientAddr);
    if (!newClient) {
        LOG_ERROR("Ŭ���̾�Ʈ ���� ���� ����");
        closesocket(clientSocket);
        return;
    }

    // IOCP�� ���
    if (!NetworkSessionManager::RegisterToIOCP(networkManager->GetCompletionPort(), newClient)) {
        LOG_ERROR("IOCP ��� ���� - Ŭ���̾�Ʈ ID: " + std::to_string(newClient->id));
        clientManager->RemoveClient(newClient->id);
        return;
    }

    // �ʱ� ���� ��û
    if (!NetworkSessionManager::PostRecv(newClient)) {
        LOG_ERROR("�ʱ� ���� ��û ���� - Ŭ���̾�Ʈ ID: " + std::to_string(newClient->id));
        clientManager->RemoveClient(newClient->id);
        return;
    }

    // �� Ŭ���̾�Ʈ �ʱ�ȭ
    InitializeNewClient(newClient);

    LOG_INFO("�� Ŭ���̾�Ʈ ���� �Ϸ� - ID: " + std::to_string(newClient->id) +
        ", �� Ŭ���̾�Ʈ: " + std::to_string(clientManager->GetClientCount()));
}

void IOCPServer::InitializeNewClient(ClientSession* client) {
    if (!client) return;

    // Ŭ���̾�Ʈ ID ����
    PacketDispatcher::SendClientId(client);

    // �ʱ� ��ġ ����
    //PacketDispatcher::SendInitialPosition(client);

    // ���� �÷��̾�鿡�� �� �÷��̾� �˸�
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
    // Ŭ���̾�Ʈ ������Ʈ
    auto& clients = clientManager->GetClients();
    auto& mutex = clientManager->GetClientsMutex();
    gameUpdater->UpdateClients(deltaTime, clients, mutex);

    // Ÿ�Ӿƿ��� Ŭ���̾�Ʈ ����
    clientManager->CleanupTimedOutClients();
}

void IOCPServer::StartWorkerThreads() {
    LOG_INFO("��Ŀ ������ ���� - ����: " + std::to_string(config.workerThreadCount));

    for (int i = 0; i < config.workerThreadCount; ++i) {
        HANDLE hThread = CreateThread(nullptr, 0, WorkerThreadProc, this, 0, nullptr);
        if (hThread == NULL) {
            LOG_ERROR("��Ŀ ������ ���� ���� - �ε���: " + std::to_string(i) +
                ", ����: " + std::to_string(GetLastError()));
            continue;
        }

        CloseHandle(hThread);
        LOG_DEBUG("��Ŀ ������ #" + std::to_string(i + 1) + " ������");
    }
}

void IOCPServer::StopWorkerThreads() {
    LOG_INFO("��Ŀ ������ ���� ����");

    HANDLE iocp = networkManager->GetCompletionPort();
    if (iocp) {
        // ��Ŀ �����忡 ���� ��ȣ ����
        for (int i = 0; i < config.workerThreadCount; ++i) {
            PostQueuedCompletionStatus(iocp, 0, 0, nullptr);
        }
    }

    // ��� ����Ͽ� ��������� ������ �ð��� ��
    Sleep(100);

    LOG_INFO("��Ŀ ������ ���� �Ϸ�");
}

DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg) {
    IOCPServer* server = reinterpret_cast<IOCPServer*>(arg);
    server->WorkerThread();
    return 0;
}

void IOCPServer::WorkerThread() {
    DWORD threadId = GetCurrentThreadId();
    LOG_INFO("��Ŀ ������ ���� - ThreadID: " + std::to_string(threadId));

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

        // ���� ���� ��ȣ
        if (completionKey == 0 && overlapped == nullptr) {
            LOG_DEBUG("��Ŀ ������ ���� ��ȣ ���� - ThreadID: " + std::to_string(threadId));
            break;
        }

        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // ���� ���� �Ǵ� ���� ó��
        if (!result || bytesTransferred == 0) {
            if (client) {
                LOG_INFO("Ŭ���̾�Ʈ ���� ���� ���� - ID: " + std::to_string(client->id));
                clientManager->RemoveClient(client->id);
            }

            // ���� �Ҵ�� OVERLAPPED ����
            if (overlapped && client && overlapped != &client->overlapped) {
                delete overlapped;
            }
            continue;
        }

        // ������ ���� ó��
        if (client && overlapped == &client->overlapped) {
            // Ping �ð� ����
            client->LastPingTime = GetTickCount64() / 1000.0f;

            // ��Ŷ ó��
            if (bytesTransferred >= sizeof(PacketHeader)) {
                PacketDispatcher::ProcessReceivedPacket(client, client->recvBuffer, bytesTransferred);
            }

            // ���� ���� ��û
            NetworkSessionManager::PostRecv(client);
        }
        // ���� �Ϸ� ó��
        else if (overlapped) {
            delete overlapped;
        }
    }

    LOG_INFO("��Ŀ ������ ���� - ThreadID: " + std::to_string(threadId));
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
    LOG_INFO("=== ���� ���� ===");
    LOG_INFO("��Ʈ: " + std::to_string(config.port));
    LOG_INFO("��Ŀ ������: " + std::to_string(config.workerThreadCount));
    LOG_INFO("��ǥ FPS: " + std::to_string(config.targetFPS));
    LOG_INFO("�ִ� Ŭ���̾�Ʈ: " + std::to_string(config.maxClients));
    LOG_INFO("================");
}

void IOCPServer::LogPerformanceStats() const {
    int clientCount = GetClientCount();
    int updatedClients = gameUpdater->GetUpdatedClientCount();
    float avgUpdateTime = gameUpdater->GetAverageUpdateTime();

    LOG_INFO("=== ���� ��� ===");
    LOG_INFO("���� FPS: " + std::to_string(stats.fps));
    LOG_INFO("��� ������ �ð�: " + std::to_string(stats.averageFrameTime) + "ms");
    LOG_INFO("Ŭ���̾�Ʈ ��: " + std::to_string(clientCount));
    LOG_INFO("������Ʈ�� Ŭ���̾�Ʈ: " + std::to_string(updatedClients));
    LOG_INFO("��� ���� ������Ʈ �ð�: " + std::to_string(avgUpdateTime) + "ms");
    LOG_INFO("===============");
}

std::string IOCPServer::GetServerStatus() const {
    std::string status = "���� ����: ";
    status += isRunning ? "���� ��" : "������";
    status += ", Ŭ���̾�Ʈ: " + std::to_string(GetClientCount());
    status += ", FPS: " + std::to_string(stats.fps);
    return status;
}