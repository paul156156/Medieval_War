#pragma once
#include "ClientSession.h"
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

class ClientManager {
public:
    ClientManager();
    ~ClientManager();

    // 클라이언트 세션 관리
    ClientSession* CreateSession(SOCKET socket, SOCKADDR_IN addr);
    void RemoveClient(int clientId);
    ClientSession* GetClient(int clientId);

    // 연결 상태 관리
    void NotifyClientDisconnect(int disconnectedClientId);
    void CleanupTimedOutClients();

    // 접근자
    std::unordered_map<int, ClientSession*>& GetClients();
    const std::unordered_map<int, ClientSession*>& GetClients() const;
    std::shared_mutex& GetClientsMutex();

    // 통계
    int GetClientCount() const;
    int GetActiveClientCount() const;
    std::vector<int> GetAllClientIds() const;

    // 브로드캐스트
    void BroadcastToAll(const void* data, size_t size, const char* context, int excludeClientId = -1);
    void BroadcastToClients(const std::vector<int>& clientIds, const void* data, size_t size, const char* context);

    // 스폰 위치 관리
    Vec3 GetSpawnPosition(int clientId) const;

private:
    // 클라이언트 컨테이너
    std::unordered_map<int, ClientSession*> clients;
    mutable std::shared_mutex clientsMutex;

    // ID 관리
    std::atomic<int> nextClientId;

    // 스폰 위치
    std::vector<Vec3> spawnPositions;

    // 초기화
    void SetupSpawnPositions();
    void InitializeDefaultSpawnPositions();

    // 유틸리티
    bool IsValidClientId(int clientId) const;
    void LogClientStats() const;
};