#include "GameUpdater.h"
#include "Logger.h"
#include "PacketDispatcher.h"
#include <cmath>
#include <chrono>

GameUpdater::GameUpdater() {
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
            UpdateClient(client, deltaTime, currentTime);

            // 위치 브로드캐스트 필요시 수행
            if (ShouldUpdatePosition(client, currentTime)) {
                BroadcastPositionUpdate(client, clients);
                client->LastUpdateTime = currentTime;
                client->PreviousState = client->State;
            }

            // 입력 상태 리셋
            client->bJumpRequested = false;
            client->bAttackRequested = false;
            client->bRunRequested = false;
            //client->bCrouchRequested = false;

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

void GameUpdater::UpdateClient(ClientSession* client, float deltaTime, float currentTime) {
    if (!client) return;

    // 움직임 계산
    CalculateMovement(client, deltaTime);

    // 물리 시뮬레이션 적용
    if (physicsEnabled) {
        ApplyPhysics(client, deltaTime);
    }

    // 플레이어 상태 업데이트
    UpdatePlayerState(client);

    // 이전 위치 저장
    client->LastPosition = client->Position;

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

    // 달리기/웅크리기 속도 보정
    if (client->bRunRequested) {
        currentMoveSpeed *= settings.runMultiplier;
    }
    //else if (client->bCrouchRequested) {
    //    currentMoveSpeed *= settings.crouchMultiplier;
    //}

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
    float yawRad = client->ControlRotationYaw * (3.14159265f / 180.0f);

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
    // 공격 상태 우선 처리
    if (client->bAttackRequested) {
        client->State = EPlayerState::ATTACKING;
        return;
    }

    // 점프 상태 처리
    if (client->Position.Z > settings.groundLevel + 1.0f) {
        client->State = EPlayerState::JUMPING;
        return;
    }

    //// 웅크리기 상태 처리
    //if (client->bCrouchRequested) {
    //    client->State = EPlayerState::CROUCHING;
    //    return;
    //}

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

void GameUpdater::ApplyPhysics(ClientSession* client, float deltaTime) {
    // 중력 적용
    ApplyGravity(client, deltaTime);

    // 지면 충돌 체크
    CheckGroundCollision(client);
}

void GameUpdater::ApplyGravity(ClientSession* client, float deltaTime) {
    // 지면보다 높이 있을 때만 중력 적용
    if (client->Position.Z > settings.groundLevel) {
        client->Velocity.Z -= settings.gravity * deltaTime;
    }
}

void GameUpdater::CheckGroundCollision(ClientSession* client) {
    // 지면 아래로 떨어지지 않도록 처리
    if (client->Position.Z <= settings.groundLevel) {
        client->Position.Z = settings.groundLevel;

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
    float dx = client->Position.X - client->LastPosition.X;
    float dy = client->Position.Y - client->LastPosition.Y;
    float dz = client->Position.Z - client->LastPosition.Z;
    float movedDistance = sqrt(dx * dx + dy * dy + dz * dz);

    // 업데이트 조건 체크
    bool significantMovement = movedDistance > settings.minUpdateDistance;
    bool stateChanged = client->State != client->PreviousState;
    bool timeElapsed = (currentTime - client->LastUpdateTime) > settings.updateInterval;

    return significantMovement || stateChanged || timeElapsed;
}

void GameUpdater::BroadcastPositionUpdate(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients) {
    // 회전 정보 업데이트
    sourceClient->Rotation.Pitch = sourceClient->ControlRotationPitch;
    sourceClient->Rotation.Yaw = sourceClient->ControlRotationYaw;
    sourceClient->Rotation.Roll = sourceClient->ControlRotationRoll;

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