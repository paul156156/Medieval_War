#pragma once
#include "ClientSession.h"
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

class GameUpdater {
public:
    GameUpdater();
    ~GameUpdater();

    // 게임 업데이트
    void UpdateClients(float deltaTime, std::unordered_map<int, ClientSession*>& clients, std::shared_mutex& clientsMutex);

    // 설정
    void SetUpdateRate(float updatesPerSecond);
    void SetPhysicsEnabled(bool enabled);

    // 통계
    int GetUpdatedClientCount() const;
    float GetAverageUpdateTime() const;

private:
    // 개별 클라이언트 업데이트
    void UpdateClient(ClientSession* client, float deltaTime, float currentTime);

    // 물리 시뮬레이션
    void ApplyPhysics(ClientSession* client, float deltaTime);
    void ApplyGravity(ClientSession* client, float deltaTime);
    void CheckGroundCollision(ClientSession* client);
    void ApplyWorldBounds(ClientSession* client);

    // 움직임 계산
    void CalculateMovement(ClientSession* client, float deltaTime);
    Vec3 CalculateMovementDirection(ClientSession* client);
    void UpdatePlayerState(ClientSession* client);

    // 위치 업데이트 최적화
    bool ShouldUpdatePosition(ClientSession* client, float currentTime);
    void BroadcastPositionUpdate(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients);

    // 타임아웃 처리
    void CheckClientTimeouts(std::unordered_map<int, ClientSession*>& clients, float currentTime, std::vector<int>& clientsToRemove);

    // 게임 설정
    struct GameSettings {
        float moveSpeed = 500.0f;
        float runMultiplier = 2.0f;
        float crouchMultiplier = 0.5f;
        float jumpVelocity = 600.0f;
        float gravity = 980.0f;
        float groundLevel = 90.0f;
        float worldBoundary = 10000.0f;
        float minUpdateDistance = 0.1f;
        float updateInterval = 0.1f;
        float clientTimeout = 30.0f;
    } settings;

    // 통계
    int updatedClientCount = 0;
    float averageUpdateTime = 0.0f;
    bool physicsEnabled = true;
    float targetUpdateRate = 60.0f;

    // 성능 측정
    void UpdatePerformanceStats(float updateTime);
};