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
    int threadCount = sysInfo.dwNumberOfProcessors;
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

    u_long mode = 1;
    if (ioctlsocket(listenSocket, FIONBIO, &mode) != NO_ERROR)
    {
        LOG_ERROR("listenSocket ����ŷ ���� ���� - ����: " + std::to_string(WSAGetLastError()));
        return;
    }
    else
    {
        LOG_INFO("listenSocket ����ŷ ���� ����");
    }

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
            // ���� ��û ������ ó��
            AcceptClient(clientSocket, clientAddr);
        }

        // ��ü Ŭ���̾�Ʈ ������Ʈ
        Update(DeltaTime);

        // ������ �ð� ���� �� ����
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

void IOCPServer::CleanUp()
{
    LOG_INFO("���� �ڿ� ���� ����");
    isRunning = false;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors;

    // �۾��� ������ ���� ��ȣ
    if (completionPort != NULL)
    {
        LOG_INFO("�۾��� �����忡 ���� ��ȣ ����");
        for (int i = 0; i < threadCount; i++)
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