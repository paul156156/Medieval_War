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

    LOG_INFO("새 클라이언트에게 ID " + std::to_string(client->id) + " 전송됨");
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

    LOG_INFO("초기 위치 정보 전송됨 - 클라이언트 ID: " + std::to_string(client->id) +
        ", 위치: X=" + std::to_string(client->Position.X) +
        ", Y=" + std::to_string(client->Position.Y) +
        ", Z=" + std::to_string(client->Position.Z));
}

void IOCPServer::BroadcastNewPlayerJoin(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;

        // 자신에게는 전송하지 않음
        if (targetClient->id == newClient->id)
        {
            continue;
        }

        // 새 플레이어 정보 패킷 생성
        PositionPacket packet;
        packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
        packet.Header.PacketSize = sizeof(PositionPacket);
        packet.ClientId = newClient->id;
        packet.Position = newClient->Position;
        packet.Velocity = newClient->Velocity;
        packet.State = newClient->State;

        // 비동기 전송
        SendPacket(targetClient, &packet, sizeof(packet), "BroadcastNewPlayer");
    }

    LOG_INFO("새 플레이어 정보(ID: " + std::to_string(newClient->id) +
        ") 브로드캐스트 - 수신자 수: " +
        std::to_string(clients.size() - 1));
}

void IOCPServer::SendExistingPlayerList(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    int sentCount = 0;

    for (const auto& pair : clients)
    {
        ClientSession* existingClient = pair.second;

        // 자신은 제외
        if (existingClient->id == newClient->id)
        {
            continue;
        }

        // 기존 플레이어 정보 패킷 생성
        PositionPacket packet;
        packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
        packet.Header.PacketSize = sizeof(PositionPacket);
        packet.ClientId = existingClient->id;
        packet.Position = existingClient->Position;
        packet.Velocity = existingClient->Velocity;
        packet.State = existingClient->State;

        // 비동기 전송
        SendPacket(newClient, &packet, sizeof(packet), "SendExistingPlayers");
        sentCount++;
    }

    LOG_INFO("기존 플레이어 정보 " + std::to_string(sentCount) +
        "개가 새 클라이언트(ID: " + std::to_string(newClient->id) +
        ")에게 전송됨");
}

void IOCPServer::ProcessPacket(ClientSession* client, char* data, int length)
{
    if (length < sizeof(PacketHeader))
    {
        LOG_WARNING("잘못된 패킷 크기: " + std::to_string(length) +
            " 바이트 (최소 " + std::to_string(sizeof(PacketHeader)) +
            " 바이트 필요), 클라이언트 ID: " + std::to_string(client->id));
        return;
    }

    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    // 패킷 타입 유효성 검사
    if (static_cast<int>(header->PacketType) < 0 ||
        static_cast<int>(header->PacketType) > 7) {
        LOG_WARNING("잘못된 패킷 타입: " + std::to_string(static_cast<int>(header->PacketType)) +
            ", 클라이언트 ID: " + std::to_string(client->id));
        return;
    }

    switch (header->PacketType)
    {
    case EPacketType::PING:
    {
        if (length >= sizeof(PingPacket))
        {
            PingPacket* pingPacket = reinterpret_cast<PingPacket*>(data);
            client->LastPingTime = GetTickCount64() / 1000.0f;  // 서버시간으로 갱신

            PongPacket pongPacket;
            pongPacket.Header.PacketType = EPacketType::PONG;
            pongPacket.Header.PacketSize = sizeof(PongPacket);
            pongPacket.ClientId = pingPacket->ClientId;
            pongPacket.PingTime = pingPacket->PingTime;

            SendPacket(client, &pongPacket, sizeof(pongPacket), "SendPong");

            LOG_DEBUG("[서버] PingPacket 수신 - ClientId: " + std::to_string(client->id));
        }
        else
        {
            LOG_WARNING("[ProcessPacket] 잘못된 PING 패킷 크기 수신");
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
            LOG_ERROR("[ProcessPacket] INPUT 패킷 크기 불일치. 수신: " +
                std::to_string(length) + ", 예상: " +
                std::to_string(sizeof(InputPacket)));
        }
    }
    break;
    default:
    {
        LOG_WARNING("처리되지 않은 패킷 타입: " +
            std::to_string(static_cast<int>(header->PacketType)) +
            ", 클라이언트 ID: " + std::to_string(client->id));
    }
    break;
    }
}

void IOCPServer::HandleInputPacket(ClientSession* client, const InputPacket* packet)
{
    if (!client || !packet)
        return;

    LOG_DEBUG("입력 패킷 수신 - 클라이언트 ID: " + std::to_string(client->id) +
        ", Forward: " + std::to_string(packet->ForwardValue) +
        ", Right: " + std::to_string(packet->RightValue) +
		", Yaw: " + std::to_string(packet->ControlRotationYaw) +
        ", Jump: " + (packet->bJumpPressed ? "true" : "false") +
        ", Attack: " + (packet->bAttackPressed ? "true" : "false"));

    // 이동 입력 저장
    client->InputForward = packet->ForwardValue;
    client->InputRight = packet->RightValue;
    client->bJumpRequested = packet->bJumpPressed;
    client->bAttackRequested = packet->bAttackPressed;

    // 입력 값 유효성 검사 (로깅)
    if (std::abs(packet->ForwardValue) > 1.0f || std::abs(packet->RightValue) > 1.0f) {
        LOG_WARNING("비정상적인 입력 값: Forward=" + std::to_string(packet->ForwardValue) +
            ", Right=" + std::to_string(packet->RightValue) +
            ", 클라이언트 ID: " + std::to_string(client->id));
    }
}
