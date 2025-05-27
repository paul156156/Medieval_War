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

    // ���� ������Ʈ
    void UpdateClients(float deltaTime, std::unordered_map<int, ClientSession*>& clients, std::shared_mutex& clientsMutex);

    // ����
    void SetUpdateRate(float updatesPerSecond);
    void SetPhysicsEnabled(bool enabled);

    // ���
    int GetUpdatedClientCount() const;
    float GetAverageUpdateTime() const;

private:
    // ���� Ŭ���̾�Ʈ ������Ʈ
    void UpdateClient(ClientSession* client, float deltaTime, float currentTime);

    // ���� �ùķ��̼�
    void ApplyPhysics(ClientSession* client, float deltaTime);
    void ApplyGravity(ClientSession* client, float deltaTime);
    void CheckGroundCollision(ClientSession* client);
    void ApplyWorldBounds(ClientSession* client);

    // ������ ���
    void CalculateMovement(ClientSession* client, float deltaTime);
    Vec3 CalculateMovementDirection(ClientSession* client);
    void UpdatePlayerState(ClientSession* client);

    // ��ġ ������Ʈ ����ȭ
    bool ShouldUpdatePosition(ClientSession* client, float currentTime);
    void BroadcastPositionUpdate(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients);

    // Ÿ�Ӿƿ� ó��
    void CheckClientTimeouts(std::unordered_map<int, ClientSession*>& clients, float currentTime, std::vector<int>& clientsToRemove);

    // ���� ����
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

    // ���
    int updatedClientCount = 0;
    float averageUpdateTime = 0.0f;
    bool physicsEnabled = true;
    float targetUpdateRate = 60.0f;

    // ���� ����
    void UpdatePerformanceStats(float updateTime);
};