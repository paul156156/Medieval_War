// PacketDispatcher.cpp
#include "Logger.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"
#include <mutex>
#include <unordered_map>
#include <WinSock2.h>
#include <WS2tcpip.h>


void PacketDispatcher::SendClientId(ClientSession* client)
{
    ClientIdPacket packet;
    packet.Header.PacketType = EPacketType::CLIENT_ID;
    packet.Header.PacketSize = sizeof(ClientIdPacket);
    packet.ClientId = client->id;

    NetworkSessionManager::SendPacket(client, &packet, sizeof(packet), "SendClientId");
    LOG_INFO("�� Ŭ���̾�Ʈ���� ID " + std::to_string(client->id) + " ���۵�");
}

void PacketDispatcher::SendInitialPosition(ClientSession* client)
{
    PositionPacket packet;
    packet.Header.PacketType = EPacketType::PLAYER_INIT_INFO;
    packet.Header.PacketSize = sizeof(PositionPacket);
    packet.ClientId = client->id;
    packet.Position = client->Position;
    packet.Velocity = client->Velocity;
    packet.State = client->State;

    NetworkSessionManager::SendPacket(client, &packet, sizeof(packet), "SendInitialPosition");
    LOG_INFO("�ʱ� ��ġ ���� ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
}

void PacketDispatcher::BroadcastNewPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients)
{
    for (const auto& pair : clients)
    {
        ClientSession* target = pair.second;
        if (target->id == newClient->id) continue;

        PositionPacket packet;
        packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
        packet.Header.PacketSize = sizeof(PositionPacket);
        packet.ClientId = newClient->id;
        packet.Position = newClient->Position;
        packet.Velocity = newClient->Velocity;
        packet.State = newClient->State;

        NetworkSessionManager::SendPacket(target, &packet, sizeof(packet), "BroadcastNewPlayer");
    }
    LOG_INFO("�� �÷��̾� ���� ��ε�ĳ��Ʈ �Ϸ� - ID: " + std::to_string(newClient->id));
}

void PacketDispatcher::SendExistingPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients)
{
    for (const auto& pair : clients)
    {
        ClientSession* existing = pair.second;
        if (existing->id == newClient->id) continue;

        PositionPacket packet;
        packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
        packet.Header.PacketSize = sizeof(PositionPacket);
        packet.ClientId = existing->id;
        packet.Position = existing->Position;
        packet.Velocity = existing->Velocity;
        packet.State = existing->State;

        NetworkSessionManager::SendPacket(newClient, &packet, sizeof(packet), "SendExistingPlayers");
    }
    LOG_INFO("���� �÷��̾� ���� ���� �Ϸ� - ��� ID: " + std::to_string(newClient->id));
}

void PacketDispatcher::SendPong(ClientSession* client)
{
    PongPacket pong;
    pong.Header.PacketType = EPacketType::PONG;
    pong.Header.PacketSize = sizeof(PongPacket);
    pong.ClientId = client->id;
    pong.PingTime = GetTickCount64();
    client->LastPongTime = pong.PingTime / 1000.0f;

    NetworkSessionManager::SendPacket(client, &pong, sizeof(pong), "SendPong");
    LOG_DEBUG("Pong ���� - ClientId: " + std::to_string(client->id));
}