#include "IOCPServer.h"
#include "Logger.h"
#include "PacketTypes.h"

void IOCPServer::SendClientId(ClientSession* client)
{
    ClientIdPacket packet;
    packet.Header.PacketType = EPacketType::CLIENT_ID;
    packet.Header.PacketSize = sizeof(ClientIdPacket);
    packet.ClientId = client->id;

    SendPacket(client, &packet, sizeof(packet), "SendClientId");

    LOG_INFO("�� Ŭ���̾�Ʈ���� ID " + std::to_string(client->id) + " ���۵�");
}

void IOCPServer::SendInitialPosition(ClientSession* client)
{
    PositionPacket packet;
    packet.Header.PacketType = EPacketType::PLAYER_INIT_INFO;
    packet.Header.PacketSize = sizeof(PositionPacket);
    packet.ClientId = client->id;
    packet.Position = client->Position;
    packet.Velocity = client->Velocity;
    packet.State = client->State;

    SendPacket(client, &packet, sizeof(packet), "SendInitialPosition");

    LOG_INFO("�ʱ� ��ġ ���� ���۵� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
        ", ��ġ: X=" + std::to_string(client->Position.X) +
        ", Y=" + std::to_string(client->Position.Y) +
        ", Z=" + std::to_string(client->Position.Z));
}

void IOCPServer::BroadcastNewPlayerJoin(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;

        // �ڽſ��Դ� �������� ����
        if (targetClient->id == newClient->id)
        {
            continue;
        }

        // �� �÷��̾� ���� ��Ŷ ����
        PositionPacket packet;
        packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
        packet.Header.PacketSize = sizeof(PositionPacket);
        packet.ClientId = newClient->id;
        packet.Position = newClient->Position;
        packet.Velocity = newClient->Velocity;
        packet.State = newClient->State;

        // �񵿱� ����
        SendPacket(targetClient, &packet, sizeof(packet), "BroadcastNewPlayer");
    }

    LOG_INFO("�� �÷��̾� ����(ID: " + std::to_string(newClient->id) +
        ") ��ε�ĳ��Ʈ - ������ ��: " +
        std::to_string(clients.size() - 1));
}

void IOCPServer::SendExistingPlayerList(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    int sentCount = 0;

    for (const auto& pair : clients)
    {
        ClientSession* existingClient = pair.second;

        // �ڽ��� ����
        if (existingClient->id == newClient->id)
        {
            continue;
        }

        // ���� �÷��̾� ���� ��Ŷ ����
        PositionPacket packet;
        packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
        packet.Header.PacketSize = sizeof(PositionPacket);
        packet.ClientId = existingClient->id;
        packet.Position = existingClient->Position;
        packet.Velocity = existingClient->Velocity;
        packet.State = existingClient->State;

        // �񵿱� ����
        SendPacket(newClient, &packet, sizeof(packet), "SendExistingPlayers");
        sentCount++;
    }

    LOG_INFO("���� �÷��̾� ���� " + std::to_string(sentCount) +
        "���� �� Ŭ���̾�Ʈ(ID: " + std::to_string(newClient->id) +
        ")���� ���۵�");
}

void IOCPServer::ProcessPacket(ClientSession* client, char* data, int length)
{
    if (length < sizeof(PacketHeader))
    {
        LOG_WARNING("�߸��� ��Ŷ ũ��: " + std::to_string(length) +
            " ����Ʈ (�ּ� " + std::to_string(sizeof(PacketHeader)) +
            " ����Ʈ �ʿ�), Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return;
    }

    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    // ��Ŷ Ÿ�� ��ȿ�� �˻�
    if (static_cast<int>(header->PacketType) < 0 ||
        static_cast<int>(header->PacketType) > 7) {
        LOG_WARNING("�߸��� ��Ŷ Ÿ��: " + std::to_string(static_cast<int>(header->PacketType)) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return;
    }

    switch (header->PacketType)
    {
    case EPacketType::PING:
    {
        if (length >= sizeof(PingPacket))
        {
            PingPacket* pingPacket = reinterpret_cast<PingPacket*>(data);
            client->LastPingTime = GetTickCount64() / 1000.0f;  // �����ð����� ����

            PongPacket pongPacket;
            pongPacket.Header.PacketType = EPacketType::PONG;
            pongPacket.Header.PacketSize = sizeof(PongPacket);
            pongPacket.ClientId = pingPacket->ClientId;
            pongPacket.PingTime = pingPacket->PingTime;

            SendPacket(client, &pongPacket, sizeof(pongPacket), "SendPong");

            LOG_DEBUG("[����] PingPacket ���� - ClientId: " + std::to_string(client->id));
        }
        else
        {
            LOG_WARNING("[ProcessPacket] �߸��� PING ��Ŷ ũ�� ����");
        }
    }
    break;
    case EPacketType::PLAYER_INPUT_INFO:
    {
        if (length >= sizeof(InputPacket))
        {
            InputPacket* inputPacket = reinterpret_cast<InputPacket*>(data);
            HandleInputPacket(client, inputPacket);
        }
        else
        {
            LOG_ERROR("[ProcessPacket] INPUT ��Ŷ ũ�� ����ġ. ����: " +
                std::to_string(length) + ", ����: " +
                std::to_string(sizeof(InputPacket)));
        }
    }
    break;
    default:
    {
        LOG_WARNING("ó������ ���� ��Ŷ Ÿ��: " +
            std::to_string(static_cast<int>(header->PacketType)) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    }
    break;
    }
}

void IOCPServer::HandleInputPacket(ClientSession* client, const InputPacket* packet)
{
    if (!client || !packet)
        return;

    LOG_DEBUG("�Է� ��Ŷ ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
        ", Forward: " + std::to_string(packet->ForwardValue) +
        ", Right: " + std::to_string(packet->RightValue) +
		", Yaw: " + std::to_string(packet->ControlRotationYaw) +
        ", Jump: " + (packet->bJumpPressed ? "true" : "false") +
        ", Attack: " + (packet->bAttackPressed ? "true" : "false"));

    // �̵� �Է� ����
    client->InputForward = packet->ForwardValue;
    client->InputRight = packet->RightValue;
    client->bJumpRequested = packet->bJumpPressed;
    client->bAttackRequested = packet->bAttackPressed;

    // �Է� �� ��ȿ�� �˻� (�α�)
    if (std::abs(packet->ForwardValue) > 1.0f || std::abs(packet->RightValue) > 1.0f) {
        LOG_WARNING("���������� �Է� ��: Forward=" + std::to_string(packet->ForwardValue) +
            ", Right=" + std::to_string(packet->RightValue) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    }
}
