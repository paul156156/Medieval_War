// IOCPServer.cpp (�����丵�� ����)
#include "IOCPServer.h"
#include "Logger.h"
#include "NetworkManager.h"
#include "GameUpdater.h"
#include "ClientManager.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"
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

DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg) {
    IOCPServer* server = reinterpret_cast<IOCPServer*>(arg);
    server->WorkerThread();
    return 0;
}

void IOCPServer::Update(float DeltaTime) {
    GameUpdater gameUpdater;
    gameUpdater.UpdateClients(DeltaTime, clients, clientsMutex);
}

void IOCPServer::AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr) {
    ClientManager clientManager;
    ClientSession* newClient = clientManager.CreateSession(clientSocket, clientAddr);

    if (newClient) {
        NetworkSessionManager::SetSocketOptions(clientSocket);

        if (!NetworkSessionManager::RegisterToIOCP(networkManager.GetCompletionPort(), newClient)) {
            LOG_ERROR("IOCP ��� ����: Ŭ���̾�Ʈ ID " + std::to_string(newClient->id));
            closesocket(clientSocket);
            delete newClient;
            return;
        }

        if (!NetworkSessionManager::PostRecv(newClient)) {
            LOG_ERROR("�ʱ� ���� ��û ����: Ŭ���̾�Ʈ ID " + std::to_string(newClient->id));
            closesocket(clientSocket);
            delete newClient;
            return;
        }

        PacketDispatcher::SendClientId(newClient);
        PacketDispatcher::SendInitialPosition(newClient);

        {
            std::lock_guard<std::mutex> lock(clientsMutex);

            if (!clients.empty()) {
                PacketDispatcher::SendExistingPlayer(newClient, clients);
                PacketDispatcher::BroadcastNewPlayer(newClient, clients);
            }

            clients[newClient->id] = newClient;
        }

        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), ipStr, INET_ADDRSTRLEN);

        LOG_INFO("�� Ŭ���̾�Ʈ �����: ID " + std::to_string(newClient->id) +
            ", IP: " + std::string(ipStr) +
            ", Port: " + std::to_string(ntohs(clientAddr.sin_port)));
    }
}

void IOCPServer::WorkerThread() {
    DWORD bytesTransferred = 0;
    ULONG_PTR completionKey = 0;
    OVERLAPPED* overlapped = nullptr;

    while (isRunning) {
        BOOL result = GetQueuedCompletionStatus(
            networkManager.GetCompletionPort(),
            &bytesTransferred,
            &completionKey,
            &overlapped,
            INFINITE);

        // ���� ���� ��ȣ Ȯ��
        if (completionKey == 0 && overlapped == nullptr) {
            LOG_INFO("IOCP �۾��� ������ ���� ��û ����");
            break;
        }

        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // Ŭ���̾�Ʈ ���� ���� �Ǵ� ���� Ȯ��
        if (!result || bytesTransferred == 0) {
            if (client) {
                LOG_WARNING("Ŭ���̾�Ʈ ���� ���� �Ǵ� ���� - ID: " + std::to_string(client->id));
                int clientId = client->id;
                closesocket(client->socket);

                std::lock_guard<std::mutex> lock(clientsMutex);
                auto it = clients.find(clientId);
                if (it != clients.end()) {
                    ClientSession* client = it->second;  // ������ ���� ����
                    clients.erase(it);  // �ݺ��� ����

                    // ���� �����ϰ� �޸� ����
                    if (client) {
                        delete client;
                    }

                    // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� �˸�
                    DisconnectPacket packet;
                    packet.Header.PacketType = EPacketType::DISCONNECT;
                    packet.Header.PacketSize = sizeof(DisconnectPacket);
                    packet.ClientId = clientId;

                    for (const auto& pair : clients) {
                        NetworkSessionManager::SendPacket(
                            pair.second, &packet, sizeof(packet), "NotifyClientDisconnect");
                    }
                }
            }

            if (overlapped && client && overlapped != &client->overlapped) {
                delete overlapped;
            }

            continue;
        }

        // ���� �Ϸ� ó��
        if (client && overlapped == &client->overlapped) {
            // �� ���� ó��
            float currentTime = GetTickCount64() / 1000.0f;
            client->LastPingTime = currentTime;

            // ���ŵ� ������ ó��
            if (bytesTransferred >= sizeof(PacketHeader)) {
                PacketHeader* header = reinterpret_cast<PacketHeader*>(client->recvBuffer);

                // ��Ŷ Ÿ�Կ� ���� ó��
                switch (header->PacketType) {
                case EPacketType::CONNECT:
					if (bytesTransferred >= sizeof(ConnectPacket)) {
						ConnectPacket* connectPacket = reinterpret_cast<ConnectPacket*>(client->recvBuffer);
						client->id = connectPacket->ClientId;
						PacketDispatcher::SendClientId(client);
					}
					break;
				case EPacketType::DISCONNECT:
					if (bytesTransferred >= sizeof(DisconnectPacket)) {
						DisconnectPacket* disconnectPacket = reinterpret_cast<DisconnectPacket*>(client->recvBuffer);
						int clientId = disconnectPacket->ClientId;
						closesocket(client->socket);
						client->socket = INVALID_SOCKET;
						std::lock_guard<std::mutex> lock(clientsMutex);
						clients.erase(clientId);
					}
					break;
				case EPacketType::PLAYER_INIT_INFO:
					if (bytesTransferred >= sizeof(ConnectPacket)) {
						ConnectPacket* connectPacket = reinterpret_cast<ConnectPacket*>(client->recvBuffer);
						client->id = connectPacket->ClientId;
						PacketDispatcher::SendClientId(client);
					}
					break;
				case EPacketType::PLAYER_POSITION_INFO:
					if (bytesTransferred >= sizeof(PositionPacket)) {
						PositionPacket* positionPacket = reinterpret_cast<PositionPacket*>(client->recvBuffer);
						client->Position = positionPacket->Position;
						client->Velocity = positionPacket->Velocity;
						client->Rotation = positionPacket->Rotation;
						client->State = positionPacket->State;
					}
					break;
                case EPacketType::PING:
                    PacketDispatcher::SendPong(client);
                    break;

                case EPacketType::PLAYER_INPUT_INFO:
                    if (bytesTransferred >= sizeof(InputPacket)) {
                        InputPacket* inputPacket = reinterpret_cast<InputPacket*>(client->recvBuffer);
                        client->InputForward = inputPacket->ForwardValue;
                        client->InputRight = inputPacket->RightValue;
                        client->ControlRotationYaw = inputPacket->ControlRotationYaw;
                        client->bJumpRequested = inputPacket->bJumpPressed;
                        client->bAttackRequested = inputPacket->bAttackPressed;
                    }
                    break;

                    // �ٸ� ��Ŷ Ÿ�Կ� ���� ó�� �߰�
                }
            }

            // ���� ���� ��û
            NetworkSessionManager::PostRecv(client);
        }
        // �۽� �Ϸ� ó��
        else if (overlapped) {
            delete overlapped;
        }
    }

    LOG_INFO("IOCP �۾��� ������ ����");
}