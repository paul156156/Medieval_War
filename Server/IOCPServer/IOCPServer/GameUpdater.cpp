#include "GameUpdater.h"
#include "Logger.h"
#include "PacketDispatcher.h"
#include "NetworkSessionManager.h"
#include <cmath>
#include <chrono>

GameUpdater::GameUpdater() {
    LOG_INFO("���� �������� �ʱ�ȭ ����");

    // ���̸� �ε� �õ�
    if (LoadHeightmap("heightmap")) {

        LOG_INFO("Heightmap �ε� �Ϸ�!");
    }
    else {
        LOG_WARNING("heightmap �ε� ����, �⺻ ground level: " +
            std::to_string(settings.groundLevel));
    }

    // ������� ���� ���� ���� ���� üũ
    std::ifstream metaFile("../../Data/heightmap_meta.txt");
    std::ifstream dataFile("../../Data/heightmap.bin");

    LOG_INFO("Meta file exists: " + std::string(metaFile.good() ? "Yes" : "No"));
    LOG_INFO("Data file exists: " + std::string(dataFile.good() ? "Yes" : "No"));

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
            UpdateClient(client, clients, deltaTime, currentTime);

            // ��ġ ��ε�ĳ��Ʈ �ʿ�� ����
            if (ShouldUpdatePosition(client, currentTime)) {
                BroadcastPositionUpdate(client, clients);
                client->LastUpdateTime = currentTime;
                client->PreviousState = client->State;
            }

            // �Է� ���� ����
            client->bRunRequested = false;
            client->bJumpRequested = false;
            client->bAttackRequested = false;
            client->bDefendRequested = false;

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

void GameUpdater::UpdateClient(ClientSession* client, std::unordered_map<int, ClientSession*>& clients, float deltaTime, float currentTime) {
    if (!client) return;

    // ������ ���
    CalculateMovement(client, deltaTime);

    // ���� �ùķ��̼� ����
    if (physicsEnabled) {
        ApplyPhysics(client, deltaTime);
    }

    // �÷��̾� ���� ������Ʈ
    UpdatePlayerState(client);

    // �÷��̾� �׼� ������Ʈ
    UpdatePlayerAction(client, clients);

    // ���� ��ġ ����
    client->PreviousPosition = client->Position;

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

    // �޸��� �ӵ� ����
    if (client->bRunRequested) {
        currentMoveSpeed *= settings.runMultiplier;
    }

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
    float yawRad = client->InputYaw * (3.14159265f / 180.0f);

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
    // ���� ��ġ�� ���� �ٴ� ���� ��������
    float currentGroundLevel = GetGroundLevelAtPosition(client->Position);

    // ���� ���� ó��
    if (client->Position.Z > currentGroundLevel + 1.0f) {
        client->State = EPlayerState::JUMPING;
        return;
    }

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

void GameUpdater::UpdatePlayerAction(ClientSession* client, std::unordered_map<int, ClientSession*>& clients)
{
    EPlayerAction previousAction = client->Action;

    // �⺻ �׼� �������� �ʱ�ȭ (���ϸ� �ּ� ����)
    // client->Action = EPlayerAction::NONE;

    // ���� ��û
    if (client->bAttackRequested)
    {
        client->Action = EPlayerAction::ATTACK;
        client->ActionTimer = 1.0f; // ���� ���� �ð� (��)
        client->bAttackHitProcessed = false; // ���� ó�� �ʱ�ȭ

        LOG_DEBUG("Attack action set for client " + std::to_string(client->id));
    }

    // ��� ��û
    if (client->bDefendRequested)
    {
        client->Action = EPlayerAction::DEFEND;
        LOG_DEBUG("Defend action set for client " + std::to_string(client->id));
    }

    // �׼� Ÿ�̸� ����
    if (client->ActionTimer > 0.0f)
    {
        client->ActionTimer -= 1.0f / 60.0f; // 60FPS ����
    }
    else
    {
        // Ÿ�̸� ���� �� ���� �ʱ�ȭ
        if (client->Action == EPlayerAction::ATTACK)
        {
            client->bAttackHitProcessed = false; // ���� ���� �����ϰ� �ʱ�ȭ
        }
        client->Action = EPlayerAction::NONE;
    }

    // �׼� ���� �α�
    if (previousAction != client->Action)
    {
        LOG_INFO("Action changed for client " + std::to_string(client->id) +
            " from " + std::to_string(static_cast<int>(previousAction)) +
            " to " + std::to_string(static_cast<int>(client->Action)));
    }

    // ���� ���� ó�� (�� ����)
    if (client->Action == EPlayerAction::ATTACK && !client->bAttackHitProcessed)
    {
        const float attackRange = 200.0f;

        for (const auto& pair : clients)
        {
            ClientSession* target = pair.second;

            if (!target || target == client || !target->IsConnected())
                continue;

            float dx = target->Position.X - client->Position.X;
            float dy = target->Position.Y - client->Position.Y;
            float distanceSq = dx * dx + dy * dy;

            if (distanceSq <= attackRange * attackRange)
            {
                if (target->Action == EPlayerAction::DEFEND)
                {
                    LOG_INFO("���� ��ȿȭ - ��� ��� ��. ������: " + std::to_string(client->id) +
                        ", ���: " + std::to_string(target->id));
                    continue;
                }

                if (target->HP <= 0)
                    continue;

                target->HP -= 1;
                if (target->HP < 0) target->HP = 0;

                StatusPacket status;
                status.Header.PacketType = EPacketType::PLAYER_STATUS_INFO;
                status.Header.PacketSize = sizeof(StatusPacket);
                status.ClientId = target->id;
                status.HP = target->HP;

                NetworkSessionManager::SendPacketSafe(target, &status, sizeof(status), "SendStatusPacket");

                LOG_INFO("���� ���� - ������: " + std::to_string(client->id) +
                    ", ���: " + std::to_string(target->id) +
                    ", ���� HP: " + std::to_string(target->HP));
            }
        }

        client->bAttackHitProcessed = true; // �� ���� ���� ó��
    }
}

void GameUpdater::ApplyPhysics(ClientSession* client, float deltaTime) {
    // �߷� ����
    ApplyGravity(client, deltaTime);

    // ���� �浹 üũ
    CheckGroundCollision(client);
}

void GameUpdater::ApplyGravity(ClientSession* client, float deltaTime) {
    // ���� ��ġ�� ���� �ٴ� ���� ���
    float currentGroundLevel = GetGroundLevelAtPosition(client->Position);

    // ���麸�� ���� ���� ���� �߷� ����
    if (client->Position.Z > currentGroundLevel) {
        client->Velocity.Z -= settings.gravity * deltaTime;
    }
}

void GameUpdater::CheckGroundCollision(ClientSession* client) {
    // ���� ��ġ�� ���� �ٴ� ���� ���
    float currentGroundLevel = GetGroundLevelAtPosition(client->Position);

    // ���� �Ʒ��� �������� �ʵ��� ó��
    if (client->Position.Z <= currentGroundLevel) {
        client->Position.Z = currentGroundLevel;

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
    float dx = client->Position.X - client->PreviousPosition.X;
    float dy = client->Position.Y - client->PreviousPosition.Y;
    float dz = client->Position.Z - client->PreviousPosition.Z;
    float movedDistance = sqrt(dx * dx + dy * dy + dz * dz);

    // ������Ʈ ���� üũ
    bool significantMovement = movedDistance > settings.minUpdateDistance;
    bool stateChanged = client->State != client->PreviousState;
    bool timeElapsed = (currentTime - client->LastUpdateTime) > settings.updateInterval;

    return significantMovement || stateChanged || timeElapsed;
}

void GameUpdater::BroadcastPositionUpdate(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients) {
    // ȸ�� ���� ������Ʈ
    sourceClient->Rotation.Pitch = sourceClient->InputPitch;
    sourceClient->Rotation.Yaw = sourceClient->InputYaw;
    sourceClient->Rotation.Roll = sourceClient->InputRoll;

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

bool GameUpdater::LoadHeightmap(const std::string& filepath) {
    LOG_INFO("Starting heightmap load: " + filepath);

    // ��Ÿ������ ���� �ε�
    std::string metaPath = filepath + "_meta.txt";
    std::ifstream metaFile(metaPath);
    if (!metaFile.is_open()) {
        LOG_ERROR("Failed to open heightmap metadata file: " + metaPath);
        return false;
    }

    std::string metaLine;
    std::getline(metaFile, metaLine);
    metaFile.close();

    // ��Ÿ������ �Ľ�: width,height,minX,minY,maxX,maxY,zScale,zOffset
    std::istringstream ss(metaLine);
    std::string token;

    try {
        std::getline(ss, token, ','); heightmap.width = std::stoi(token);
        std::getline(ss, token, ','); heightmap.height = std::stoi(token);
        std::getline(ss, token, ','); heightmap.minX = std::stof(token);
        std::getline(ss, token, ','); heightmap.minY = std::stof(token);
        std::getline(ss, token, ','); heightmap.maxX = std::stof(token);
        std::getline(ss, token, ','); heightmap.maxY = std::stof(token);
        std::getline(ss, token, ','); heightmap.zScale = std::stof(token);
        std::getline(ss, token, ','); heightmap.zOffset = std::stof(token);
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to parse heightmap metadata: " + std::string(e.what()));
        return false;
    }

    LOG_INFO("Heightmap metadata loaded:");
    LOG_INFO("  Size: " + std::to_string(heightmap.width) + "x" + std::to_string(heightmap.height));
    LOG_INFO("  World bounds: X(" + std::to_string(heightmap.minX) + " to " + std::to_string(heightmap.maxX) + ")");
    LOG_INFO("  World bounds: Y(" + std::to_string(heightmap.minY) + " to " + std::to_string(heightmap.maxY) + ")");
    LOG_INFO("  Z scale: " + std::to_string(heightmap.zScale) + ", Z offset: " + std::to_string(heightmap.zOffset));

    // ���� ������ ���� �ε�
    std::string dataPath = filepath + ".bin";
    std::ifstream heightFile(dataPath, std::ios::binary);
    if (!heightFile.is_open()) {
        LOG_ERROR("Failed to open heightmap data file: " + dataPath);
        return false;
    }

    // ���� ũ�� Ȯ��
    heightFile.seekg(0, std::ios::end);
    size_t fileSize = heightFile.tellg();
    heightFile.seekg(0, std::ios::beg);

    size_t expectedSize = heightmap.width * heightmap.height * sizeof(uint16_t);
    if (fileSize != expectedSize) {
        LOG_ERROR("Heightmap file size mismatch. Expected: " + std::to_string(expectedSize) +
            ", Actual: " + std::to_string(fileSize));
        return false;
    }

    // ���� ������ �ε�
    heightmap.heights.resize(heightmap.width * heightmap.height);
    heightFile.read(reinterpret_cast<char*>(heightmap.heights.data()), fileSize);
    heightFile.close();

    heightmap.isLoaded = true;

    LOG_INFO("Heightmap loaded successfully!");
    LOG_INFO("  Data points: " + std::to_string(heightmap.heights.size()));

    return true;
}

float GameUpdater::GetGroundLevelAtPosition(const Vec3& position) {
    if (!heightmap.isLoaded) {
        return settings.groundLevel;  // �⺻�� ��ȯ
    }

    // ���� ��ǥ�� �ؽ�ó ��ǥ�� ��ȯ
    float normalizedX = (position.X - heightmap.minX) / (heightmap.maxX - heightmap.minX);
    float normalizedY = (position.Y - heightmap.minY) / (heightmap.maxY - heightmap.minY);

    // ���� üũ
    if (normalizedX < 0.0f || normalizedX >= 1.0f ||
        normalizedY < 0.0f || normalizedY >= 1.0f) {
        LOG_DEBUG("Position out of heightmap bounds: (" + std::to_string(position.X) +
            ", " + std::to_string(position.Y) + ")");
        return settings.groundLevel;
    }

    // �ؼ� ��ǥ ���
    float texelX = normalizedX * (heightmap.width - 1);
    float texelY = normalizedY * (heightmap.height - 1);

    // ���̸��Ͼ� ������ ���� �ε���
    int x0 = static_cast<int>(texelX);
    int y0 = static_cast<int>(texelY);
    int x1 = std::min(x0 + 1, heightmap.width - 1);
    int y1 = std::min(y0 + 1, heightmap.height - 1);

    // ���� ����ġ
    float fx = texelX - x0;
    float fy = texelY - y0;

    // 4�� ���� ���̰� ��������
    uint16_t h00 = heightmap.heights[y0 * heightmap.width + x0];
    uint16_t h10 = heightmap.heights[y0 * heightmap.width + x1];
    uint16_t h01 = heightmap.heights[y1 * heightmap.width + x0];
    uint16_t h11 = heightmap.heights[y1 * heightmap.width + x1];

    // ���̸��Ͼ� ����
    float h0 = h00 * (1.0f - fx) + h10 * fx;
    float h1 = h01 * (1.0f - fx) + h11 * fx;
    float finalHeight = h0 * (1.0f - fy) + h1 * fy;

    // uint16 ���̰��� ���� ���� ���̷� ��ȯ
    float worldHeight = (finalHeight / 65535.0f) * 1024.0f - 512.0f;  // -512 ~ 512 ����
    worldHeight = worldHeight * heightmap.zScale + heightmap.zOffset;

    return worldHeight;
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