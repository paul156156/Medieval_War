// IOCPServer.cpp (�����丵�� ����)
#include "IOCPServer.h"
#include "Logger.h"
#include "NetworkManager.h"
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>


IOCPServer::IOCPServer() : isRunning(true), nextClientId(1) {
    Logger::GetInstance().Initialize();
    LOG_INFO("IOCPServer �ν��Ͻ� ������");
}

IOCPServer::~IOCPServer() {
    LOG_INFO("IOCPServer �Ҹ��� ȣ���");
    CleanUp();
}

bool IOCPServer::Initialize(int port) {
    LOG_INFO("���� �ʱ�ȭ ���� (��Ʈ: " + std::to_string(port) + ")");

    if (!networkManager.InitializeSocket(port)) {
        LOG_ERROR("���� �ʱ�ȭ ����");
        return false;
    }

    if (!networkManager.SetupIOCP()) {
        LOG_ERROR("IOCP ���� ����");
        return false;
    }

    // ������ ���� = CPU ��
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors;

    for (int i = 0; i < threadCount; ++i) {
        HANDLE hThread = CreateThread(nullptr, 0, WorkerThreadProc, this, 0, nullptr);
        if (hThread == NULL) {
            LOG_ERROR("�۾��� ������ ���� ����: " + std::to_string(GetLastError()));
            return false;
        }
        CloseHandle(hThread);
        LOG_INFO("�۾��� ������ ������: " + std::to_string(i + 1));
    }

    LOG_INFO("���� �ʱ�ȭ �Ϸ�");
    return true;
}

void IOCPServer::Run() {
    LOG_INFO("���� ���� ����");

    SOCKET listenSocket = networkManager.GetListenSocket();
    uint64_t lastTick = GetTickCount64();
    float averageFrameTime = 0;

    while (isRunning) {
        uint64_t frameStart = GetTickCount64();

        SOCKADDR_IN clientAddr;
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, nullptr, 0);

        if (clientSocket != INVALID_SOCKET) {
            AcceptClient(clientSocket, clientAddr);
        }

        float deltaTime = (GetTickCount64() - lastTick) / 1000.0f;
        lastTick = GetTickCount64();

        Update(deltaTime);

        uint64_t frameEnd = GetTickCount64();
        uint64_t frameTime = frameEnd - frameStart;
        averageFrameTime = averageFrameTime * 0.9f + frameTime * 0.1f;

        const uint64_t targetFrameTime = 16;
        if (frameTime < targetFrameTime) {
            Sleep(static_cast<DWORD>(targetFrameTime - frameTime));
        }
    }

    LOG_INFO("���� ���� �����");
}

void IOCPServer::CleanUp() {
    LOG_INFO("���� �ڿ� ���� ����");
    isRunning = false;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors;

    HANDLE iocp = networkManager.GetCompletionPort();
    for (int i = 0; i < threadCount; ++i) {
        PostQueuedCompletionStatus(iocp, 0, 0, nullptr);
    }

    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (auto& pair : clients) {
            closesocket(pair.second->socket);
            delete pair.second;
        }
        clients.clear();
    }

    networkManager.Shutdown();
    LOG_INFO("���� �ڿ� ���� �Ϸ�");
}