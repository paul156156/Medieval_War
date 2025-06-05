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

    // 서버 생명주기
    bool Initialize(int port);
    void Run();
    void Stop();
    void CleanUp();

    // 통계 및 정보
    int GetClientCount() const;
    float GetServerFPS() const;
    bool IsRunning() const;

private:
    // 핵심 컴포넌트
    std::unique_ptr<NetworkManager> networkManager;
    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<GameUpdater> gameUpdater;

    // 서버 상태
    std::atomic<bool> isRunning;
    std::atomic<bool> isInitialized;

    // 네트워크 처리
    void AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr);
    void InitializeNewClient(ClientSession* client);

    // 게임 루프
    void Update(float deltaTime);
    void CalculateServerStats(uint64_t frameTime);

    // 워커 스레드
    void StartWorkerThreads();
    void StopWorkerThreads();
    static DWORD WINAPI WorkerThreadProc(LPVOID arg);
    void WorkerThread();

    // 서버 통계
    struct ServerStats {
        float fps = 0.0f;
        float averageFrameTime = 0.0f;
        uint64_t frameCount = 0;
        uint64_t lastStatsUpdate = 0;
    } stats;

    // 설정
    struct ServerConfig {
        int port = 9000;
        int workerThreadCount = 0;
        float targetFPS = 60.0f;
        bool enableStats = true;
        int maxClients = 1000;
    } config;

    // 스레드 관리
    std::vector<std::thread> workerThreads;

    // 유틸리티
    void LogServerInfo() const;
    void LogPerformanceStats() const;
    std::string GetServerStatus() const;
};