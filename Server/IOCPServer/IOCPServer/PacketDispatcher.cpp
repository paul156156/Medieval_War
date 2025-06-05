#include "PacketDispatcher.h"
#include "Logger.h"
#include "NetworkSessionManager.h"

void PacketDispatcher::SendClientId(ClientSession* client) {
    if (!client) {
        LOG_ERROR("SendClientId: ��ȿ���� ���� Ŭ���̾�Ʈ");
        return;
    }

    ClientIdPacket packet = CreateClientIdPacket(client->id);

    if (NetworkSessionManager::SendPacketSafe(client, &packet, sizeof(packet), "SendClientId")) {
        LogPacketSent("CLIENT_ID", client->id, sizeof(packet));
        LOG_INFO("�� Ŭ���̾�Ʈ���� ID " + std::to_string(client->id) + " ���۵�");
    }
}

//void PacketDispatcher::SendInitialPosition(ClientSession* client) {
//    if (!client) {
//        LOG_ERROR("SendInitialPosition: ��ȿ���� ���� Ŭ���̾�Ʈ");
//        return;
//    }
//
//    PositionPacket packet = CreatePositionPacket(client);
//    packet.Header.PacketType = EPacketType::PLAYER_INIT_INFO;
//
//    if (NetworkSessionManager::SendPacketSafe(client, &packet, sizeof(packet), "SendInitialPosition")) {
//        LogPacketSent("PLAYER_INIT_INFO", client->id, sizeof(packet));
//        LOG_INFO("�ʱ� ��ġ ���� ���۵� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
//            ", ��ġ: (" + std::to_string(client->Position.X) +
//            ", " + std::to_string(client->Position.Y) +
//            ", " + std::to_string(client->Position.Z) + ")");
//    }
//}

void PacketDispatcher::SendPong(ClientSession* client) {
    if (!client) {
        LOG_ERROR("SendPong: ��ȿ���� ���� Ŭ���̾�Ʈ");
        return;
    }

    PongPacket packet = CreatePongPacket(client);

    if (NetworkSessionManager::SendPacketSafe(client, &packet, sizeof(packet), "SendPong")) {
        LogPacketSent("PONG", client->id, sizeof(packet));
        LOG_DEBUG("Pong ���۵� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    }
}

void PacketDispatcher::BroadcastNewPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("BroadcastNewPlayer: ��ȿ���� ���� �� Ŭ���̾�Ʈ");
        return;
    }

    OutputPacket packet = CreateOutputPacket(newClient);

    int successCount = 0;
    int totalCount = 0;

    for (const auto& pair : clients) {
        ClientSession* target = pair.second;
        if (target && target->id != newClient->id && target->IsConnected()) {
            totalCount++;
            if (NetworkSessionManager::SendPacketSafe(target, &packet, sizeof(packet), "BroadcastNewPlayer")) {
                successCount++;
            }
        }
    }

    LogBroadcastStats("BroadcastNewPlayer", successCount, totalCount);
    LOG_INFO("�� �÷��̾� ���� ��ε�ĳ��Ʈ �Ϸ� - ID: " + std::to_string(newClient->id) +
        ", ������: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
}

void PacketDispatcher::SendExistingPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("SendExistingPlayer: ��ȿ���� ���� �� Ŭ���̾�Ʈ");
        return;
    }

    int sentCount = 0;

    for (const auto& pair : clients) {
        ClientSession* existing = pair.second;
        if (existing && existing->id != newClient->id && existing->IsConnected()) {
            OutputPacket packet = CreateOutputPacket(existing);

            if (NetworkSessionManager::SendPacketSafe(newClient, &packet, sizeof(packet), "SendExistingPlayers")) {
                sentCount++;
            }
        }
    }

    LOG_INFO("���� �÷��̾� ���� ���� �Ϸ� - ��� ID: " + std::to_string(newClient->id) +
        ", ���۵� �÷��̾� ��: " + std::to_string(sentCount));
}

void PacketDispatcher::BroadcastPlayerUpdate(ClientSession* sourceClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!sourceClient) {
        LOG_ERROR("BroadcastPlayerUpdate: ��ȿ���� ���� �ҽ� Ŭ���̾�Ʈ");
        return;
    }

    OutputPacket packet = CreateOutputPacket(sourceClient);

    int successCount = 0;
    int totalCount = 0;

    for (const auto& pair : clients) {
        ClientSession* target = pair.second;
        if (target && target->IsConnected()) {
            totalCount++;
            if (NetworkSessionManager::SendPacketSafe(target, &packet, sizeof(packet), "BroadcastPlayerUpdate")) {
                successCount++;
            }
        }
    }

    // �������� ���� ���� ��� �α�
    if (totalCount > 0 && successCount < totalCount * 0.8f) {
        LOG_WARNING("�÷��̾� ������Ʈ ��ε�ĳ��Ʈ �Ϻ� ���� - �ҽ� ID: " + std::to_string(sourceClient->id) +
            ", ����: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
    }
}

void PacketDispatcher::NotifyPlayerDisconnect(int disconnectedClientId, const std::unordered_map<int, ClientSession*>& clients) {
    DisconnectPacket packet = CreateDisconnectPacket(disconnectedClientId);

    int successCount = 0;
    int totalCount = 0;

    for (const auto& pair : clients) {
        ClientSession* target = pair.second;
        if (target && target->id != disconnectedClientId && target->IsConnected()) {
            totalCount++;
            if (NetworkSessionManager::SendPacketSafe(target, &packet, sizeof(packet), "NotifyPlayerDisconnect")) {
                successCount++;
            }
        }
    }

    LogBroadcastStats("NotifyPlayerDisconnect", successCount, totalCount);
    LOG_INFO("�÷��̾� ���� ���� �˸� �Ϸ� - ID: " + std::to_string(disconnectedClientId) +
        ", �˸� ���: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
}

void PacketDispatcher::BroadcastPlayerState(ClientSession* sourceClient, EPlayerState state, const std::unordered_map<int, ClientSession*>& clients) {
    if (!sourceClient) {
        LOG_ERROR("BroadcastPlayerState: ��ȿ���� ���� �ҽ� Ŭ���̾�Ʈ");
        return;
    }

    // �ӽ÷� ���� �����Ͽ� ��Ŷ ����
    EPlayerState originalState = sourceClient->State;
    sourceClient->State = state;

    OutputPacket packet = CreateOutputPacket(sourceClient);

    // ���� ���·� ����
    sourceClient->State = originalState;

    int successCount = 0;
    int totalCount = 0;

    for (const auto& pair : clients) {
        ClientSession* target = pair.second;
        if (target && target->id != sourceClient->id && target->IsConnected()) {
            totalCount++;
            if (NetworkSessionManager::SendPacketSafe(target, &packet, sizeof(packet), "BroadcastPlayerState")) {
                successCount++;
            }
        }
    }

    LogBroadcastStats("BroadcastPlayerState", successCount, totalCount);
}

void PacketDispatcher::BroadcastPlayerAction(ClientSession* sourceClient, EPlayerAction action, const std::unordered_map<int, ClientSession*>& clients) {
    if (!sourceClient) {
        LOG_ERROR("BroadcastPlayerAction: ��ȿ���� ���� �ҽ� Ŭ���̾�Ʈ");
        return;
    }

    // �ӽ÷� ���� �����Ͽ� ��Ŷ ����
    EPlayerAction originalAction = sourceClient->Action;
    sourceClient->Action = action;

    OutputPacket packet = CreateOutputPacket(sourceClient);

    // ���� ���·� ����
    sourceClient->Action = originalAction;

    int successCount = 0;
    int totalCount = 0;

    for (const auto& pair : clients) {
        ClientSession* target = pair.second;
        if (target && target->id != sourceClient->id && target->IsConnected()) {
            totalCount++;
            if (NetworkSessionManager::SendPacketSafe(target, &packet, sizeof(packet), "BroadcastPlayerAction")) {
                successCount++;
            }
        }
    }

    LogBroadcastStats("BroadcastPlayerAction", successCount, totalCount);
}

bool PacketDispatcher::ProcessReceivedPacket(ClientSession* client, char* data, int length) {
    if (!client || !data || length < sizeof(PacketHeader)) {
        LOG_ERROR("ProcessReceivedPacket: ��ȿ���� ���� �Ű�����");
        return false;
    }

    //LOG_DEBUG("��Ŷ ���ŵ� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
    //    ", ����: " + std::to_string(length));

    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    if (!ValidatePacketHeader(header, length)) {
        LOG_WARNING("��Ŷ ��� ���� ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return false;
    }

    // ��Ŷ Ÿ�Ժ� ó��
    switch (header->PacketType) {
    case EPacketType::PING:
        if (length >= sizeof(PingPacket)) {
            HandlePingPacket(client, reinterpret_cast<PingPacket*>(data));
            return true;
        }
        break;

    case EPacketType::PLAYER_INPUT_INFO:
        if (length >= sizeof(InputPacket)) {
            HandleInputPacket(client, reinterpret_cast<InputPacket*>(data));
            return true;
        }
        break;

    case EPacketType::PLAYER_INIT_INFO:
        if (length >= sizeof(InitPacket)) {
            HandleInitPacket(client, reinterpret_cast<InitPacket*>(data));
            return true;
        }
        break;

    case EPacketType::CONNECT:
        if (length >= sizeof(ConnectPacket)) {
            HandleConnectPacket(client, reinterpret_cast<ConnectPacket*>(data));
            return true;
        }
        break;

    case EPacketType::DISCONNECT:
        if (length >= sizeof(DisconnectPacket)) {
            HandleDisconnectPacket(client, reinterpret_cast<DisconnectPacket*>(data));
            return true;
        }
        break;

    default:
        LOG_WARNING("ó������ ���� ��Ŷ Ÿ��: " + std::to_string(static_cast<int>(header->PacketType)) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return false;
    }

    LOG_WARNING("��Ŷ ũ�� ����ġ - Ÿ��: " + std::to_string(static_cast<int>(header->PacketType)) +
        ", ���� ũ��: " + std::to_string(length) +
        ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    return false;
}

// Private ���� �Լ���
ClientIdPacket PacketDispatcher::CreateClientIdPacket(int clientId) {
    ClientIdPacket packet;
    packet.Header.PacketType = EPacketType::CLIENT_ID;
    packet.Header.PacketSize = sizeof(ClientIdPacket);
    packet.ClientId = clientId;
    return packet;
}

OutputPacket PacketDispatcher::CreateOutputPacket(ClientSession* client) {
    OutputPacket packet;
    packet.Header.PacketType = EPacketType::PLAYER_UPDATE_INFO;
    packet.Header.PacketSize = sizeof(OutputPacket);
    packet.ClientId = client->id;
    packet.Position = client->Position;
    packet.Rotation = client->Rotation;
    packet.Velocity = client->Velocity;
    packet.State = client->State;
	packet.Action = client->Action;
    return packet;
}

PongPacket PacketDispatcher::CreatePongPacket(ClientSession* client) {
    PongPacket packet;
    packet.Header.PacketType = EPacketType::PONG;
    packet.Header.PacketSize = sizeof(PongPacket);
    packet.ClientId = client->id;
    packet.PingTime = GetTickCount64();

    // Ŭ���̾�Ʈ�� Pong �ð� ������Ʈ
    client->LastPongTime = packet.PingTime / 1000.0f;

    return packet;
}

DisconnectPacket PacketDispatcher::CreateDisconnectPacket(int clientId) {
    DisconnectPacket packet;
    packet.Header.PacketType = EPacketType::DISCONNECT;
    packet.Header.PacketSize = sizeof(DisconnectPacket);
    packet.ClientId = clientId;
    return packet;
}

bool PacketDispatcher::ValidatePacketHeader(const PacketHeader* header, size_t receivedSize) {
    return IsValidPacketHeader(header, receivedSize);
}

bool PacketDispatcher::ValidateInputPacket(const InputPacket* packet) {
    if (!packet) return false;

    return IsValidInputValue(packet->ForwardValue) &&
        IsValidInputValue(packet->RightValue) &&
        IsValidRotationValue(packet->RotationPitch) &&
        IsValidRotationValue(packet->RotationYaw) &&
        IsValidRotationValue(packet->RotationRoll);
}

bool PacketDispatcher::ValidateOutputPacket(const OutputPacket* packet) {
    if (!packet) return false;

	return IsValidPlayerState(packet->State) && IsValidPlayerAction(packet->Action) &&
        isfinite(packet->Position.X) && isfinite(packet->Position.Y) && isfinite(packet->Position.Z) &&
        isfinite(packet->Velocity.X) && isfinite(packet->Velocity.Y) && isfinite(packet->Velocity.Z);
}

void PacketDispatcher::HandlePingPacket(ClientSession* client, const PingPacket* packet) {
    LogPacketReceived("PING", client->id, sizeof(PingPacket));

    client->LastPingTime = GetTickCount64() / 1000.0f;

    SendPong(client);
}

void PacketDispatcher::HandleInputPacket(ClientSession* client, const InputPacket* packet) {
    LOG_DEBUG("�Է� ��Ŷ ���� - Ŭ���̾�Ʈ ID: " + std::to_string(packet->ClientId) +
        ", Forward: " + std::to_string(packet->ForwardValue) +
        ", Right: " + std::to_string(packet->RightValue) +
        ", Pitch: " + std::to_string(packet->RotationPitch) +
        ", Yaw: " + std::to_string(packet->RotationYaw) +
        ", Roll: " + std::to_string(packet->RotationRoll) +
        ", Run: " + std::to_string(packet->bRunPressed) +
        ", Jump: " + std::to_string(packet->bJumpPressed) +
        ", Attack: " + std::to_string(packet->bAttackPressed) +
        ", Defend: " + std::to_string(packet->bDefendPressed));

    if (!ValidateInputPacket(packet)) {
        LOG_WARNING("��ȿ���� ���� �Է� ��Ŷ - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return;
    }

    LogPacketReceived("INPUT", client->id, sizeof(InputPacket));

    // �Է� ������ ������Ʈ
    client->InputForward = packet->ForwardValue;
    client->InputRight = packet->RightValue;
    client->InputPitch = packet->RotationPitch;
    client->InputYaw = packet->RotationYaw;
    client->InputRoll = packet->RotationRoll;
    client->bRunRequested = packet->bRunPressed;
    client->bJumpRequested = packet->bJumpPressed;
    client->bAttackRequested = packet->bAttackPressed;
	client->bDefendRequested = packet->bDefendPressed;

    //// �׼� ��ư�� Ʈ���� ������� ó�� (�� ���� ����)
    //if (packet->bJumpPressed && !client->bJumpRequested) {
    //    client->bJumpRequested = true;
    //    LOG_DEBUG("���� ��û ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    //}

    //if (packet->bAttackPressed && !client->bAttackRequested) {
    //    client->bAttackRequested = true;
    //    LOG_DEBUG("���� ��û ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    //}

    //if (packet->bDefendPressed && !client->bDefendRequested) {
    //    client->bDefendRequested = true;
    //    LOG_DEBUG("��� ��û ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    //}

    // �Է� �ð� ������Ʈ (���� ������)
    client->LastInputTime = GetTickCount64() / 1000.0f;
}

void PacketDispatcher::HandleInitPacket(ClientSession* client, const InitPacket* packet) {
    LogPacketReceived("INIT", client->id, sizeof(InitPacket));

    client->Position = packet->Position;
    client->Rotation = packet->Rotation;
    client->PreviousPosition = client->Position;

    LOG_INFO("Ŭ���̾�Ʈ �ʱ�ȭ ���� ���� - ID: " + std::to_string(client->id) +
        ", ��ġ: (" + std::to_string(client->Position.X) +
        ", " + std::to_string(client->Position.Y) +
        ", " + std::to_string(client->Position.Z) + ")");
}

void PacketDispatcher::HandleConnectPacket(ClientSession* client, const ConnectPacket* packet) {
    LogPacketReceived("CONNECT", client->id, sizeof(ConnectPacket));

    client->ConnectionState = EConnectionState::AUTHENTICATED;
    LOG_INFO("Ŭ���̾�Ʈ ���� Ȯ�ε� - ID: " + std::to_string(client->id));
}

void PacketDispatcher::HandleDisconnectPacket(ClientSession* client, const DisconnectPacket* packet) {
    LogPacketReceived("DISCONNECT", client->id, sizeof(DisconnectPacket));

    client->ConnectionState = EConnectionState::DISCONNECTING;
    LOG_INFO("Ŭ���̾�Ʈ ���� ���� ��û - ID: " + std::to_string(client->id));
}

void PacketDispatcher::SendExistingPlayerIDs(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("SendExistingPlayerIDs: ��ȿ���� ���� �� Ŭ���̾�Ʈ");
        return;
    }

    int sentCount = 0;
    for (const auto& pair : clients) {
        ClientSession* existingClient = pair.second;
        if (existingClient && existingClient->id != newClient->id && existingClient->IsConnected()) {
            ClientIdPacket packet;
            packet.Header.PacketType = EPacketType::CLIENT_ID;
            packet.Header.PacketSize = sizeof(ClientIdPacket);
            packet.ClientId = existingClient->id;

            if (NetworkSessionManager::SendPacketSafe(newClient, &packet, sizeof(packet), "SendExistingPlayerIDs")) {
                sentCount++;
            }
        }
    }

    LOG_INFO("���� �÷��̾� ID ���� �Ϸ� - ���: " + std::to_string(newClient->id) +
        ", ���۵� ID ����: " + std::to_string(sentCount));
}

void PacketDispatcher::BroadcastNewPlayerID(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("BroadcastNewPlayerID: ��ȿ���� ���� �� Ŭ���̾�Ʈ");
        return;
    }

    ClientIdPacket packet;
    packet.Header.PacketType = EPacketType::CLIENT_ID;
    packet.Header.PacketSize = sizeof(ClientIdPacket);
    packet.ClientId = newClient->id;

    int successCount = 0;
    int totalCount = 0;

    for (const auto& pair : clients) {
        ClientSession* target = pair.second;
        if (target && target->id != newClient->id && target->IsConnected()) {
            totalCount++;
            if (NetworkSessionManager::SendPacketSafe(target, &packet, sizeof(packet), "BroadcastNewPlayerID")) {
                successCount++;
            }
        }
    }

    LOG_INFO("�� �÷��̾� ID ��ε�ĳ��Ʈ �Ϸ� - ID: " + std::to_string(newClient->id) +
        ", ����: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
}

void PacketDispatcher::LogPacketSent(const char* packetType, int clientId, size_t size) {
    LOG_DEBUG("[SEND] " + std::string(packetType) + " -> Ŭ���̾�Ʈ " + std::to_string(clientId) +
        " (" + std::to_string(size) + " bytes)");
}

void PacketDispatcher::LogPacketReceived(const char* packetType, int clientId, size_t size) {
    LOG_DEBUG("[RECV] " + std::string(packetType) + " <- Ŭ���̾�Ʈ " + std::to_string(clientId) +
        " (" + std::to_string(size) + " bytes)");
}

void PacketDispatcher::LogBroadcastStats(const char* context, int successCount, int totalCount) {
    if (totalCount > 0) {
        float successRate = (float)successCount / totalCount * 100.0f;
        LOG_DEBUG("[BROADCAST] " + std::string(context) + " - ������: " +
            std::to_string(successRate) + "% (" + std::to_string(successCount) +
            "/" + std::to_string(totalCount) + ")");
    }
}