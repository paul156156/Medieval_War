#include "IOCPServer.h"
#include "Logger.h"

ClientSession* IOCPServer::CreateSession(SOCKET socket, SOCKADDR_IN addr)
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
    float now = GetTickCount64() / 1000.0f;
    client->LastPingTime = now;
    client->LastPongTime = now;

    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    //if (SpawnPositions.empty())
    //{
    //    SetupSpawnPositions();
    //}
    //client->Position = SpawnPositions[(client->id - 1) % SpawnPositions.size()];
    //client->LastPosition = client->Position;

    return client;
}

void IOCPServer::InitializeNewClientSession(ClientSession* client)
{
    SendClientId(client);
    //SendInitialPosition(client);
    BroadcastNewPlayerJoin(client);
    SendExistingPlayerList(client);
}

void IOCPServer::RemoveClient(int clientId)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    auto it = clients.find(clientId);
    if (it != clients.end())
    {
        ClientSession* client = it->second;

        shutdown(client->socket, SD_BOTH);

        closesocket(client->socket);
        LOG_INFO("클라이언트 연결 끊김 (ID: " + std::to_string(client->id) + ")");
        
        // 다른 클라이언트들에게 연결 끊김 알림
        NotifyClientDisconnect(clientId);

        clients.erase(it);
        delete client;
    }
    else {
        LOG_WARNING("존재하지 않는 클라이언트 ID를 제거하려고 시도: " +
            std::to_string(clientId));
    }
}

void IOCPServer::NotifyClientDisconnect(int disconnectedClientId)
{
    PositionPacket packet;
    packet.Header.PacketType = EPacketType::DISCONNECT;
    packet.Header.PacketSize = sizeof(DisconnectPacket);
    packet.ClientId = disconnectedClientId;

    int notifyCount = 0;
    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;
        // 연결이 끊긴 클라이언트는 제외
        if (targetClient->id != disconnectedClientId)
        {
            // 비동기 전송
            SendPacket(targetClient, &packet, sizeof(packet), "NotifyClientDisconnect");
            notifyCount++;
        }
    }

    LOG_INFO("클라이언트 연결 끊김 알림(ID: " + std::to_string(disconnectedClientId) +
        ") - 수신자 수: " + std::to_string(notifyCount));
}
