#include "PacketDispatcher.h"
#include "Logger.h"
#include "NetworkSessionManager.h"

void PacketDispatcher::SendClientId(ClientSession* client) {
    if (!client) {
        LOG_ERROR("SendClientId: 유효하지 않은 클라이언트");
        return;
    }

    ClientIdPacket packet = CreateClientIdPacket(client->id);

    if (NetworkSessionManager::SendPacketSafe(client, &packet, sizeof(packet), "SendClientId")) {
        LogPacketSent("CLIENT_ID", client->id, sizeof(packet));
        LOG_INFO("새 클라이언트에게 ID " + std::to_string(client->id) + " 전송됨");
    }
}

//void PacketDispatcher::SendInitialPosition(ClientSession* client) {
//    if (!client) {
//        LOG_ERROR("SendInitialPosition: 유효하지 않은 클라이언트");
//        return;
//    }
//
//    PositionPacket packet = CreatePositionPacket(client);
//    packet.Header.PacketType = EPacketType::PLAYER_INIT_INFO;
//
//    if (NetworkSessionManager::SendPacketSafe(client, &packet, sizeof(packet), "SendInitialPosition")) {
//        LogPacketSent("PLAYER_INIT_INFO", client->id, sizeof(packet));
//        LOG_INFO("초기 위치 정보 전송됨 - 클라이언트 ID: " + std::to_string(client->id) +
//            ", 위치: (" + std::to_string(client->Position.X) +
//            ", " + std::to_string(client->Position.Y) +
//            ", " + std::to_string(client->Position.Z) + ")");
//    }
//}

void PacketDispatcher::SendPong(ClientSession* client) {
    if (!client) {
        LOG_ERROR("SendPong: 유효하지 않은 클라이언트");
        return;
    }

    PongPacket packet = CreatePongPacket(client);

    if (NetworkSessionManager::SendPacketSafe(client, &packet, sizeof(packet), "SendPong")) {
        LogPacketSent("PONG", client->id, sizeof(packet));
        LOG_DEBUG("Pong 전송됨 - 클라이언트 ID: " + std::to_string(client->id));
    }
}

void PacketDispatcher::BroadcastNewPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("BroadcastNewPlayer: 유효하지 않은 새 클라이언트");
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
    LOG_INFO("새 플레이어 정보 브로드캐스트 완료 - ID: " + std::to_string(newClient->id) +
        ", 수신자: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
}

void PacketDispatcher::SendExistingPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("SendExistingPlayer: 유효하지 않은 새 클라이언트");
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

    LOG_INFO("기존 플레이어 정보 전송 완료 - 대상 ID: " + std::to_string(newClient->id) +
        ", 전송된 플레이어 수: " + std::to_string(sentCount));
}

void PacketDispatcher::BroadcastPlayerUpdate(ClientSession* sourceClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!sourceClient) {
        LOG_ERROR("BroadcastPlayerUpdate: 유효하지 않은 소스 클라이언트");
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

    // 성공률이 낮을 때만 경고 로그
    if (totalCount > 0 && successCount < totalCount * 0.8f) {
        LOG_WARNING("플레이어 업데이트 브로드캐스트 일부 실패 - 소스 ID: " + std::to_string(sourceClient->id) +
            ", 성공: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
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
    LOG_INFO("플레이어 연결 종료 알림 완료 - ID: " + std::to_string(disconnectedClientId) +
        ", 알림 대상: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
}

void PacketDispatcher::BroadcastPlayerState(ClientSession* sourceClient, EPlayerState state, const std::unordered_map<int, ClientSession*>& clients) {
    if (!sourceClient) {
        LOG_ERROR("BroadcastPlayerState: 유효하지 않은 소스 클라이언트");
        return;
    }

    // 임시로 상태 변경하여 패킷 생성
    EPlayerState originalState = sourceClient->State;
    sourceClient->State = state;

    OutputPacket packet = CreateOutputPacket(sourceClient);

    // 원래 상태로 복원
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
        LOG_ERROR("BroadcastPlayerAction: 유효하지 않은 소스 클라이언트");
        return;
    }

    // 임시로 상태 변경하여 패킷 생성
    EPlayerAction originalAction = sourceClient->Action;
    sourceClient->Action = action;

    OutputPacket packet = CreateOutputPacket(sourceClient);

    // 원래 상태로 복원
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
        LOG_ERROR("ProcessReceivedPacket: 유효하지 않은 매개변수");
        return false;
    }

    //LOG_DEBUG("패킷 수신됨 - 클라이언트 ID: " + std::to_string(client->id) +
    //    ", 길이: " + std::to_string(length));

    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    if (!ValidatePacketHeader(header, length)) {
        LOG_WARNING("패킷 헤더 검증 실패 - 클라이언트 ID: " + std::to_string(client->id));
        return false;
    }

    // 패킷 타입별 처리
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
        LOG_WARNING("처리되지 않은 패킷 타입: " + std::to_string(static_cast<int>(header->PacketType)) +
            ", 클라이언트 ID: " + std::to_string(client->id));
        return false;
    }

    LOG_WARNING("패킷 크기 불일치 - 타입: " + std::to_string(static_cast<int>(header->PacketType)) +
        ", 받은 크기: " + std::to_string(length) +
        ", 클라이언트 ID: " + std::to_string(client->id));
    return false;
}

// Private 헬퍼 함수들
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

    // 클라이언트의 Pong 시간 업데이트
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
    LOG_DEBUG("입력 패킷 수신 - 클라이언트 ID: " + std::to_string(packet->ClientId) +
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
        LOG_WARNING("유효하지 않은 입력 패킷 - 클라이언트 ID: " + std::to_string(client->id));
        return;
    }

    LogPacketReceived("INPUT", client->id, sizeof(InputPacket));

    // 입력 데이터 업데이트
    client->InputForward = packet->ForwardValue;
    client->InputRight = packet->RightValue;
    client->InputPitch = packet->RotationPitch;
    client->InputYaw = packet->RotationYaw;
    client->InputRoll = packet->RotationRoll;
    client->bRunRequested = packet->bRunPressed;
    client->bJumpRequested = packet->bJumpPressed;
    client->bAttackRequested = packet->bAttackPressed;
	client->bDefendRequested = packet->bDefendPressed;

    //// 액션 버튼은 트리거 방식으로 처리 (한 번만 실행)
    //if (packet->bJumpPressed && !client->bJumpRequested) {
    //    client->bJumpRequested = true;
    //    LOG_DEBUG("점프 요청 설정 - 클라이언트 ID: " + std::to_string(client->id));
    //}

    //if (packet->bAttackPressed && !client->bAttackRequested) {
    //    client->bAttackRequested = true;
    //    LOG_DEBUG("공격 요청 설정 - 클라이언트 ID: " + std::to_string(client->id));
    //}

    //if (packet->bDefendPressed && !client->bDefendRequested) {
    //    client->bDefendRequested = true;
    //    LOG_DEBUG("방어 요청 설정 - 클라이언트 ID: " + std::to_string(client->id));
    //}

    // 입력 시간 업데이트 (스팸 방지용)
    client->LastInputTime = GetTickCount64() / 1000.0f;
}

void PacketDispatcher::HandleInitPacket(ClientSession* client, const InitPacket* packet) {
    LogPacketReceived("INIT", client->id, sizeof(InitPacket));

    client->Position = packet->Position;
    client->Rotation = packet->Rotation;
    client->PreviousPosition = client->Position;

    LOG_INFO("클라이언트 초기화 정보 수신 - ID: " + std::to_string(client->id) +
        ", 위치: (" + std::to_string(client->Position.X) +
        ", " + std::to_string(client->Position.Y) +
        ", " + std::to_string(client->Position.Z) + ")");
}

void PacketDispatcher::HandleConnectPacket(ClientSession* client, const ConnectPacket* packet) {
    LogPacketReceived("CONNECT", client->id, sizeof(ConnectPacket));

    client->ConnectionState = EConnectionState::AUTHENTICATED;
    LOG_INFO("클라이언트 연결 확인됨 - ID: " + std::to_string(client->id));
}

void PacketDispatcher::HandleDisconnectPacket(ClientSession* client, const DisconnectPacket* packet) {
    LogPacketReceived("DISCONNECT", client->id, sizeof(DisconnectPacket));

    client->ConnectionState = EConnectionState::DISCONNECTING;
    LOG_INFO("클라이언트 연결 종료 요청 - ID: " + std::to_string(client->id));
}

void PacketDispatcher::SendExistingPlayerIDs(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("SendExistingPlayerIDs: 유효하지 않은 새 클라이언트");
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

    LOG_INFO("기존 플레이어 ID 전송 완료 - 대상: " + std::to_string(newClient->id) +
        ", 전송된 ID 개수: " + std::to_string(sentCount));
}

void PacketDispatcher::BroadcastNewPlayerID(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients) {
    if (!newClient) {
        LOG_ERROR("BroadcastNewPlayerID: 유효하지 않은 새 클라이언트");
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

    LOG_INFO("새 플레이어 ID 브로드캐스트 완료 - ID: " + std::to_string(newClient->id) +
        ", 성공: " + std::to_string(successCount) + "/" + std::to_string(totalCount));
}

void PacketDispatcher::LogPacketSent(const char* packetType, int clientId, size_t size) {
    LOG_DEBUG("[SEND] " + std::string(packetType) + " -> 클라이언트 " + std::to_string(clientId) +
        " (" + std::to_string(size) + " bytes)");
}

void PacketDispatcher::LogPacketReceived(const char* packetType, int clientId, size_t size) {
    LOG_DEBUG("[RECV] " + std::string(packetType) + " <- 클라이언트 " + std::to_string(clientId) +
        " (" + std::to_string(size) + " bytes)");
}

void PacketDispatcher::LogBroadcastStats(const char* context, int successCount, int totalCount) {
    if (totalCount > 0) {
        float successRate = (float)successCount / totalCount * 100.0f;
        LOG_DEBUG("[BROADCAST] " + std::string(context) + " - 성공률: " +
            std::to_string(successRate) + "% (" + std::to_string(successCount) +
            "/" + std::to_string(totalCount) + ")");
    }
}