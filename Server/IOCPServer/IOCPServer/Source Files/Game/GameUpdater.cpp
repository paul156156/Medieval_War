#include "GameUpdater.h"
#include "Logger.h"
#include "PacketDispatcher.h"
#include <cmath>
#include <chrono>

GameUpdater::GameUpdater() {
    LOG_INFO("���� �������� �ʱ�ȭ �Ϸ�");
}

GameUpdater::~GameUpdater() {
    LOG_INFO("���� �������� ���� �Ϸ�");
}

void GameUpdater::UpdateClients(float deltaTime, std::unordered_map<int, ClientSession*>& clients, std::shared_mutex& clientsMutex) {
    auto updateStart = std::chrono::high_resolution_clock::now();

    // ��Ÿ Ÿ�� ���� �� ����
    if (deltaTime > 0.5f) {
        LOG_WARNING("������������ ū ��Ÿ Ÿ��: " + std::to_string(deltaTime) + "��. 0.5�ʷ� ����");
        deltaTime = 0.5f;
    }

    const float currentTime = GetTickCount64() / 1000.0f;
    std::vector<int> clientsToRemove;
    updatedClientCount = 0;

    // Ŭ���̾�Ʈ ������Ʈ (�б� �� ���)
    {
        std::shared_lock<std::shared_mutex> lock(clientsMutex);

        for (auto& pair : clients) {
            ClientSession* client = pair.second;
            if (!client) {
                LOG_WARNING("null Ŭ���̾�Ʈ ���� �߰�");
                continue;
            }

            // Ÿ�Ӿƿ� üũ
            if (client->IsTimedOut(currentTime)) {
                LOG_WARNING("Ŭ���̾�Ʈ Ÿ�Ӿƿ� - ID: " + std::to_string(client->id) +
                    ", ������ Ping: " + std::to_string(currentTime - client->LastPingTime) + "�� ��");
                clientsToRemove.push_back(client->id);
                continue;
            }

            // Ŭ���̾�Ʈ ������Ʈ
            UpdateClient(client, deltaTime, currentTime);

            // ��ġ ��ε�ĳ��Ʈ �ʿ�� ����
            if (ShouldUpdatePosition(client, currentTime)) {
                BroadcastPositionUpdate(client, clients);
                client->LastUpdateTime = currentTime;
                client->PreviousState = client->State;
            }

            // �Է� ���� ����
            client->bJumpRequested = false;
            client->bAttackRequested = false;
            client->bRunRequested = false;
            //client->bCrouchRequested = false;

            // ���� �ӵ� ����
            client->PreviousVelocity = client->Velocity;
            updatedClientCount++;
        }
    }

    // Ÿ�Ӿƿ��� Ŭ���̾�Ʈ ���� (���� �� �ʿ�)
    if (!clientsToRemove.empty()) {
        std::unique_lock<std::shared_mutex> lock(clientsMutex);
        for (int clientId : clientsToRemove) {
            auto it = clients.find(clientId);
            if (it != clients.end()) {
                clients.erase(it);
                LOG_INFO("Ÿ�Ӿƿ����� Ŭ���̾�Ʈ ���ŵ� - ID: " + std::to_string(clientId));
            }
        }
    }

    // ���� ����
    auto updateEnd = std::chrono::high_resolution_clock::now();
    float updateTime = std::chrono::duration<float, std::milli>(updateEnd - updateStart).count();
    UpdatePerformanceStats(updateTime);
}

void GameUpdater::UpdateClient(ClientSession* client, float deltaTime, float currentTime) {
    if (!client) return;

    // ������ ���
    CalculateMovement(client, deltaTime);

    // ���� �ùķ��̼� ����
    if (physicsEnabled) {
        ApplyPhysics(client, deltaTime);
    }

    // �÷��̾� ���� ������Ʈ
    UpdatePlayerState(client);

    // ���� ��ġ ����
    client->LastPosition = client->Position;

    // ��ġ ������Ʈ
    client->Position.X += client->Velocity.X * deltaTime;
    client->Position.Y += client->Velocity.Y * deltaTime;
    client->Position.Z += client->Velocity.Z * deltaTime;

    // ���� ��� üũ
    ApplyWorldBounds(client);
}

void GameUpdater::CalculateMovement(ClientSession* client, float deltaTime) {
    // �Է°� ��� �̵� ���� ���
    Vec3 moveDir = CalculateMovementDirection(client);

    // �⺻ �̵� �ӵ� ����
    float currentMoveSpeed = settings.moveSpeed;

    // �޸���/��ũ���� �ӵ� ����
    if (client->bRunRequested) {
        currentMoveSpeed *= settings.runMultiplier;
    }
    //else if (client->bCrouchRequested) {
    //    currentMoveSpeed *= settings.crouchMultiplier;
    //}

    // ���� �ӵ� ����
    client->Velocity.X = moveDir.X * currentMoveSpeed;
    client->Velocity.Y = moveDir.Y * currentMoveSpeed;

    // ���� ó��
    if (client->bJumpRequested && client->Position.Z <= settings.groundLevel + 1.0f) {
        client->Velocity.Z = settings.jumpVelocity;
        LOG_DEBUG("���� ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    }
}

Vec3 GameUpdater::CalculateMovementDirection(ClientSession* client) {
    float forward = client->InputForward;
    float right = client->InputRight;
    float yawRad = client->ControlRotationYaw * (3.14159265f / 180.0f);

    float cosYaw = cos(yawRad);
    float sinYaw = sin(yawRad);

    Vec3 moveDir;
    moveDir.X = forward * cosYaw - right * sinYaw;
    moveDir.Y = forward * sinYaw + right * cosYaw;
    moveDir.Z = 0.0f;

    // ����ȭ
    float magnitude = sqrt(moveDir.X * moveDir.X + moveDir.Y * moveDir.Y);
    if (magnitude > 0.0f) {
        moveDir.X /= magnitude;
        moveDir.Y /= magnitude;
    }

    return moveDir;
}

void GameUpdater::UpdatePlayerState(ClientSession* client) {
    // ���� ���� �켱 ó��
    if (client->bAttackRequested) {
        client->State = EPlayerState::ATTACKING;
        return;
    }

    // ���� ���� ó��
    if (client->Position.Z > settings.groundLevel + 1.0f) {
        client->State = EPlayerState::JUMPING;
        return;
    }

    //// ��ũ���� ���� ó��
    //if (client->bCrouchRequested) {
    //    client->State = EPlayerState::CROUCHING;
    //    return;
    //}

    // �̵� ���� ó��
    float horizontalSpeed = sqrt(client->Velocity.X * client->Velocity.X + client->Velocity.Y * client->Velocity.Y);

    if (horizontalSpeed > 0.1f) {
        if (client->bRunRequested) {
            client->State = EPlayerState::RUNNING;
        }
        else {
            client->State = EPlayerState::WALKING;
        }
    }
    else {
        client->State = EPlayerState::IDLE;
    }
}

void GameUpdater::ApplyPhysics(ClientSession* client, float deltaTime) {
    // �߷� ����
    ApplyGravity(client, deltaTime);

    // ���� �浹 üũ
    CheckGroundCollision(client);
}

void GameUpdater::ApplyGravity(ClientSession* client, float deltaTime) {
    // ���麸�� ���� ���� ���� �߷� ����
    if (client->Position.Z > settings.groundLevel) {
        client->Velocity.Z -= settings.gravity * deltaTime;
    }
}

void GameUpdater::CheckGroundCollision(ClientSession* client) {
    // ���� �Ʒ��� �������� �ʵ��� ó��
    if (client->Position.Z <= settings.groundLevel) {
        client->Position.Z = settings.groundLevel;

        // ���� �ӵ��� 0���� ����
        if (client->Velocity.Z < 0) {
            client->Velocity.Z = 0.0f;
        }

        // ���� ���¿��� ���� �� ���� ����
        if (client->State == EPlayerState::JUMPING) {
            client->State = EPlayerState::IDLE;
        }
    }
}

void GameUpdater::ApplyWorldBounds(ClientSession* client) {
    // ���� ��� ���� ��ġ ����
    if (client->Position.X < -settings.worldBoundary) {
        client->Position.X = -settings.worldBoundary;
        client->Velocity.X = 0.0f;
    }
    if (client->Position.X > settings.worldBoundary) {
        client->Position.X = settings.worldBoundary;
        client->Velocity.X = 0.0f;
    }
    if (client->Position.Y < -settings.worldBoundary) {
        client->Position.Y = -settings.worldBoundary;
        client->Velocity.Y = 0.0f;
    }
    if (client->Position.Y > settings.worldBoundary) {
        client->Position.Y = settings.worldBoundary;
        client->Velocity.Y = 0.0f;
    }
}

bool GameUpdater::ShouldUpdatePosition(ClientSession* client, float currentTime) {
    // �̵� �Ÿ� ���
    float dx = client->Position.X - client->LastPosition.X;
    float dy = client->Position.Y - client->LastPosition.Y;
    float dz = client->Position.Z - client->LastPosition.Z;
    float movedDistance = sqrt(dx * dx + dy * dy + dz * dz);

    // ������Ʈ ���� üũ
    bool significantMovement = movedDistance > settings.minUpdateDistance;
    bool stateChanged = client->State != client->PreviousState;
    bool timeElapsed = (currentTime - client->LastUpdateTime) > settings.updateInterval;

    return significantMovement || stateChanged || timeElapsed;
}

void GameUpdater::BroadcastPositionUpdate(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients) {
    // ȸ�� ���� ������Ʈ
    sourceClient->Rotation.Pitch = sourceClient->ControlRotationPitch;
    sourceClient->Rotation.Yaw = sourceClient->ControlRotationYaw;
    sourceClient->Rotation.Roll = sourceClient->ControlRotationRoll;

    // ��ġ ������Ʈ ��ε�ĳ��Ʈ
    PacketDispatcher::BroadcastPlayerUpdate(sourceClient, clients);
}

void GameUpdater::SetUpdateRate(float updatesPerSecond) {
    if (updatesPerSecond > 0.0f && updatesPerSecond <= 120.0f) {
        targetUpdateRate = updatesPerSecond;
        settings.updateInterval = 1.0f / updatesPerSecond;
        LOG_INFO("������Ʈ �ֱ� �����: " + std::to_string(updatesPerSecond) + "Hz");
    }
}

void GameUpdater::SetPhysicsEnabled(bool enabled) {
    physicsEnabled = enabled;
    LOG_INFO("���� �ùķ��̼� " + std::string(enabled ? "Ȱ��ȭ" : "��Ȱ��ȭ"));
}

int GameUpdater::GetUpdatedClientCount() const {
    return updatedClientCount;
}

float GameUpdater::GetAverageUpdateTime() const {
    return averageUpdateTime;
}

void GameUpdater::UpdatePerformanceStats(float updateTime) {
    // ���� �̵� ������� ��� ������Ʈ �ð� ���
    const float alpha = 0.1f;
    averageUpdateTime = averageUpdateTime * (1.0f - alpha) + updateTime * alpha;

    // ���� ��� (10ms �ʰ���)
    if (updateTime > 10.0f) {
        LOG_WARNING("���� ������Ʈ �ð��� ����: " + std::to_string(updateTime) + "ms" +
            ", Ŭ���̾�Ʈ ��: " + std::to_string(updatedClientCount));
    }
}