#include "IOCPServer.h"
#include "Logger.h"
#include "PacketTypes.h"

void IOCPServer::Update(float DeltaTime)
{
    if (DeltaTime > 0.5f) {
        LOG_WARNING("������������ �� ��Ÿ Ÿ��: " + std::to_string(DeltaTime) + "��");
        // �ʹ� �� ��Ÿ Ÿ���� �����Ͽ� ���� ��� ���� ����
        DeltaTime = 0.5f;
    }
    const float CurrentTime = GetTickCount64() / 1000.0f; // �� ����

    std::vector<int> ClientsToRemove;

    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        for (auto& pair : clients)
        {
            ClientSession* client = pair.second;
            if (!client)
            {
                LOG_WARNING("[Update] null ClientSession �߰�");
                continue;
            }
            float TimeSinceLastPing = CurrentTime - client->LastPingTime;

            // (2) 5�� ������ ���� ���
            if (TimeSinceLastPing > 5.0f)
            {
                LOG_WARNING("Ŭ���̾�Ʈ Ping Ÿ�Ӿƿ� �߻� - ID: " + std::to_string(client->id) +
                    ", ������ Ping �� ��� �ð�: " + std::to_string(TimeSinceLastPing) + "��");
                ClientsToRemove.push_back(client->id);
            }

            // --- �̵� ���� ��� (�þ� ����) ���� ---
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

            // ���� ó��
            if (client->bJumpRequested && client->Position.Z <= 90.0f + 1.0f)
            {
                client->Velocity.Z = 600.0f;
                client->State = EPlayerState::JUMPING;
                client->bJumpRequested = true;
            }

            // ���� ó��
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

            // ���� ��ġ ����
            client->LastPosition = client->Position;

            // ��ġ �̵�
            client->Position.X += client->Velocity.X * DeltaTime;
            client->Position.Y += client->Velocity.Y * DeltaTime;
            client->Position.Z += client->Velocity.Z * DeltaTime;

            LOG_INFO("��ġ ������Ʈ - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
                ", ��ġ: X=" + std::to_string(client->Position.X) +
                ", Y=" + std::to_string(client->Position.Y) +
                ", Z=" + std::to_string(client->Position.Z) +
                ", �ӵ�: X=" + std::to_string(client->Velocity.X) +
                ", Y=" + std::to_string(client->Velocity.Y) +
                ", Z=" + std::to_string(client->Velocity.Z));

            // �߷� ����
            const float Gravity = 980.0f;
            client->Velocity.Z -= Gravity * DeltaTime;

            // �� ����
            if (client->Position.Z <= 90.0f)
            {
                client->Position.Z = 90.0f;
                if (client->Velocity.Z < 0)
                    client->Velocity.Z = 0.0f;

                if (client->State == EPlayerState::JUMPING)
                    client->State = EPlayerState::IDLE;
            }

            // ���� ��� �浹 ó�� (����: -5000~5000)
            const float WorldBoundary = 1000.0f;
            if (client->Position.X < -WorldBoundary) client->Position.X = -WorldBoundary;
            if (client->Position.X > WorldBoundary) client->Position.X = WorldBoundary;
            if (client->Position.Y < -WorldBoundary) client->Position.Y = -WorldBoundary;
            if (client->Position.Y > WorldBoundary) client->Position.Y = WorldBoundary;

            // ��ġ�� ����� ������ ���� ������Ʈ ��Ŷ ���� (�뿪�� ����ȭ)
            const float MinUpdateDistance = 0.1f; // �ּ� 0.1 ���� �̵��ؾ� ��Ŷ ����
            float distMoved = sqrt(
                pow(client->Position.X - client->LastPosition.X, 2) +
                pow(client->Position.Y - client->LastPosition.Y, 2) +
                pow(client->Position.Z - client->LastPosition.Z, 2)
            );

            // ����� �̵��߰ų�, ���°� ����Ǿ��ų�, ���� �ð��� ���� ��쿡�� ��ε�ĳ��Ʈ
            const float UpdateInterval = 0.1f; // �ִ� 0.1�ʸ��� ������Ʈ
            float currentTime = GetTickCount64() / 1000.0f;
            if (distMoved > MinUpdateDistance ||
                client->State != client->PreviousState ||
                currentTime - client->LastUpdateTime > UpdateInterval)
            {

                LOG_INFO("[����] BroadcastPosition �غ� �Ϸ� - ClientId: " + std::to_string(client->id) +
                    ", distMoved: " + std::to_string(distMoved) +
                    ", State: " + std::to_string((int)client->State) +
                    ", TimeSinceLastUpdate: " + std::to_string(currentTime - client->LastUpdateTime));


                client->LastUpdateTime = currentTime;
                client->PreviousState = client->State;

                // Ŭ���̾�Ʈ�� ��ġ ���� ����
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

    LOG_INFO("[����] BroadcastPosition ȣ�� - ClientId: " + std::to_string(sourceClient->id) +
        ", Position: (" + std::to_string(sourceClient->Position.X) + ", " +
        std::to_string(sourceClient->Position.Y) + ", " +
        std::to_string(sourceClient->Position.Z) + ")");


    // ���� ���� ī��Ʈ (������)
    int successCount = 0;

    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;

        // �ڽſ��Դ� �������� ���� (Ŭ���̾�Ʈ ���ѿ� ���� �ٸ��� ó�� ����)
        if (targetClient->id == sourceClient->id)
        {
            continue;
        }

        LOG_INFO("[����] PositionUpdatePacket ���� - From ClientId: " + std::to_string(sourceClient->id) +
            " To ClientId: " + std::to_string(targetClient->id));

        // �񵿱� ����
        if (SendPacket(targetClient, &packet, sizeof(packet), "BroadcastPosition")) {
            successCount++;
        }
    }

    // �ڼ��� �α״� �����Ӹ��� �ʹ� ���� ��µǹǷ� Ư�� ���ǿ����� ���
    // ��: ���� ���а� �ְų�, ����� ����� ��
    if (successCount < clients.size() - 1) {
        LOG_WARNING("��ġ ��ε�ĳ��Ʈ �Ϻ� ���� - Ŭ���̾�Ʈ ID: " +
            std::to_string(sourceClient->id) + ", ����: " +
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
