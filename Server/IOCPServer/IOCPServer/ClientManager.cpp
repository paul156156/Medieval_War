#include "ClientManager.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"

ClientManager::ClientManager() : nextClientId(1) {
    SetupSpawnPositions();
    LOG_INFO("클라이언트 매니저 초기화 완료");
}

ClientManager::~ClientManager() {
    std::unique_lock<std::shared_mutex> lock(clientsMutex);

    LOG_INFO("클라이언트 매니저 정리 시작 - 총 클라이언트: " + std::to_string(clients.size()));

    for (auto& pair : clients) {
        if (pair.second) {
            NetworkSessionManager::DisconnectClient(pair.second);
            delete pair.second;
        }
    }
    clients.clear();

    LOG_INFO("클라이언트 매니저 정리 완료");
}

ClientSession* ClientManager::CreateSession(SOCKET socket, SOCKADDR_IN addr) {
    // 새로운 클라이언트 세션 생성
    ClientSession* client = new ClientSession();

    int clientId = nextClientId.fetch_add(1);
    client->Initialize(socket, addr, clientId);

    // 스폰 위치 설정
    client->Position = GetSpawnPosition(clientId);
    client->PreviousPosition = client->Position;

    // 클라이언트 맵에 추가
    {
        std::unique_lock<std::shared_mutex> lock(clientsMutex);
        clients[clientId] = client;
    }

    // 클라이언트 정보 로깅
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);

    LOG_INFO("새 클라이언트 세션 생성됨 - ID: " + std::to_string(clientId) +
        ", IP: " + std::string(ipStr) +
        ", Port: " + std::to_string(ntohs(addr.sin_port)) +
        ", 스폰 위치: (" + std::to_string(client->Position.X) +
        ", " + std::to_string(client->Position.Y) +
        ", " + std::to_string(client->Position.Z) + ")");

    LogClientStats();
    return client;
}

void ClientManager::RemoveClient(int clientId) {
    ClientSession* clientToRemove = nullptr;

    {
        std::unique_lock<std::shared_mutex> lock(clientsMutex);
        auto it = clients.find(clientId);
        if (it != clients.end()) {
            clientToRemove = it->second;
            clients.erase(it);
        }
    }

    if (clientToRemove) {
        LOG_INFO("클라이언트 제거 시작 - ID: " + std::to_string(clientId));

        // 다른 클라이언트들에게 연결 종료 알림
        NotifyClientDisconnect(clientId);

        // 네트워크 연결 정리
        NetworkSessionManager::DisconnectClient(clientToRemove);

        // 메모리 해제
        delete clientToRemove;

        LOG_INFO("클라이언트 제거 완료 - ID: " + std::to_string(clientId));
        LogClientStats();
    }
    else {
        LOG_WARNING("존재하지 않는 클라이언트 ID 제거 시도: " + std::to_string(clientId));
    }
}

ClientSession* ClientManager::GetClient(int clientId) {
    std::shared_lock<std::shared_mutex> lock(clientsMutex);
    auto it = clients.find(clientId);
    return (it != clients.end()) ? it->second : nullptr;
}

void ClientManager::NotifyClientDisconnect(int disconnectedClientId) {
    DisconnectPacket packet;
    packet.Header.PacketType = EPacketType::DISCONNECT;
    packet.Header.PacketSize = sizeof(DisconnectPacket);
    packet.ClientId = disconnectedClientId;

    int notifyCount = 0;

    {
        std::shared_lock<std::shared_mutex> lock(clientsMutex);
        for (const auto& pair : clients) {
            ClientSession* targetClient = pair.second;
            if (targetClient && targetClient->id != disconnectedClientId && targetClient->IsConnected()) {
                NetworkSessionManager::SendPacket(targetClient, &packet, sizeof(packet), "NotifyClientDisconnect");
                notifyCount++;
            }
        }
    }

    LOG_INFO("클라이언트 연결 종료 알림 완료 - ID: " + std::to_string(disconnectedClientId) +
        ", 알림 대상: " + std::to_string(notifyCount) + "명");
}

void ClientManager::CleanupTimedOutClients() {
    std::vector<int> clientsToRemove;
    float currentTime = GetTickCount64() / 1000.0f;

    {
        std::shared_lock<std::shared_mutex> lock(clientsMutex);
        for (const auto& pair : clients) {
            ClientSession* client = pair.second;
            if (client && client->IsTimedOut(currentTime)) {
                clientsToRemove.push_back(client->id);
            }
        }
    }

    // 타임아웃된 클라이언트들 제거
    for (int clientId : clientsToRemove) {
        LOG_WARNING("클라이언트 타임아웃으로 제거 - ID: " + std::to_string(clientId));
        RemoveClient(clientId);
    }
}

std::unordered_map<int, ClientSession*>& ClientManager::GetClients() {
    return clients;
}

const std::unordered_map<int, ClientSession*>& ClientManager::GetClients() const {
    return clients;
}

std::shared_mutex& ClientManager::GetClientsMutex() {
    return clientsMutex;
}

int ClientManager::GetClientCount() const {
    std::shared_lock<std::shared_mutex> lock(clientsMutex);
    return static_cast<int>(clients.size());
}

int ClientManager::GetActiveClientCount() const {
    std::shared_lock<std::shared_mutex> lock(clientsMutex);
    int activeCount = 0;
    for (const auto& pair : clients) {
        if (pair.second && pair.second->IsConnected()) {
            activeCount++;
        }
    }
    return activeCount;
}

std::vector<int> ClientManager::GetAllClientIds() const {
    std::shared_lock<std::shared_mutex> lock(clientsMutex);
    std::vector<int> clientIds;
    clientIds.reserve(clients.size());

    for (const auto& pair : clients) {
        clientIds.push_back(pair.first);
    }

    return clientIds;
}

void ClientManager::BroadcastToAll(const void* data, size_t size, const char* context, int excludeClientId) {
    int broadcastCount = 0;
    int failedCount = 0;

    {
        std::shared_lock<std::shared_mutex> lock(clientsMutex);
        for (const auto& pair : clients) {
            ClientSession* client = pair.second;
            if (client && client->id != excludeClientId && client->IsConnected()) {
                if (NetworkSessionManager::SendPacketSafe(client, data, size, context)) {
                    broadcastCount++;
                }
                else {
                    failedCount++;
                }
            }
        }
    }

    LOG_DEBUG("브로드캐스트 완료 - 컨텍스트: " + std::string(context ? context : "Unknown") +
        ", 성공: " + std::to_string(broadcastCount) +
        ", 실패: " + std::to_string(failedCount));
}

void ClientManager::BroadcastToClients(const std::vector<int>& clientIds, const void* data, size_t size, const char* context) {
    int broadcastCount = 0;
    int failedCount = 0;

    std::shared_lock<std::shared_mutex> lock(clientsMutex);
    for (int clientId : clientIds) {
        auto it = clients.find(clientId);
        if (it != clients.end() && it->second && it->second->IsConnected()) {
            if (NetworkSessionManager::SendPacketSafe(it->second, data, size, context)) {
                broadcastCount++;
            }
            else {
                failedCount++;
            }
        }
    }

    LOG_DEBUG("선택적 브로드캐스트 완료 - 컨텍스트: " + std::string(context ? context : "Unknown") +
        ", 대상: " + std::to_string(clientIds.size()) +
        ", 성공: " + std::to_string(broadcastCount) +
        ", 실패: " + std::to_string(failedCount));
}

Vec3 ClientManager::GetSpawnPosition(int clientId) const {
    if (spawnPositions.empty()) {
        LOG_WARNING("스폰 위치가 설정되지 않음. 기본 위치 반환");
        return Vec3(0.0f, 0.0f, 90.0f);
    }

    size_t index = (clientId - 1) % spawnPositions.size();
    return spawnPositions[index];
}

void ClientManager::SetupSpawnPositions() {
    InitializeDefaultSpawnPositions();
    LOG_INFO("스폰 위치 설정 완료 - 총 " + std::to_string(spawnPositions.size()) + "개");
}

void ClientManager::InitializeDefaultSpawnPositions() {
    spawnPositions.clear();

    // 기본 스폰 위치들 (원형 배치)
    const float radius = 500.0f;
    const int spawnCount = 8;
    const float groundLevel = 90.0f;

    for (int i = 0; i < spawnCount; ++i) {
        float angle = (2.0f * 3.14159265f * i) / spawnCount;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        spawnPositions.emplace_back(x, y, groundLevel);
    }

    // 중앙 스폰 위치도 추가
    spawnPositions.emplace_back(0.0f, 0.0f, groundLevel);
}

bool ClientManager::IsValidClientId(int clientId) const {
    return clientId > 0 && clientId < nextClientId.load();
}

void ClientManager::LogClientStats() const {
    int totalClients = GetClientCount();
    int activeClients = GetActiveClientCount();

    LOG_INFO("클라이언트 통계 - 전체: " + std::to_string(totalClients) +
        ", 활성: " + std::to_string(activeClients));
}