#include "ClientManager.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"

ClientManager::ClientManager() : nextClientId(1) {
    SetupSpawnPositions();
    LOG_INFO("Ŭ���̾�Ʈ �Ŵ��� �ʱ�ȭ �Ϸ�");
}

ClientManager::~ClientManager() {
    std::unique_lock<std::shared_mutex> lock(clientsMutex);

    LOG_INFO("Ŭ���̾�Ʈ �Ŵ��� ���� ���� - �� Ŭ���̾�Ʈ: " + std::to_string(clients.size()));

    for (auto& pair : clients) {
        if (pair.second) {
            NetworkSessionManager::DisconnectClient(pair.second);
            delete pair.second;
        }
    }
    clients.clear();

    LOG_INFO("Ŭ���̾�Ʈ �Ŵ��� ���� �Ϸ�");
}

ClientSession* ClientManager::CreateSession(SOCKET socket, SOCKADDR_IN addr) {
    // ���ο� Ŭ���̾�Ʈ ���� ����
    ClientSession* client = new ClientSession();

    int clientId = nextClientId.fetch_add(1);
    client->Initialize(socket, addr, clientId);

    // ���� ��ġ ����
    client->Position = GetSpawnPosition(clientId);
    client->PreviousPosition = client->Position;

    // Ŭ���̾�Ʈ �ʿ� �߰�
    {
        std::unique_lock<std::shared_mutex> lock(clientsMutex);
        clients[clientId] = client;
    }

    // Ŭ���̾�Ʈ ���� �α�
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), ipStr, INET_ADDRSTRLEN);

    LOG_INFO("�� Ŭ���̾�Ʈ ���� ������ - ID: " + std::to_string(clientId) +
        ", IP: " + std::string(ipStr) +
        ", Port: " + std::to_string(ntohs(addr.sin_port)) +
        ", ���� ��ġ: (" + std::to_string(client->Position.X) +
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
        LOG_INFO("Ŭ���̾�Ʈ ���� ���� - ID: " + std::to_string(clientId));

        // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� �˸�
        NotifyClientDisconnect(clientId);

        // ��Ʈ��ũ ���� ����
        NetworkSessionManager::DisconnectClient(clientToRemove);

        // �޸� ����
        delete clientToRemove;

        LOG_INFO("Ŭ���̾�Ʈ ���� �Ϸ� - ID: " + std::to_string(clientId));
        LogClientStats();
    }
    else {
        LOG_WARNING("�������� �ʴ� Ŭ���̾�Ʈ ID ���� �õ�: " + std::to_string(clientId));
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

    LOG_INFO("Ŭ���̾�Ʈ ���� ���� �˸� �Ϸ� - ID: " + std::to_string(disconnectedClientId) +
        ", �˸� ���: " + std::to_string(notifyCount) + "��");
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

    // Ÿ�Ӿƿ��� Ŭ���̾�Ʈ�� ����
    for (int clientId : clientsToRemove) {
        LOG_WARNING("Ŭ���̾�Ʈ Ÿ�Ӿƿ����� ���� - ID: " + std::to_string(clientId));
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

    LOG_DEBUG("��ε�ĳ��Ʈ �Ϸ� - ���ؽ�Ʈ: " + std::string(context ? context : "Unknown") +
        ", ����: " + std::to_string(broadcastCount) +
        ", ����: " + std::to_string(failedCount));
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

    LOG_DEBUG("������ ��ε�ĳ��Ʈ �Ϸ� - ���ؽ�Ʈ: " + std::string(context ? context : "Unknown") +
        ", ���: " + std::to_string(clientIds.size()) +
        ", ����: " + std::to_string(broadcastCount) +
        ", ����: " + std::to_string(failedCount));
}

Vec3 ClientManager::GetSpawnPosition(int clientId) const {
    if (spawnPositions.empty()) {
        LOG_WARNING("���� ��ġ�� �������� ����. �⺻ ��ġ ��ȯ");
        return Vec3(0.0f, 0.0f, 90.0f);
    }

    size_t index = (clientId - 1) % spawnPositions.size();
    return spawnPositions[index];
}

void ClientManager::SetupSpawnPositions() {
    InitializeDefaultSpawnPositions();
    LOG_INFO("���� ��ġ ���� �Ϸ� - �� " + std::to_string(spawnPositions.size()) + "��");
}

void ClientManager::InitializeDefaultSpawnPositions() {
    spawnPositions.clear();

    // �⺻ ���� ��ġ�� (���� ��ġ)
    const float radius = 500.0f;
    const int spawnCount = 8;
    const float groundLevel = 90.0f;

    for (int i = 0; i < spawnCount; ++i) {
        float angle = (2.0f * 3.14159265f * i) / spawnCount;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        spawnPositions.emplace_back(x, y, groundLevel);
    }

    // �߾� ���� ��ġ�� �߰�
    spawnPositions.emplace_back(0.0f, 0.0f, groundLevel);
}

bool ClientManager::IsValidClientId(int clientId) const {
    return clientId > 0 && clientId < nextClientId.load();
}

void ClientManager::LogClientStats() const {
    int totalClients = GetClientCount();
    int activeClients = GetActiveClientCount();

    LOG_INFO("Ŭ���̾�Ʈ ��� - ��ü: " + std::to_string(totalClients) +
        ", Ȱ��: " + std::to_string(activeClients));
}