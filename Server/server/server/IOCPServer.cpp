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
    LOG_INFO("서버 인스턴스 생성됨");
}

IOCPServer::~IOCPServer() {
    LOG_INFO("서버 소멸자 호출됨");
    CleanUp();
}

std::string IOCPServer::GetSocketErrorString(int error) const
{
    switch (error) {
    case WSAECONNRESET: return "WSAECONNRESET: 연결이 원격 호스트에 의해 재설정됨";
    case WSAECONNABORTED: return "WSAECONNABORTED: 소프트웨어가 연결 중단 발생";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: 연결 시간 초과";
    case WSAENETDOWN: return "WSAENETDOWN: 네트워크가 다운됨";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: 호스트에 도달할 수 없음";
    case WSAEINTR: return "WSAEINTR: 함수 호출이 중단됨";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: 리소스가 일시적으로 사용 불가";
    default: return "알 수 없는 오류: " + std::to_string(error);
    }
}

int IOCPServer::GetClientCount() const
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    return static_cast<int>(clients.size());
}

bool IOCPServer::Initialize(int port)
{
    LOG_INFO("서버 초기화 시작 (포트: " + std::to_string(port) + ")");

    // 윈속 초기화
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        LOG_ERROR("WSAStartup 실패");
        return false;
    }
    LOG_INFO("윈속 초기화 성공");

    // 소켓 생성
    listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET)
    {
        LOG_ERROR("소켓 생성 실패: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("리스닝 소켓 생성 성공");

    // TCP 소켓 옵션 설정: LINGER 비활성화로 종료 속도 향상
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER 옵션
    if (setsockopt(listenSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        LOG_WARNING("LINGER 옵션 설정 실패: " + std::to_string(WSAGetLastError()));
    }

    // TCP_NODELAY 활성화 (Nagle 알고리즘 비활성화)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        LOG_WARNING("TCP_NODELAY 옵션 설정 실패: " + std::to_string(WSAGetLastError()));
    }

    // 바인딩
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        LOG_ERROR("Bind 실패: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("소켓 바인딩 성공 (포트: " + std::to_string(port) + ")");

    // 리슨
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        LOG_ERROR("Listen 실패: " + std::to_string(WSAGetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("리스닝 시작됨");

    // IOCP 생성
    completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (completionPort == NULL)
    {
        LOG_ERROR("IOCP 생성 실패: " + std::to_string(GetLastError()));
        CleanUp();
        return false;
    }
    LOG_INFO("IOCP 생성 성공");

    // CPU 개수 확인
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors * 2;
    LOG_INFO("CPU 코어 수: " + std::to_string(sysInfo.dwNumberOfProcessors) + ", 생성할 작업자 스레드: " + std::to_string(threadCount));

    // 작업자 스레드 생성
    for (int i = 0; i < threadCount; i++)
    {
        HANDLE thread = CreateThread(NULL, 0, WorkerThreadProc, this, 0, NULL);
        if (thread == NULL)
        {
            LOG_ERROR("작업자 스레드 생성 실패: " + std::to_string(GetLastError()));
            CleanUp();
            return false;
        }
        LOG_INFO("작업자 스레드 #" + std::to_string(i + 1) + " 생성됨");
        CloseHandle(thread);
    }

    LOG_INFO("서버 초기화 완료");
    return true;
}

void IOCPServer::Run()
{
    LOG_INFO("서버 실행 시작");
    uint64_t LastTickTime = GetTickCount64();
    uint64_t framesCount = 0;
    uint64_t lastFpsTime = GetTickCount64();
    float averageFrameTime = 0;

    while (isRunning)
    {
        uint64_t frameStartTime = GetTickCount64();

        uint64_t Now = GetTickCount64();
        float DeltaTime = (Now - LastTickTime) / 1000.0f; // 밀리초 → 초
        LastTickTime = Now;

        // FPS 계산 (1초마다)
        framesCount++;
        if (Now - lastFpsTime > 1000) {
            float fps = static_cast<float>(framesCount) * 1000.0f / (Now - lastFpsTime);
            LOG_INFO("서버 FPS: " + std::to_string(fps) + ", 평균 프레임 시간: " +
                std::to_string(averageFrameTime) + "ms, 클라이언트 수: " +
                std::to_string(GetClientCount()));

            framesCount = 0;
            lastFpsTime = Now;
        }

        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, NULL, 0);

        if (clientSocket != INVALID_SOCKET)
        {
            // 1. 연결 요청 있으면 처리
            AcceptNewClients(clientSocket, clientAddr);
        }

        // 2. 전체 클라이언트 업데이트
        Update(DeltaTime);

        // 3. 프레임 시간 측정 및 조절
        uint64_t frameEndTime = GetTickCount64();
        uint64_t frameTime = frameEndTime - frameStartTime;

        // 지수 이동 평균으로 평균 프레임 시간 계산 (가중치 0.1)
        averageFrameTime = averageFrameTime * 0.9f + frameTime * 0.1f;

        // 목표 프레임 시간 (16.67ms = 약 60 FPS)
        const uint64_t targetFrameTime = 16;

        if (frameTime < targetFrameTime) {
            Sleep(static_cast<DWORD>(targetFrameTime - frameTime));
        }
    }

    LOG_INFO("서버 실행 종료");
}

void IOCPServer::AcceptNewClients(SOCKET clientSocket, SOCKADDR_IN clientAddr)
{
    // TCP 소켓 옵션 설정: LINGER 비활성화로 종료 속도 향상
    LINGER lingerOpt = { 0, 0 }; // SO_DONTLINGER 옵션
    if (setsockopt(clientSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOpt, sizeof(LINGER)) == SOCKET_ERROR) {
        LOG_WARNING("클라이언트 LINGER 옵션 설정 실패: " + std::to_string(WSAGetLastError()));
    }

    // TCP_NODELAY 활성화 (Nagle 알고리즘 비활성화)
    BOOL tcpNoDelay = TRUE;
    if (setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&tcpNoDelay, sizeof(BOOL)) == SOCKET_ERROR) {
        LOG_WARNING("클라이언트 TCP_NODELAY 옵션 설정 실패: " + std::to_string(WSAGetLastError()));
    }

    // 이하 코드 = 클라이언트 세션 생성
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
        LOG_ERROR("소켓을 IOCP에 연결 실패: " + std::to_string(GetLastError()));
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
    LOG_INFO("클라이언트 연결됨: " + std::string(clientIP) + ":" +
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
        LOG_ERROR("[SendPacket] 잘못된 매개변수. 컨텍스트: " + std::string(context));
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
            LOG_ERROR("[SendPacket] WSASend 실패. 오류: " + GetSocketErrorString(error) +
                ", 컨텍스트: " + std::string(context) +
                ", 클라이언트 ID: " + std::to_string(client->id));

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

    LOG_INFO("새 클라이언트에게 ID " + std::to_string(client->id) + " 전송됨");
}

void IOCPServer::BroadcastNewPlayer(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    for (const auto& pair : clients)
    {
        ClientSession* targetClient = pair.second;

        // 자신에게는 전송하지 않음
        if (targetClient->id == newClient->id)
        {
            continue;
        }

        // 새 플레이어 정보 패킷 생성
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = newClient->id;
        packet.Position = newClient->Position;
        //packet.Rotation = newClient->Rotation;
        packet.Velocity = newClient->Velocity;
        packet.State = newClient->State;

        // 비동기 전송
        SendPacket(targetClient, &packet, sizeof(packet), "BroadcastNewPlayer");
    }

    LOG_INFO("새 플레이어 정보(ID: " + std::to_string(newClient->id) +
        ") 브로드캐스트 - 수신자 수: " +
        std::to_string(clients.size() - 1));
}

void IOCPServer::SendExistingPlayers(ClientSession* newClient)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    int sentCount = 0;

    for (const auto& pair : clients)
    {
        ClientSession* existingClient = pair.second;

        // 자신은 제외
        if (existingClient->id == newClient->id)
        {
            continue;
        }

        // 기존 플레이어 정보 패킷 생성
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = existingClient->id;
        packet.Position = existingClient->Position;
        //packet.Rotation = existingClient->Rotation;
        packet.Velocity = existingClient->Velocity;
        packet.State = existingClient->State;

        // 비동기 전송
        SendPacket(newClient, &packet, sizeof(packet), "SendExistingPlayers");
        sentCount++;
    }

    LOG_INFO("기존 플레이어 정보 " + std::to_string(sentCount) +
        "개가 새 클라이언트(ID: " + std::to_string(newClient->id) +
        ")에게 전송됨");
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
        LOG_ERROR("WSARecv 실패: " + GetSocketErrorString(WSAGetLastError()) +
            ", 클라이언트 ID: " + std::to_string(client->id));
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
        LOG_INFO("클라이언트 연결 끊김 (ID: " + std::to_string(client->id) + ")");

        // 다른 클라이언트들에게 연결 끊김 알림
        NotifyClientDisconnect(clientId);

        clients.erase(it);
        delete client;
    }
    else {
        LOG_WARNING("존재하지 않는 클라이언트 ID를 제거하려고 시도: " +
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
        // 연결이 끊긴 클라이언트는 제외
        if (targetClient->id != disconnectedClientId)
        {
            // 비동기 전송
            SendPacket(targetClient, &packet, sizeof(packet), "NotifyClientDisconnect");
            notifyCount++;
        }
    }

    LOG_INFO("클라이언트 연결 끊김 알림(ID: " + std::to_string(disconnectedClientId) +
        ") - 수신자 수: " + std::to_string(notifyCount));
}

void IOCPServer::ProcessPacket(ClientSession* client, char* data, int length)
{
    if (length < sizeof(PacketHeader))
    {
        LOG_WARNING("잘못된 패킷 크기: " + std::to_string(length) +
            " 바이트 (최소 " + std::to_string(sizeof(PacketHeader)) +
            " 바이트 필요), 클라이언트 ID: " + std::to_string(client->id));
        return;
    }

    PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

    // 패킷 타입 유효성 검사
    if (static_cast<int>(header->PacketType) < 0 ||
        static_cast<int>(header->PacketType) > 6) {
        LOG_WARNING("잘못된 패킷 타입: " + std::to_string(static_cast<int>(header->PacketType)) +
            ", 클라이언트 ID: " + std::to_string(client->id));
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
            client->LastPingTime = GetTickCount64() / 1000.0f;  // 서버시간으로 갱신

            PongPacket pongPacket;
            pongPacket.Header.PacketType = EPacketType::PONG;
            pongPacket.Header.PacketSize = sizeof(PongPacket);
            pongPacket.ClientId = pingPacket->ClientId;
            pongPacket.PingTime = pingPacket->PingTime;  // 클라가 보낸 시간 그대로

            SendPacket(client, &pongPacket, sizeof(pongPacket), "SendPong");

            LOG_INFO("[서버] PingPacket 수신 - ClientId: " + std::to_string(client->id));
        }
        else
        {
            LOG_WARNING("[ProcessPacket] 잘못된 PING 패킷 크기 수신");
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
            LOG_ERROR("[ProcessPacket] INPUT 패킷 크기 불일치. 수신: " +
                std::to_string(length) + ", 예상: " +
                std::to_string(sizeof(InputPacket)));
        }
        break;
    }
    case EPacketType::POSITION_UPDATE:
        break;
    default:
        LOG_WARNING("처리되지 않은 패킷 타입: " +
            std::to_string(static_cast<int>(header->PacketType)) +
            ", 클라이언트 ID: " + std::to_string(client->id));
        break;
    }
}

void IOCPServer::HandleInputPacket(ClientSession* client, const InputPacket* packet)
{
    if (!client || !packet)
        return;

    //LOG_DEBUG("입력 패킷 수신 - 클라이언트 ID: " + std::to_string(client->id) +
    //    ", Forward: " + std::to_string(packet->ForwardValue) +
    //    ", Right: " + std::to_string(packet->RightValue) +
    //    ", Jump: " + (packet->bJumpPressed ? "true" : "false") +
    //    ", Attack: " + (packet->bAttackPressed ? "true" : "false"));

    // 이동 입력 저장
    client->InputForward = packet->ForwardValue;
    client->InputRight = packet->RightValue;
    client->bJumpRequested = packet->bJumpPressed;
    client->bAttackRequested = packet->bAttackPressed;

    // 입력 값 유효성 검사 (로깅)
    if (std::abs(packet->ForwardValue) > 1.0f || std::abs(packet->RightValue) > 1.0f) {
        LOG_WARNING("비정상적인 입력 값: Forward=" + std::to_string(packet->ForwardValue) +
            ", Right=" + std::to_string(packet->RightValue) +
            ", 클라이언트 ID: " + std::to_string(client->id));
    }
}

void IOCPServer::Update(float DeltaTime)
{
    if (DeltaTime > 0.5f) {
        LOG_WARNING("비정상적으로 긴 델타 타임: " + std::to_string(DeltaTime) + "초");
        // 너무 긴 델타 타임을 제한하여 물리 계산 오차 방지
        DeltaTime = 0.5f;
    }

    std::lock_guard<std::mutex> lock(clientsMutex);

    for (auto& pair : clients)
    {
        ClientSession* client = pair.second;

        const float now = GetTickCount64() / 1000.0f;
        if (now - client->LastPingTime > 5.0f) {
            LOG_WARNING("클라이언트 Ping 타임아웃 발생 - ID: " + std::to_string(client->id));
            RemoveClient(client->id);
            continue; // 이미 지운 클라이언트는 Skip
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
        }

        // 공격 처리
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

        // 이전 위치 저장
        client->LastPosition = client->Position;

        // 위치 이동
        client->Position.X += client->Velocity.X * DeltaTime;
        client->Position.Y += client->Velocity.Y * DeltaTime;
        client->Position.Z += client->Velocity.Z * DeltaTime;

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
        const float WorldBoundary = 5000.0f;
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

// 주의: 이 함수 호출 전에 반드시 clientsMutex가 Lock되어야 함
void IOCPServer::BroadcastPosition(ClientSession* sourceClient)
{
    PositionUpdatePacket packet;
    packet.Header.PacketType = EPacketType::POSITION_UPDATE;
    packet.Header.PacketSize = sizeof(PositionUpdatePacket);
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

DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg)
{
    IOCPServer* server = static_cast<IOCPServer*>(arg);
    server->WorkerThread();
    return 0;
}

void IOCPServer::WorkerThread()
{
    // 스레드 ID 로깅 (디버깅 용도)
    DWORD threadId = GetCurrentThreadId();
    LOG_INFO("작업자 스레드 시작 (ThreadID: " + std::to_string(threadId) + ")");

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

        // 클라이언트 세션
        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // 서버 종료
        if (completionKey == 0 && overlapped == nullptr)
        {
            LOG_INFO("작업자 스레드 종료 신호 받음 (ThreadID: " + std::to_string(threadId) + ")");
            break;
        }

        // 에러 처리
        if (!result || bytesTransferred == 0)
        {
            if (client)
            {
                // 에러 코드 로깅
                int lastError = WSAGetLastError();
                if (!result && overlapped) {
                    LOG_INFO("클라이언트 연결 중단 - ID: " + std::to_string(client->id) +
                        ", 오류: " + GetSocketErrorString(lastError));
                }
                else {
                    LOG_INFO("클라이언트가 정상적으로 연결 종료 - ID: " + std::to_string(client->id));
                }

                RemoveClient(client->id);
            }

            if (overlapped && overlapped != &client->overlapped)
            {
                delete overlapped;
            }

            continue;
        }

        // 데이터 수신 처리
        if (overlapped == &client->overlapped)
        {
            // 로그 정보 (너무 자세한 로그는 성능에 영향을 줄 수 있으므로 디버그 모드에만 활성화)
#ifdef _DEBUG
            LOG_DEBUG("데이터 수신: " + std::to_string(bytesTransferred) +
                " 바이트, 클라이언트 ID: " + std::to_string(client->id));
#endif

            // 패킷 처리
            ProcessPacket(client, client->recvBuffer, bytesTransferred);

            // 다시 비동기 수신 시작
            StartRecv(client);
        }
        // 데이터 송신 완료 처리
        else
        {
            // 송신 완료 후 OVERLAPPED 메모리 해제
            delete overlapped;
        }
    }

    LOG_INFO("작업자 스레드 종료 (ThreadID: " + std::to_string(threadId) + ")");
}

void IOCPServer::CleanUp()
{
    LOG_INFO("서버 자원 정리 시작");
    isRunning = false;

    // 작업자 스레드 종료 신호
    if (completionPort != NULL)
    {
        LOG_INFO("작업자 스레드에 종료 신호 전송");
        for (int i = 0; i < 16; i++)
        {
            PostQueuedCompletionStatus(completionPort, 0, 0, NULL);
        }
    }

    // 클라이언트 연결 정리
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        if (!clients.empty()) {
            LOG_INFO("클라이언트 연결 정리 중 (" + std::to_string(clients.size()) + "개)");
        }

        for (auto& pair : clients)
        {
            closesocket(pair.second->socket);
            delete pair.second;
        }

        clients.clear();
    }

    // 소켓 정리
    if (listenSocket != INVALID_SOCKET)
    {
        LOG_INFO("리스닝 소켓 정리");
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }

    // IOCP 정리
    if (completionPort != NULL)
    {
        LOG_INFO("IOCP 핸들 정리");
        CloseHandle(completionPort);
        completionPort = NULL;
    }

    LOG_INFO("윈속 정리");
    WSACleanup();

    LOG_INFO("서버 자원 정리 완료");
}