// ClientManager.cpp
#include "ClientManager.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"
#include <WinSock2.h>
#include <WS2tcpip.h>


ClientManager::ClientManager() : nextClientId(1) {
    SetupSpawnPositions();
}

ClientManager::~ClientManager() {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto& pair : clients) {
        closesocket(pair.second->socket);
        delete pair.second;
    }
    clients.clear();
}

ClientSession* ClientManager::CreateSession(SOCKET socket, SOCKADDR_IN addr)
{
    ClientSession* client = new ClientSession();
    client->socket = socket;
    client->addr = addr;
    client->id = nextClientId++;
    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);
    client->State = EPlayerState::IDLE;
    client->PreviousState = client->State;
    client->Rotation = { 0.0f, 0.0f, 0.0f };
    client->LastUpdateTime = GetTickCount64() / 1000.0f;
    client->LastPingTime = client->LastUpdateTime;
    client->LastPongTime = client->LastUpdateTime;

    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    client->Position = SpawnPositions[(client->id - 1) % SpawnPositions.size()];
    client->LastPosition = client->Position;

    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients[client->id] = client;
    }

    return client;
}

void ClientManager::RemoveClient(int clientId)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = clients.find(clientId);
    if (it != clients.end()) {
        ClientSession* client = it->second;
        shutdown(client->socket, SD_BOTH);
        closesocket(client->socket);
        delete client;
        clients.erase(it);
        NotifyClientDisconnect(clientId);
        LOG_INFO("클라이언트 제거됨: ID " + std::to_string(clientId));
    }
    else {
        LOG_WARNING("존재하지 않는 클라이언트 ID 제거 시도: " + std::to_string(clientId));
    }
}

void ClientManager::NotifyClientDisconnect(int disconnectedClientId)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    PositionPacket packet;
    packet.Header.PacketType = EPacketType::DISCONNECT;
    packet.Header.PacketSize = sizeof(DisconnectPacket);
    packet.ClientId = disconnectedClientId;

    for (const auto& pair : clients) {
        ClientSession* targetClient = pair.second;
        if (targetClient->id != disconnectedClientId) {
            NetworkSessionManager::SendPacket(targetClient, &packet, sizeof(packet), "NotifyClientDisconnect");
        }
    }
    LOG_INFO("클라이언트 연결 종료 알림 - ID: " + std::to_string(disconnectedClientId));
}

std::unordered_map<int, ClientSession*>& ClientManager::GetClients() {
    return clients;
}

std::mutex& ClientManager::GetClientsMutex() {
    return clientsMutex;
}

void ClientManager::SetupSpawnPositions()
{
    SpawnPositions.push_back({ 0.0f, 0.0f, 90.0f });
    SpawnPositions.push_back({ 300.0f, 0.0f, 90.0f });
    SpawnPositions.push_back({ -300.0f, 0.0f, 90.0f });
    SpawnPositions.push_back({ 0.0f, 300.0f, 90.0f });
    SpawnPositions.push_back({ 0.0f, -300.0f, 90.0f });
}