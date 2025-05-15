// GameUpdater.cpp
#include "GameUpdater.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"
#include <cmath>
#include <WinSock2.h>
#include <WS2tcpip.h>


void GameUpdater::UpdateClients(float DeltaTime, std::unordered_map<int, ClientSession*>& clients, std::mutex& clientsMutex)
{
    if (DeltaTime > 0.5f) DeltaTime = 0.5f;
    const float currentTime = GetTickCount64() / 1000.0f;
    std::vector<int> ClientsToRemove;

    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto& pair : clients)
    {
        ClientSession* client = pair.second;
        if (!client) continue;

        if ((currentTime - client->LastPingTime) > 5.0f)
        {
            LOG_WARNING("[PingTimeout] 클라이언트 ID: " + std::to_string(client->id));
            ClientsToRemove.push_back(client->id);
            continue;
        }

        UpdateClient(client, DeltaTime, currentTime);
        BroadcastPosition(client, clients);

        client->bJumpRequested = false;
        client->bAttackRequested = false;
        client->PreviousVelocity = client->Velocity;
    }

    for (int id : ClientsToRemove) {
        clients.erase(id);
    }
}

void GameUpdater::UpdateClient(ClientSession* client, float DeltaTime, float currentTime)
{
    float Forward = client->InputForward;
    float Right = client->InputRight;
    float YawRad = client->ControlRotationYaw * 3.14159265f / 180.0f;
    float CosYaw = cos(YawRad);
    float SinYaw = sin(YawRad);

    Vec3 MoveDir = {
        Forward * CosYaw + Right * SinYaw,
        Forward * SinYaw - Right * CosYaw,
        0.0f
    };

    float magnitude = sqrt(MoveDir.X * MoveDir.X + MoveDir.Y * MoveDir.Y);
    if (magnitude > 0.0f) {
        MoveDir.X /= magnitude;
        MoveDir.Y /= magnitude;
    }

    const float MoveSpeed = 500.0f;
    client->Velocity.X = MoveDir.X * MoveSpeed;
    client->Velocity.Y = MoveDir.Y * MoveSpeed;

    if (client->bJumpRequested && client->Position.Z <= 91.0f) {
        client->Velocity.Z = 600.0f;
        client->State = EPlayerState::JUMPING;
    }
    else if (client->bAttackRequested) {
        client->State = EPlayerState::ATTACKING;
    }
    else if (magnitude > 0.0f) {
        client->State = EPlayerState::WALKING;
    }
    else if (client->State != EPlayerState::JUMPING) {
        client->State = EPlayerState::IDLE;
    }

    client->LastPosition = client->Position;

    client->Position.X += client->Velocity.X * DeltaTime;
    client->Position.Y += client->Velocity.Y * DeltaTime;
    client->Position.Z += client->Velocity.Z * DeltaTime;

    const float Gravity = 980.0f;
    client->Velocity.Z -= Gravity * DeltaTime;

    if (client->Position.Z <= 90.0f) {
        client->Position.Z = 90.0f;
        if (client->Velocity.Z < 0) client->Velocity.Z = 0;
        if (client->State == EPlayerState::JUMPING) client->State = EPlayerState::IDLE;
    }
}

void GameUpdater::BroadcastPosition(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients)
{
    const float MinUpdateDist = 0.1f;
    const float UpdateInterval = 0.1f;
    float dx = sourceClient->Position.X - sourceClient->LastPosition.X;
    float dy = sourceClient->Position.Y - sourceClient->LastPosition.Y;
    float dz = sourceClient->Position.Z - sourceClient->LastPosition.Z;
    float movedDist = sqrt(dx * dx + dy * dy + dz * dz);

    float now = GetTickCount64() / 1000.0f;

    if (movedDist < MinUpdateDist &&
        sourceClient->State == sourceClient->PreviousState &&
        now - sourceClient->LastUpdateTime < UpdateInterval)
        return;

    sourceClient->LastUpdateTime = now;
    sourceClient->PreviousState = sourceClient->State;

    PositionPacket packet;
    packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
    packet.Header.PacketSize = sizeof(PositionPacket);
    packet.ClientId = sourceClient->id;
    packet.Position = sourceClient->Position;
	packet.Rotation = sourceClient->Rotation;
    packet.Velocity = sourceClient->Velocity;
    packet.State = sourceClient->State;

    for (const auto& pair : clients)
    {
        if (pair.first == sourceClient->id) continue;
        NetworkSessionManager::SendPacket(pair.second, &packet, sizeof(packet), "BroadcastPosition");
    }
}