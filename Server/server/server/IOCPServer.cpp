#include "IOCPServer.h"
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include "PacketTypes.h"
#include "Logger.h"

IOCPServer::IOCPServer() : listenSocket(INVALID_SOCKET), completionPort(NULL), nextClientId(1), isRunning(true)
{
    Logger::GetInstance().Initialize();
    LOG_INFO("���� �ν��Ͻ� ������");
}

IOCPServer::~IOCPServer() {
    LOG_INFO("���� �Ҹ��� ȣ���");
    CleanUp();
}

std::string IOCPServer::GetSocketErrorString(int error) const
{
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: ������ ���� ȣ��Ʈ�� ���� �缳����";
    case WSAECONNABORTED: return "WSAECONNABORTED: ����Ʈ��� ���� �ߴ� �߻�";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: ���� �ð� �ʰ�";
    case WSAENETDOWN: return "WSAENETDOWN: ��Ʈ��ũ�� �ٿ��";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: ȣ��Ʈ�� ������ �� ����";
    case WSAEINTR: return "WSAEINTR: �Լ� ȣ���� �ߴܵ�";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: ���ҽ��� �Ͻ������� ��� �Ұ�";
    default: return "�� �� ���� ����: " + std::to_string(error);
    }
}

int IOCPServer::GetClientCount() const
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    return static_cast<int>(clients.size());
}

bool IOCPServer::Initialize(int port)
{
    LOG_INFO("���� �ʱ�ȭ ���� (��Ʈ: " + std::to_string(port) + ")");

    // ���� �ʱ�ȭ
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        LOG_ERROR("WSAStartup ����");
        return false;
    }
    LOG_INFO("���� �ʱ�ȭ ����");

    // ���� ����
    listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET)
    {
        LOG_ERROR("���� ���� ����: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("������ ���� ���� ����");

    // TCP ���� �ɼ� ����: LINGER ��Ȱ��ȭ�� ���� �ӵ� ���
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER �ɼ�
    if (setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        LOG_WARNING("LINGER �ɼ� ���� ����: " + std::to_string(WSAGetLastError()));
    }

    // TCP_NODELAY Ȱ��ȭ (Nagle �˰��� ��Ȱ��ȭ)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        LOG_WARNING("TCP_NODELAY �ɼ� ���� ����: " + std::to_string(WSAGetLastError()));
    }

    // ���ε�
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        LOG_ERROR("Bind ����: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("���� ���ε� ���� (��Ʈ: " + std::to_string(port) + ")");

    // ����
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        LOG_ERROR("Listen ����: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("������ ���۵�");

    // IOCP ����
    completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (completionPort == NULL)
    {
        LOG_ERROR("IOCP ���� ����: " + std::to_string(GetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("IOCP ���� ����");

    // CPU ���� Ȯ��
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors * 2;
    LOG_INFO("CPU �ھ� ��: " + std::to_string(sysInfo.dwNumberOfProcessors) + ", ������ �۾��� ������: " + std::to_string(threadCount));

    // �۾��� ������ ����
    for (int i = 0; i < threadCount; i++)
    {
        HANDLE thread = CreateThread(NULL, 0, WorkerThreadProc, this, 0, NULL);
        if (thread == NULL)
        {
            LOG_ERROR("�۾��� ������ ���� ����: " + std::to_string(GetLastError()));
            CleanUp();
            return false;
        }
        LOG_INFO("�۾��� ������ #" + std::to_string(i + 1) + " ������");
        CloseHandle(thread);
    }

    LOG_INFO("���� �ʱ�ȭ �Ϸ�");
    return true;
}

void IOCPServer::Run()
{
    LOG_INFO("���� ���� ����");
    uint64_t LastTickTime = GetTickCount64();
    uint64_t framesCount = 0;
    uint64_t lastFpsTime = GetTickCount64();
    float averageFrameTime = 0;

    while (isRunning)
    {
        uint64_t frameStartTime = GetTickCount64();

        uint64_t Now = GetTickCount64();
        float DeltaTime = (Now - LastTickTime) / 1000.0f; // �и��� �� ��
        LastTickTime = Now;

        // FPS ��� (1�ʸ���)
        framesCount++;
        if (Now - lastFpsTime > 1000) {
            float fps = static_cast<float>(framesCount) * 1000.0f / (Now - lastFpsTime);
            LOG_INFO("���� FPS: " + std::to_string(fps) + ", ��� ������ �ð�: " +
                std::to_string(averageFrameTime) + "ms, Ŭ���̾�Ʈ ��: " +
                std::to_string(GetClientCount()));

            framesCount = 0;
            lastFpsTime = Now;
        }

        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, NULL, 0);

        if (clientSocket != INVALID_SOCKET)
        {
            // 1. ���� ��û ������ ó��
            AcceptNewClients(clientSocket, clientAddr);
        }

        // 2. ��ü Ŭ���̾�Ʈ ������Ʈ
        Update(DeltaTime);

        // 3. ������ �ð� ���� �� ����
        uint64_t frameEndTime = GetTickCount64();
        uint64_t frameTime = frameEndTime - frameStartTime;

        // ���� �̵� ������� ��� ������ �ð� ��� (����ġ 0.1)
        averageFrameTime = averageFrameTime * 0.9f + frameTime * 0.1f;

        // ��ǥ ������ �ð� (16.67ms = �� 60 FPS)
        const uint64_t targetFrameTime = 16;

        if (frameTime < targetFrameTime) {
            Sleep(static_cast<DWORD>(targetFrameTime - frameTime));
        }
    }

    LOG_INFO("���� ���� ����");
}

void IOCPServer::AcceptNewClients(SOCKET clientSocket, SOCKADDR_IN clientAddr)
{
    // TCP ���� �ɼ� ����: LINGER ��Ȱ��ȭ�� ���� �ӵ� ���
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER �ɼ�
    if (setsockopt(clientSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        LOG_WARNING("Ŭ���̾�Ʈ LINGER �ɼ� ���� ����: " + std::to_string(WSAGetLastError()));
    }

    // TCP_NODELAY Ȱ��ȭ (Nagle �˰��� ��Ȱ��ȭ)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        LOG_WARNING("Ŭ���̾�Ʈ TCP_NODELAY �ɼ� ���� ����: " + std::to_string(WSAGetLastError()));
    }

    // ���� �ڵ� = Ŭ���̾�Ʈ ���� ����
    ClientSession* client = new ClientSession();
    client->socket = clientSocket;
    client->addr = clientAddr;
    client->id = nextClientId++;
    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);
    client->Position = { 0.0f, 0.0f, 0.0f };
    client->LastPosition = { 0.0f, 0.0f, 0.0f };
    client->Rotation = { 0.0f, 0.0f, 0.0f };
    client->State = EPlayerState::IDLE;
    client->PreviousState = EPlayerState::IDLE;
    client->LastUpdateTime = GetTickCount64() / 1000.0f;
    client->LastPingTime = GetTickCount64() / 1000.0f;
    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    if (CreateIoCompletionPort((HANDLE)client->socket, completionPort, (ULONG_PTR)client, 0) == NULL)
    {
        LOG_ERROR("������ IOCP�� ���� ����: " + std::to_string(GetLastError()));
        closesocket(client->socket);
        delete client;
        return;
    }

    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients[client->id] = client;
    }

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
    LOG_INFO("Ŭ���̾�Ʈ �����: " + std::string(clientIP) + ":" +
        std::to_string(ntohs(clientAddr.sin_port)) + " (ID: " +
        std::to_string(client->id) + ")");

    SendClientId(client);
    BroadcastNewPlayer(client);
    SendExistingPlayers(client);
    StartRecv(client);
}

bool IOCPServer::SendPacket(ClientSession* client, const void* data, size_t size, const char* context)
{
    if (!client || size == 0)
    {
        LOG_ERROR("[SendPacket] �߸��� �Ű�����. ���ؽ�Ʈ: " + std::string(context));
        return false;
    }

    WSABUF wsaBuf;
    wsaBuf.buf = (CHAR*)data;
    wsaBuf.len = (ULONG)size;

    WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
    ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

    DWORD sendBytes = 0;
    int result = WSASend(client->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL);

    if (result == SOCKET_ERROR)
    {
        int error = WSAGetLastError();
        if (error != WSA_IO_PENDING)
        {
            LOG_ERROR("[SendPacket] WSASend ����. ����: " + GetSocketErrorString(error) +
                ", ���ؽ�Ʈ: " + std::string(context) +
                ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));

            delete overlapped;
            return false;
        }
    }

    return true;
}

void IOCPServer::SendClientId(ClientSession* client)
{
    ClientIdPacket packet;
    packet.Header.PacketType = EPacketType::CLIENT_ID;
    packet.Header.PacketSize = sizeof(ClientIdPacket);
    packet.ClientId = client->id;

    SendPacket(client, &packet, sizeof(packet), "SendClientId");

    LOG_INFO("�� Ŭ���̾�Ʈ���� ID " + std::to_string(client->id) + " ���۵�");
}

void IOCPServer::BroadcastNewPlayer(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;

        // �ڽſ��Դ� �������� ����
        if (targetClient->id == newClient->id)
        {
            continue;
        }

        // �� �÷��̾� ���� ��Ŷ ����
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = newClient->id;
        packet.Position = newClient->Position;
        //packet.Rotation = newClient->Rotation;
        packet.Velocity = newClient->Velocity;
        packet.State = newClient->State;

        // �񵿱� ����
        SendPacket(targetClient, &packet, sizeof(packet), "BroadcastNewPlayer");
    }

    LOG_INFO("�� �÷��̾� ����(ID: " + std::to_string(newClient->id) +
        ") ��ε�ĳ��Ʈ - ������ ��: " +
        std::to_string(clients.size() - 1));
}

void IOCPServer::SendExistingPlayers(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    int sentCount = 0;

    for (const auto& pair : clients)
    {
        ClientSession* existingClient = pair.second;

        // �ڽ��� ����
        if (existingClient->id == newClient->id)
        {
            continue;
        }

        // ���� �÷��̾� ���� ��Ŷ ����
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = existingClient->id;
        packet.Position = existingClient->Position;
        //packet.Rotation = existingClient->Rotation;
        packet.Velocity = existingClient->Velocity;
        packet.State = existingClient->State;

        // �񵿱� ����
        SendPacket(newClient, &packet, sizeof(packet), "SendExistingPlayers");
        sentCount++;
    }

    LOG_INFO("���� �÷��̾� ���� " + std::to_string(sentCount) +
        "���� �� Ŭ���̾�Ʈ(ID: " + std::to_string(newClient->id) +
        ")���� ���۵�");
}

bool IOCPServer::StartRecv(ClientSession* client)
{
    DWORD recvBytes = 0;
    DWORD flags = 0;

    client->wsaBuf.buf = client->recvBuffer;
    client->wsaBuf.len = sizeof(client->recvBuffer);
    ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

    int result = WSARecv(client->socket, &client->wsaBuf, 1, &recvBytes, &flags, &client->overlapped, NULL);

    if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
    {
        LOG_ERROR("WSARecv ����: " + GetSocketErrorString(WSAGetLastError()) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        RemoveClient(client->id);
        return false;
    }

    return true;
}

void IOCPServer::RemoveClient(int clientId)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    auto it = clients.find(clientId);
    if (it != clients.end())
    {
        ClientSession* client = it->second;
        closesocket(client->socket);
        LOG_INFO("Ŭ���̾�Ʈ ���� ���� (ID: " + std::to_string(client->id) + ")");

        // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� �˸�
        NotifyClientDisconnect(clientId);

        clients.erase(it);
        delete client;
    }
    else {
        LOG_WARNING("�������� �ʴ� Ŭ���̾�Ʈ ID�� �����Ϸ��� �õ�: " +
            std::to_string(clientId));
    }
}

void IOCPServer::NotifyClientDisconnect(int disconnectedClientId)
{
    PositionUpdatePacket packet;
    packet.Header.PacketType = EPacketType::DISCONNECT;
    packet.Header.PacketSize = sizeof(DisconnectPacket);
    packet.ClientId = disconnectedClientId;

    int notifyCount = 0;
    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;
        // ������ ���� Ŭ���̾�Ʈ�� ����
        if (targetClient->id != disconnectedClientId)
        {
            // �񵿱� ����
            SendPacket(targetClient, &packet, sizeof(packet), "NotifyClientDisconnect");
            notifyCount++;
        }
    }

    LOG_INFO("Ŭ���̾�Ʈ ���� ���� �˸�(ID: " + std::to_string(disconnectedClientId) +
        ") - ������ ��: " + std::to_string(notifyCount));
}

void IOCPServer::ProcessPacket(ClientSession* client, char* data, int length)
{
    if (length < sizeof(PacketHeader))
    {
        LOG_WARNING("�߸��� ��Ŷ ũ��: " + std::to_string(length) +
            " ����Ʈ (�ּ� " + std::to_string(sizeof(PacketHeader)) +
            " ����Ʈ �ʿ�), Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return;
    }

    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    // ��Ŷ Ÿ�� ��ȿ�� �˻�
    if (static_cast<int>(header->PacketType) < 0 ||
        static_cast<int>(header->PacketType) > 6) {
        LOG_WARNING("�߸��� ��Ŷ Ÿ��: " + std::to_string(static_cast<int>(header->PacketType)) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        return;
    }

    switch (header->PacketType)
    {
    case EPacketType::CLIENT_ID:
        break;
    case EPacketType::CONNECT:
        break;
    case EPacketType::DISCONNECT:
        break;
    case EPacketType::PING:
    {
        if (length >= sizeof(PingPacket))
        {
            PingPacket* pingPacket = reinterpret_cast<PingPacket*>(data);
            client->LastPingTime = GetTickCount64() / 1000.0f;  // �����ð����� ����

            PongPacket pongPacket;
            pongPacket.Header.PacketType = EPacketType::PONG;
            pongPacket.Header.PacketSize = sizeof(PongPacket);
            pongPacket.ClientId = pingPacket->ClientId;
            pongPacket.PingTime = pingPacket->PingTime;  // Ŭ�� ���� �ð� �״��

            SendPacket(client, &pongPacket, sizeof(pongPacket), "SendPong");

            LOG_INFO("[����] PingPacket ���� - ClientId: " + std::to_string(client->id));
        }
        else
        {
            LOG_WARNING("[ProcessPacket] �߸��� PING ��Ŷ ũ�� ����");
        }
        break;
    }
    case EPacketType::PONG:
        break;
    case EPacketType::INPUT:
    {
        if (length >= sizeof(InputPacket))
        {
            InputPacket* inputPacket = reinterpret_cast<InputPacket*>(data);
            HandleInputPacket(client, inputPacket);
        }
        else
        {
            LOG_ERROR("[ProcessPacket] INPUT ��Ŷ ũ�� ����ġ. ����: " +
                std::to_string(length) + ", ����: " +
                std::to_string(sizeof(InputPacket)));
        }
        break;
    }
    case EPacketType::POSITION_UPDATE:
        break;
    default:
        LOG_WARNING("ó������ ���� ��Ŷ Ÿ��: " +
            std::to_string(static_cast<int>(header->PacketType)) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
        break;
    }
}

void IOCPServer::HandleInputPacket(ClientSession* client, const InputPacket* packet)
{
    if (!client || !packet)
        return;

    //LOG_DEBUG("�Է� ��Ŷ ���� - Ŭ���̾�Ʈ ID: " + std::to_string(client->id) +
    //    ", Forward: " + std::to_string(packet->ForwardValue) +
    //    ", Right: " + std::to_string(packet->RightValue) +
    //    ", Jump: " + (packet->bJumpPressed ? "true" : "false") +
    //    ", Attack: " + (packet->bAttackPressed ? "true" : "false"));

    // �̵� �Է� ����
    client->InputForward = packet->ForwardValue;
    client->InputRight = packet->RightValue;
    client->bJumpRequested = packet->bJumpPressed;
    client->bAttackRequested = packet->bAttackPressed;

    // �Է� �� ��ȿ�� �˻� (�α�)
    if (std::abs(packet->ForwardValue) > 1.0f || std::abs(packet->RightValue) > 1.0f) {
        LOG_WARNING("���������� �Է� ��: Forward=" + std::to_string(packet->ForwardValue) +
            ", Right=" + std::to_string(packet->RightValue) +
            ", Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
    }
}

void IOCPServer::Update(float DeltaTime)
{
    if (DeltaTime > 0.5f) {
        LOG_WARNING("������������ �� ��Ÿ Ÿ��: " + std::to_string(DeltaTime) + "��");
        // �ʹ� �� ��Ÿ Ÿ���� �����Ͽ� ���� ��� ���� ����
        DeltaTime = 0.5f;
    }

    std::lock_guard<std::mutex> lock(clientsMutex);

    for (auto& pair : clients)
    {
        ClientSession* client = pair.second;

        const float now = GetTickCount64() / 1000.0f;
        if (now - client->LastPingTime > 5.0f) {
            LOG_WARNING("Ŭ���̾�Ʈ Ping Ÿ�Ӿƿ� �߻� - ID: " + std::to_string(client->id));
            RemoveClient(client->id);
            continue; // �̹� ���� Ŭ���̾�Ʈ�� Skip
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
        }

        // ���� ó��
        if (client->bAttackRequested)
        {
            client->State = EPlayerState::ATTACKING;
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
        const float WorldBoundary = 5000.0f;
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

// ����: �� �Լ� ȣ�� ���� �ݵ�� clientsMutex�� Lock�Ǿ�� ��
void IOCPServer::BroadcastPosition(ClientSession* sourceClient)
{
    PositionUpdatePacket packet;
    packet.Header.PacketType = EPacketType::POSITION_UPDATE;
    packet.Header.PacketSize = sizeof(PositionUpdatePacket);
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

DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg)
{
    IOCPServer* server = static_cast<IOCPServer*>(arg);
    server->WorkerThread();
    return 0;
}

void IOCPServer::WorkerThread()
{
    // ������ ID �α� (����� �뵵)
    DWORD threadId = GetCurrentThreadId();
    LOG_INFO("�۾��� ������ ���� (ThreadID: " + std::to_string(threadId) + ")");

    while (isRunning)
    {
        DWORD bytesTransferred = 0;
        ULONG_PTR completionKey = 0;
        OVERLAPPED* overlapped = nullptr;

        BOOL result = GetQueuedCompletionStatus(
            completionPort,
            &bytesTransferred,
            &completionKey,
            &overlapped,
            INFINITE);

        // Ŭ���̾�Ʈ ����
        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // ���� ����
        if (completionKey == 0 && overlapped == nullptr)
        {
            LOG_INFO("�۾��� ������ ���� ��ȣ ���� (ThreadID: " + std::to_string(threadId) + ")");
            break;
        }

        // ���� ó��
        if (!result || bytesTransferred == 0)
        {
            if (client)
            {
                // ���� �ڵ� �α�
                int lastError = WSAGetLastError();
                if (!result && overlapped) {
                    LOG_INFO("Ŭ���̾�Ʈ ���� �ߴ� - ID: " + std::to_string(client->id) +
                        ", ����: " + GetSocketErrorString(lastError));
                }
                else {
                    LOG_INFO("Ŭ���̾�Ʈ�� ���������� ���� ���� - ID: " + std::to_string(client->id));
                }

                RemoveClient(client->id);
            }

            if (overlapped && overlapped != &client->overlapped)
            {
                delete overlapped;
            }

            continue;
        }

        // ������ ���� ó��
        if (overlapped == &client->overlapped)
        {
            // �α� ���� (�ʹ� �ڼ��� �α״� ���ɿ� ������ �� �� �����Ƿ� ����� ��忡�� Ȱ��ȭ)
#ifdef _DEBUG
            LOG_DEBUG("������ ����: " + std::to_string(bytesTransferred) +
                " ����Ʈ, Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
#endif

            // ��Ŷ ó��
            ProcessPacket(client, client->recvBuffer, bytesTransferred);

            // �ٽ� �񵿱� ���� ����
            StartRecv(client);
        }
        // ������ �۽� �Ϸ� ó��
        else
        {
            // �۽� �Ϸ� �� OVERLAPPED �޸� ����
            delete overlapped;
        }
    }

    LOG_INFO("�۾��� ������ ���� (ThreadID: " + std::to_string(threadId) + ")");
}

void IOCPServer::CleanUp()
{
    LOG_INFO("���� �ڿ� ���� ����");
    isRunning = false;

    // �۾��� ������ ���� ��ȣ
    if (completionPort != NULL)
    {
        LOG_INFO("�۾��� �����忡 ���� ��ȣ ����");
        for (int i = 0; i < 16; i++)
        {
            PostQueuedCompletionStatus(completionPort, 0, 0, NULL);
        }
    }

    // Ŭ���̾�Ʈ ���� ����
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        if (!clients.empty()) {
            LOG_INFO("Ŭ���̾�Ʈ ���� ���� �� (" + std::to_string(clients.size()) + "��)");
        }

        for (auto& pair : clients)
        {
            closesocket(pair.second->socket);
            delete pair.second;
        }

        clients.clear();
    }

    // ���� ����
    if (listenSocket != INVALID_SOCKET)
    {
        LOG_INFO("������ ���� ����");
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }

    // IOCP ����
    if (completionPort != NULL)
    {
        LOG_INFO("IOCP �ڵ� ����");
        CloseHandle(completionPort);
        completionPort = NULL;
    }

    LOG_INFO("���� ����");
    WSACleanup();

    LOG_INFO("���� �ڿ� ���� �Ϸ�");
}