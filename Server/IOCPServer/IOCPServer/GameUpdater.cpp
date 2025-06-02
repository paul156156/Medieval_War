#include "GameUpdater.h"
#include "Logger.h"
#include "PacketDispatcher.h"
#include "NetworkSessionManager.h"
#include <cmath>
#include <chrono>

GameUpdater::GameUpdater() {
    LOG_INFO("게임 업데이터 초기화 시작");

    // 높이맵 로드 시도
    if (LoadHeightmap("heightmap")) {

        LOG_INFO("Heightmap 로드 완료!");
    }
    else {
        LOG_WARNING("heightmap 로드 실패, 기본 ground level: " +
            std::to_string(settings.groundLevel));
    }

    // 디버깅을 위해 파일 존재 여부 체크
    std::ifstream metaFile("../../Data/heightmap_meta.txt");
    std::ifstream dataFile("../../Data/heightmap.bin");

    LOG_INFO("Meta file exists: " + std::string(metaFile.good() ? "Yes" : "No"));
    LOG_INFO("Data file exists: " + std::string(dataFile.good() ? "Yes" : "No"));

    LOG_INFO("게임 업데이터 초기화 완료");
}

GameUpdater::~GameUpdater() {
    LOG_INFO("게임 업데이터 정리 완료");
}

void GameUpdater::UpdateClients(float deltaTime, std::unordered_map<int, ClientSession*>& clients, std::shared_mutex& clientsMutex) {
    auto updateStart = std::chrono::high_resolution_clock::now();

    // 델타 타임 검증 및 보정
    if (deltaTime > 0.5f) {
        LOG_WARNING("비정상적으로 큰 델타 타임: " + std::to_string(deltaTime) + "초. 0.5초로 제한");
        deltaTime = 0.5f;
    }

    const float currentTime = GetTickCount64() / 1000.0f;
    std::vector<int> clientsToRemove;
    updatedClientCount = 0;

    // 클라이언트 업데이트 (읽기 락 사용)
    {
        std::shared_lock<std::shared_mutex> lock(clientsMutex);

        for (auto& pair : clients) {
            ClientSession* client = pair.second;
            if (!client) {
                LOG_WARNING("null 클라이언트 세션 발견");
                continue;
            }

            // 타임아웃 체크
            if (client->IsTimedOut(currentTime)) {
                LOG_WARNING("클라이언트 타임아웃 - ID: " + std::to_string(client->id) +
                    ", 마지막 Ping: " + std::to_string(currentTime - client->LastPingTime) + "초 전");
                clientsToRemove.push_back(client->id);
                continue;
            }

            // 클라이언트 업데이트
            UpdateClient(client, clients, deltaTime, currentTime);

            // 위치 브로드캐스트 필요시 수행
            if (ShouldUpdatePosition(client, currentTime)) {
                BroadcastPositionUpdate(client, clients);
                client->LastUpdateTime = currentTime;
                client->PreviousState = client->State;
            }

            // 입력 상태 리셋
            client->bRunRequested = false;
            client->bJumpRequested = false;
            client->bAttackRequested = false;
            client->bDefendRequested = false;

            // 이전 속도 저장
            client->PreviousVelocity = client->Velocity;
            updatedClientCount++;
        }
    }

    // 타임아웃된 클라이언트 제거 (쓰기 락 필요)
    if (!clientsToRemove.empty()) {
        std::unique_lock<std::shared_mutex> lock(clientsMutex);
        for (int clientId : clientsToRemove) {
            auto it = clients.find(clientId);
            if (it != clients.end()) {
                clients.erase(it);
                LOG_INFO("타임아웃으로 클라이언트 제거됨 - ID: " + std::to_string(clientId));
            }
        }
    }

    // 성능 측정
    auto updateEnd = std::chrono::high_resolution_clock::now();
    float updateTime = std::chrono::duration<float, std::milli>(updateEnd - updateStart).count();
    UpdatePerformanceStats(updateTime);
}

void GameUpdater::UpdateClient(ClientSession* client, std::unordered_map<int, ClientSession*>& clients, float deltaTime, float currentTime) {
    if (!client) return;

    // 움직임 계산
    CalculateMovement(client, deltaTime);

    // 물리 시뮬레이션 적용
    if (physicsEnabled) {
        ApplyPhysics(client, deltaTime);
    }

    // 플레이어 상태 업데이트
    UpdatePlayerState(client);

    // 플레이어 액션 업데이트
    UpdatePlayerAction(client, clients);

    // 이전 위치 저장
    client->PreviousPosition = client->Position;

    // 위치 업데이트
    client->Position.X += client->Velocity.X * deltaTime;
    client->Position.Y += client->Velocity.Y * deltaTime;
    client->Position.Z += client->Velocity.Z * deltaTime;

    // 월드 경계 체크
    ApplyWorldBounds(client);
}

void GameUpdater::CalculateMovement(ClientSession* client, float deltaTime) {
    // 입력값 기반 이동 방향 계산
    Vec3 moveDir = CalculateMovementDirection(client);

    // 기본 이동 속도 적용
    float currentMoveSpeed = settings.moveSpeed;

    // 달리기 속도 보정
    if (client->bRunRequested) {
        currentMoveSpeed *= settings.runMultiplier;
    }

    // 수평 속도 설정
    client->Velocity.X = moveDir.X * currentMoveSpeed;
    client->Velocity.Y = moveDir.Y * currentMoveSpeed;

    // 점프 처리
    if (client->bJumpRequested && client->Position.Z <= settings.groundLevel + 1.0f) {
        client->Velocity.Z = settings.jumpVelocity;
        LOG_DEBUG("점프 실행 - 클라이언트 ID: " + std::to_string(client->id));
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

    // 정규화
    float magnitude = sqrt(moveDir.X * moveDir.X + moveDir.Y * moveDir.Y);
    if (magnitude > 0.0f) {
        moveDir.X /= magnitude;
        moveDir.Y /= magnitude;
    }

    return moveDir;
}

void GameUpdater::UpdatePlayerState(ClientSession* client) {
    // 현재 위치의 실제 바닥 높이 가져오기
    float currentGroundLevel = GetGroundLevelAtPosition(client->Position);

    // 점프 상태 처리
    if (client->Position.Z > currentGroundLevel + 1.0f) {
        client->State = EPlayerState::JUMPING;
        return;
    }

    // 이동 상태 처리
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

    // 기본 액션 없음으로 초기화 (원하면 주석 해제)
    // client->Action = EPlayerAction::NONE;

    // 공격 요청
    if (client->bAttackRequested)
    {
        client->Action = EPlayerAction::ATTACK;
        client->ActionTimer = 1.0f; // 공격 지속 시간 (초)
        client->bAttackHitProcessed = false; // 공격 처리 초기화

        LOG_DEBUG("Attack action set for client " + std::to_string(client->id));
    }

    // 방어 요청
    if (client->bDefendRequested)
    {
        client->Action = EPlayerAction::DEFEND;
        LOG_DEBUG("Defend action set for client " + std::to_string(client->id));
    }

    // 액션 타이머 감소
    if (client->ActionTimer > 0.0f)
    {
        client->ActionTimer -= 1.0f / 60.0f; // 60FPS 기준
    }
    else
    {
        // 타이머 만료 시 상태 초기화
        if (client->Action == EPlayerAction::ATTACK)
        {
            client->bAttackHitProcessed = false; // 다음 공격 가능하게 초기화
        }
        client->Action = EPlayerAction::NONE;
    }

    // 액션 변경 로그
    if (previousAction != client->Action)
    {
        LOG_INFO("Action changed for client " + std::to_string(client->id) +
            " from " + std::to_string(static_cast<int>(previousAction)) +
            " to " + std::to_string(static_cast<int>(client->Action)));
    }

    // 실제 공격 처리 (한 번만)
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
                    LOG_INFO("공격 무효화 - 대상 방어 중. 공격자: " + std::to_string(client->id) +
                        ", 대상: " + std::to_string(target->id));
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

                LOG_INFO("공격 성공 - 공격자: " + std::to_string(client->id) +
                    ", 대상: " + std::to_string(target->id) +
                    ", 남은 HP: " + std::to_string(target->HP));
            }
        }

        client->bAttackHitProcessed = true; // 한 번만 공격 처리
    }
}

void GameUpdater::ApplyPhysics(ClientSession* client, float deltaTime) {
    // 중력 적용
    ApplyGravity(client, deltaTime);

    // 지면 충돌 체크
    CheckGroundCollision(client);
}

void GameUpdater::ApplyGravity(ClientSession* client, float deltaTime) {
    // 현재 위치의 실제 바닥 높이 계산
    float currentGroundLevel = GetGroundLevelAtPosition(client->Position);

    // 지면보다 높이 있을 때만 중력 적용
    if (client->Position.Z > currentGroundLevel) {
        client->Velocity.Z -= settings.gravity * deltaTime;
    }
}

void GameUpdater::CheckGroundCollision(ClientSession* client) {
    // 현재 위치의 실제 바닥 높이 계산
    float currentGroundLevel = GetGroundLevelAtPosition(client->Position);

    // 지면 아래로 떨어지지 않도록 처리
    if (client->Position.Z <= currentGroundLevel) {
        client->Position.Z = currentGroundLevel;

        // 하향 속도만 0으로 설정
        if (client->Velocity.Z < 0) {
            client->Velocity.Z = 0.0f;
        }

        // 점프 상태에서 착지 시 상태 변경
        if (client->State == EPlayerState::JUMPING) {
            client->State = EPlayerState::IDLE;
        }
    }
}

void GameUpdater::ApplyWorldBounds(ClientSession* client) {
    // 월드 경계 내로 위치 제한
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
    // 이동 거리 계산
    float dx = client->Position.X - client->PreviousPosition.X;
    float dy = client->Position.Y - client->PreviousPosition.Y;
    float dz = client->Position.Z - client->PreviousPosition.Z;
    float movedDistance = sqrt(dx * dx + dy * dy + dz * dz);

    // 업데이트 조건 체크
    bool significantMovement = movedDistance > settings.minUpdateDistance;
    bool stateChanged = client->State != client->PreviousState;
    bool timeElapsed = (currentTime - client->LastUpdateTime) > settings.updateInterval;

    return significantMovement || stateChanged || timeElapsed;
}

void GameUpdater::BroadcastPositionUpdate(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients) {
    // 회전 정보 업데이트
    sourceClient->Rotation.Pitch = sourceClient->InputPitch;
    sourceClient->Rotation.Yaw = sourceClient->InputYaw;
    sourceClient->Rotation.Roll = sourceClient->InputRoll;

    // 위치 업데이트 브로드캐스트
    PacketDispatcher::BroadcastPlayerUpdate(sourceClient, clients);
}

void GameUpdater::SetUpdateRate(float updatesPerSecond) {
    if (updatesPerSecond > 0.0f && updatesPerSecond <= 120.0f) {
        targetUpdateRate = updatesPerSecond;
        settings.updateInterval = 1.0f / updatesPerSecond;
        LOG_INFO("업데이트 주기 변경됨: " + std::to_string(updatesPerSecond) + "Hz");
    }
}

void GameUpdater::SetPhysicsEnabled(bool enabled) {
    physicsEnabled = enabled;
    LOG_INFO("물리 시뮬레이션 " + std::string(enabled ? "활성화" : "비활성화"));
}

bool GameUpdater::LoadHeightmap(const std::string& filepath) {
    LOG_INFO("Starting heightmap load: " + filepath);

    // 메타데이터 파일 로드
    std::string metaPath = filepath + "_meta.txt";
    std::ifstream metaFile(metaPath);
    if (!metaFile.is_open()) {
        LOG_ERROR("Failed to open heightmap metadata file: " + metaPath);
        return false;
    }

    std::string metaLine;
    std::getline(metaFile, metaLine);
    metaFile.close();

    // 메타데이터 파싱: width,height,minX,minY,maxX,maxY,zScale,zOffset
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

    // 높이 데이터 파일 로드
    std::string dataPath = filepath + ".bin";
    std::ifstream heightFile(dataPath, std::ios::binary);
    if (!heightFile.is_open()) {
        LOG_ERROR("Failed to open heightmap data file: " + dataPath);
        return false;
    }

    // 파일 크기 확인
    heightFile.seekg(0, std::ios::end);
    size_t fileSize = heightFile.tellg();
    heightFile.seekg(0, std::ios::beg);

    size_t expectedSize = heightmap.width * heightmap.height * sizeof(uint16_t);
    if (fileSize != expectedSize) {
        LOG_ERROR("Heightmap file size mismatch. Expected: " + std::to_string(expectedSize) +
            ", Actual: " + std::to_string(fileSize));
        return false;
    }

    // 높이 데이터 로드
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
        return settings.groundLevel;  // 기본값 반환
    }

    // 월드 좌표를 텍스처 좌표로 변환
    float normalizedX = (position.X - heightmap.minX) / (heightmap.maxX - heightmap.minX);
    float normalizedY = (position.Y - heightmap.minY) / (heightmap.maxY - heightmap.minY);

    // 범위 체크
    if (normalizedX < 0.0f || normalizedX >= 1.0f ||
        normalizedY < 0.0f || normalizedY >= 1.0f) {
        LOG_DEBUG("Position out of heightmap bounds: (" + std::to_string(position.X) +
            ", " + std::to_string(position.Y) + ")");
        return settings.groundLevel;
    }

    // 텍셀 좌표 계산
    float texelX = normalizedX * (heightmap.width - 1);
    float texelY = normalizedY * (heightmap.height - 1);

    // 바이리니어 보간을 위한 인덱스
    int x0 = static_cast<int>(texelX);
    int y0 = static_cast<int>(texelY);
    int x1 = std::min(x0 + 1, heightmap.width - 1);
    int y1 = std::min(y0 + 1, heightmap.height - 1);

    // 보간 가중치
    float fx = texelX - x0;
    float fy = texelY - y0;

    // 4개 샘플 높이값 가져오기
    uint16_t h00 = heightmap.heights[y0 * heightmap.width + x0];
    uint16_t h10 = heightmap.heights[y0 * heightmap.width + x1];
    uint16_t h01 = heightmap.heights[y1 * heightmap.width + x0];
    uint16_t h11 = heightmap.heights[y1 * heightmap.width + x1];

    // 바이리니어 보간
    float h0 = h00 * (1.0f - fx) + h10 * fx;
    float h1 = h01 * (1.0f - fx) + h11 * fx;
    float finalHeight = h0 * (1.0f - fy) + h1 * fy;

    // uint16 높이값을 실제 월드 높이로 변환
    float worldHeight = (finalHeight / 65535.0f) * 1024.0f - 512.0f;  // -512 ~ 512 범위
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
    // 지수 이동 평균으로 평균 업데이트 시간 계산
    const float alpha = 0.1f;
    averageUpdateTime = averageUpdateTime * (1.0f - alpha) + updateTime * alpha;

    // 성능 경고 (10ms 초과시)
    if (updateTime > 10.0f) {
        LOG_WARNING("게임 업데이트 시간이 길음: " + std::to_string(updateTime) + "ms" +
            ", 클라이언트 수: " + std::to_string(updatedClientCount));
    }
}