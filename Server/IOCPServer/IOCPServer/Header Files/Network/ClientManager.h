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

    // Ŭ���̾�Ʈ ���� ����
    ClientSession* CreateSession(SOCKET socket, SOCKADDR_IN addr);
    void RemoveClient(int clientId);
    ClientSession* GetClient(int clientId);

    // ���� ���� ����
    void NotifyClientDisconnect(int disconnectedClientId);
    void CleanupTimedOutClients();

    // ������
    std::unordered_map<int, ClientSession*>& GetClients();
    const std::unordered_map<int, ClientSession*>& GetClients() const;
    std::shared_mutex& GetClientsMutex();

    // ���
    int GetClientCount() const;
    int GetActiveClientCount() const;
    std::vector<int> GetAllClientIds() const;

    // ��ε�ĳ��Ʈ
    void BroadcastToAll(const void* data, size_t size, const char* context, int excludeClientId = -1);
    void BroadcastToClients(const std::vector<int>& clientIds, const void* data, size_t size, const char* context);

    // ���� ��ġ ����
    Vec3 GetSpawnPosition(int clientId) const;

private:
    // Ŭ���̾�Ʈ �����̳�
    std::unordered_map<int, ClientSession*> clients;
    mutable std::shared_mutex clientsMutex;

    // ID ����
    std::atomic<int> nextClientId;

    // ���� ��ġ
    std::vector<Vec3> spawnPositions;

    // �ʱ�ȭ
    void SetupSpawnPositions();
    void InitializeDefaultSpawnPositions();

    // ��ƿ��Ƽ
    bool IsValidClientId(int clientId) const;
    void LogClientStats() const;
};