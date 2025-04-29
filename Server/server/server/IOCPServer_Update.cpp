#include "IOCPServer.h"
#include "Logger.h"
#include "PacketTypes.h"

void IOCPServer::Update(float DeltaTime)
{
    if (DeltaTime > 0.5f) {
        LOG_WARNING("비정상적으로 긴 델타 타임: " + std::to_string(DeltaTime) + "초");
        // 너무 긴 델타 타임을 제한하여 물리 계산 오차 방지
        DeltaTime = 0.5f;
    }
    const float CurrentTime = GetTickCount64() / 1000.0f; // 초 단위

    std::vector<int> ClientsToRemove;

    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        for (auto& pair : clients)
        {
            ClientSession* client = pair.second;
            if (!client)
            {
                LOG_WARNING("[Update] null ClientSession 발견");
                continue;
            }
            float TimeSinceLastPing = CurrentTime - client->LastPingTime;

            // (2) 5초 넘으면 제거 대상
            if (TimeSinceLastPing > 5.0f)
            {
                LOG_WARNING("클라이언트 Ping 타임아웃 발생 - ID: " + std::to_string(client->id) +
                    ", 마지막 Ping 후 경과 시간: " + std::to_string(TimeSinceLastPing) + "초");
                ClientsToRemove.push_back(client->id);
            }

            // --- 이동 방향 계산 (시야 기준) 수정 ---
            float Forward = client->InputForward;
            float Right = client->InputRight;

            float YawRad = client->ControlRotationYaw * (3.14159265f / 180.0f);
            float CosYaw = cos(YawRad);
            float SinYaw = sin(YawRad);

            Vec3 MoveDir;
            MoveDir.X = Forward * CosYaw + Right * SinYaw;
            MoveDir.Y = Forward * SinYaw - Right * CosYaw;
            MoveDir.Z = 0.0f;

            float Magnitude = sqrt(MoveDir.X * MoveDir.X + MoveDir.Y * MoveDir.Y);
            if (Magnitude > 0.0f)
            {
                MoveDir.X /= Magnitude;
                MoveDir.Y /= Magnitude;
            }

            const float MoveSpeed = 500.0f;
            client->Velocity.X = MoveDir.X * MoveSpeed;
            client->Velocity.Y = MoveDir.Y * MoveSpeed;

            // 점프 처리
            if (client->bJumpRequested && client->Position.Z <= 90.0f + 1.0f)
            {
                client->Velocity.Z = 600.0f;
                client->State = EPlayerState::JUMPING;
                client->bJumpRequested = true;
            }

            // 공격 처리
            if (client->bAttackRequested)
            {
                client->State = EPlayerState::ATTACKING;
				client->bAttackRequested = true;
            }
            else if (Magnitude > 0.0f)
            {
                client->State = EPlayerState::WALKING;
            }
            else
            {
                if (client->State != EPlayerState::JUMPING)
                    client->State = EPlayerState::IDLE;
            }

            // 이전 위치 저장
            client->LastPosition = client->Position;

            // 위치 이동
            client->Position.X += client->Velocity.X * DeltaTime;
            client->Position.Y += client->Velocity.Y * DeltaTime;
            client->Position.Z += client->Velocity.Z * DeltaTime;

            LOG_INFO("위치 업데이트 - 클라이언트 ID: " + std::to_string(client->id) +
                ", 위치: X=" + std::to_string(client->Position.X) +
                ", Y=" + std::to_string(client->Position.Y) +
                ", Z=" + std::to_string(client->Position.Z) +
                ", 속도: X=" + std::to_string(client->Velocity.X) +
                ", Y=" + std::to_string(client->Velocity.Y) +
                ", Z=" + std::to_string(client->Velocity.Z));

            // 중력 적용
            const float Gravity = 980.0f;
            client->Velocity.Z -= Gravity * DeltaTime;

            // 땅 착지
            if (client->Position.Z <= 90.0f)
            {
                client->Position.Z = 90.0f;
                if (client->Velocity.Z < 0)
                    client->Velocity.Z = 0.0f;

                if (client->State == EPlayerState::JUMPING)
                    client->State = EPlayerState::IDLE;
            }

            // 월드 경계 충돌 처리 (예시: -5000~5000)
            const float WorldBoundary = 1000.0f;
            if (client->Position.X < -WorldBoundary) client->Position.X = -WorldBoundary;
            if (client->Position.X > WorldBoundary) client->Position.X = WorldBoundary;
            if (client->Position.Y < -WorldBoundary) client->Position.Y = -WorldBoundary;
            if (client->Position.Y > WorldBoundary) client->Position.Y = WorldBoundary;

            // 위치가 충분히 변했을 때만 업데이트 패킷 전송 (대역폭 최적화)
            const float MinUpdateDistance = 0.1f; // 최소 0.1 유닛 이동해야 패킷 전송
            float distMoved = sqrt(
                pow(client->Position.X - client->LastPosition.X, 2) +
                pow(client->Position.Y - client->LastPosition.Y, 2) +
                pow(client->Position.Z - client->LastPosition.Z, 2)
            );

            // 충분히 이동했거나, 상태가 변경되었거나, 일정 시간이 지난 경우에만 브로드캐스트
            const float UpdateInterval = 0.1f; // 최대 0.1초마다 업데이트
            float currentTime = GetTickCount64() / 1000.0f;
            if (distMoved > MinUpdateDistance ||
                client->State != client->PreviousState ||
                currentTime - client->LastUpdateTime > UpdateInterval)
            {

                LOG_INFO("[서버] BroadcastPosition 준비 완료 - ClientId: " + std::to_string(client->id) +
                    ", distMoved: " + std::to_string(distMoved) +
                    ", State: " + std::to_string((int)client->State) +
                    ", TimeSinceLastUpdate: " + std::to_string(currentTime - client->LastUpdateTime));


                client->LastUpdateTime = currentTime;
                client->PreviousState = client->State;

                // 클라이언트에 위치 정보 전송
                BroadcastPosition(client);
            }

            client->bJumpRequested = false;
            client->bAttackRequested = false;
        }
    }
    for (int clientId : ClientsToRemove) {
        RemoveClient(clientId);
    }
}

void IOCPServer::BroadcastPosition(ClientSession* sourceClient)
{
    PositionPacket packet;
    packet.Header.PacketType = EPacketType::PLAYER_POSITION_INFO;
    packet.Header.PacketSize = sizeof(PositionPacket);
    packet.ClientId = sourceClient->id;
    packet.Position = sourceClient->Position;
    packet.Velocity = sourceClient->Velocity;
    packet.State = sourceClient->State;

    LOG_INFO("[서버] BroadcastPosition 호출 - ClientId: " + std::to_string(sourceClient->id) +
        ", Position: (" + std::to_string(sourceClient->Position.X) + ", " +
        std::to_string(sourceClient->Position.Y) + ", " +
        std::to_string(sourceClient->Position.Z) + ")");


    // 전송 성공 카운트 (디버깅용)
    int successCount = 0;

    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;

        // 자신에게는 전송하지 않음 (클라이언트 권한에 따라 다르게 처리 가능)
        if (targetClient->id == sourceClient->id)
        {
            continue;
        }

        LOG_INFO("[서버] PositionUpdatePacket 전송 - From ClientId: " + std::to_string(sourceClient->id) +
            " To ClientId: " + std::to_string(targetClient->id));

        // 비동기 전송
        if (SendPacket(targetClient, &packet, sizeof(packet), "BroadcastPosition")) {
            successCount++;
        }
    }

    // 자세한 로그는 프레임마다 너무 많이 출력되므로 특정 조건에서만 출력
    // 예: 전송 실패가 있거나, 디버그 모드일 때
    if (successCount < clients.size() - 1) {
        LOG_WARNING("위치 브로드캐스트 일부 실패 - 클라이언트 ID: " +
            std::to_string(sourceClient->id) + ", 성공: " +
            std::to_string(successCount) + "/" +
            std::to_string(clients.size() - 1));
    }
}

void IOCPServer::SetupSpawnPositions()
{
    SpawnPositions.push_back({ 0.0f, 0.0f, 90.0f });
    SpawnPositions.push_back({ 300.0f, 0.0f, 90.0f });
    SpawnPositions.push_back({ -300.0f, 0.0f, 90.0f });
    SpawnPositions.push_back({ 0.0f, 300.0f, 90.0f });
    SpawnPositions.push_back({ 0.0f, -300.0f, 90.0f });
}
