#pragma once
#include "NetworkManager.h"
#include "ClientManager.h"
#include "GameUpdater.h"
#include "PacketDispatcher.h"
#include <atomic>
#include <thread>
#include <vector>
#include <memory>

class IOCPServer {
public:
    IOCPServer();
    ~IOCPServer();

    // ���� �����ֱ�
    bool Initialize(int port);
    void Run();
    void Stop();
    void CleanUp();

    // ��� �� ����
    int GetClientCount() const;
    float GetServerFPS() const;
    bool IsRunning() const;

private:
    // �ٽ� ������Ʈ
    std::unique_ptr<NetworkManager> networkManager;
    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<GameUpdater> gameUpdater;

    // ���� ����
    std::atomic<bool> isRunning;
    std::atomic<bool> isInitialized;

    // ��Ʈ��ũ ó��
    void AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr);
    void InitializeNewClient(ClientSession* client);

    // ���� ����
    void Update(float deltaTime);
    void CalculateServerStats(uint64_t frameTime);

    // ��Ŀ ������
    void StartWorkerThreads();
    void StopWorkerThreads();
    static DWORD WINAPI WorkerThreadProc(LPVOID arg);
    void WorkerThread();

    // ���� ���
    struct ServerStats {
        float fps = 0.0f;
        float averageFrameTime = 0.0f;
        uint64_t frameCount = 0;
        uint64_t lastStatsUpdate = 0;
    } stats;

    // ����
    struct ServerConfig {
        int port = 9000;
        int workerThreadCount = 0;
        float targetFPS = 60.0f;
        bool enableStats = true;
        int maxClients = 1000;
    } config;

    // ������ ����
    std::vector<std::thread> workerThreads;

    // ��ƿ��Ƽ
    void LogServerInfo() const;
    void LogPerformanceStats() const;
    std::string GetServerStatus() const;
};