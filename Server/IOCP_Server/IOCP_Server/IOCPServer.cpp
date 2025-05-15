// IOCPServer.cpp (리팩토링된 버전)
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
    LOG_INFO("IOCPServer 인스턴스 생성됨");
}

IOCPServer::~IOCPServer() {
    LOG_INFO("IOCPServer 소멸자 호출됨");
    CleanUp();
}

bool IOCPServer::Initialize(int port) {
    LOG_INFO("서버 초기화 시작 (포트: " + std::to_string(port) + ")");

    if (!networkManager.InitializeSocket(port)) {
        LOG_ERROR("소켓 초기화 실패");
        return false;
    }

    if (!networkManager.SetupIOCP()) {
        LOG_ERROR("IOCP 생성 실패");
        return false;
    }

    // 스레드 개수 = CPU 수
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int threadCount = sysInfo.dwNumberOfProcessors;

    for (int i = 0; i < threadCount; ++i) {
        HANDLE hThread = CreateThread(nullptr, 0, WorkerThreadProc, this, 0, nullptr);
        if (hThread == NULL) {
            LOG_ERROR("작업자 스레드 생성 실패: " + std::to_string(GetLastError()));
            return false;
        }
        CloseHandle(hThread);
        LOG_INFO("작업자 스레드 생성됨: " + std::to_string(i + 1));
    }

    LOG_INFO("서버 초기화 완료");
    return true;
}

void IOCPServer::Run() {
    LOG_INFO("서버 실행 시작");

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

    LOG_INFO("서버 루프 종료됨");
}

void IOCPServer::CleanUp() {
    LOG_INFO("서버 자원 정리 시작");
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
    LOG_INFO("서버 자원 정리 완료");
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
            LOG_ERROR("IOCP 등록 실패: 클라이언트 ID " + std::to_string(newClient->id));
            closesocket(clientSocket);
            delete newClient;
            return;
        }

        if (!NetworkSessionManager::PostRecv(newClient)) {
            LOG_ERROR("초기 수신 요청 실패: 클라이언트 ID " + std::to_string(newClient->id));
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

        LOG_INFO("새 클라이언트 연결됨: ID " + std::to_string(newClient->id) +
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

        // 서버 종료 신호 확인
        if (completionKey == 0 && overlapped == nullptr) {
            LOG_INFO("IOCP 작업자 스레드 종료 요청 수신");
            break;
        }

        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // 클라이언트 연결 종료 또는 오류 확인
        if (!result || bytesTransferred == 0) {
            if (client) {
                LOG_WARNING("클라이언트 소켓 오류 또는 종료 - ID: " + std::to_string(client->id));
                int clientId = client->id;
                closesocket(client->socket);

                std::lock_guard<std::mutex> lock(clientsMutex);
                auto it = clients.find(clientId);
                if (it != clients.end()) {
                    ClientSession* client = it->second;  // 포인터 먼저 저장
                    clients.erase(it);  // 반복자 제거

                    // 이제 안전하게 메모리 해제
                    if (client) {
                        delete client;
                    }

                    // 다른 클라이언트들에게 연결 종료 알림
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

        // 수신 완료 처리
        if (client && overlapped == &client->overlapped) {
            // 핑 응답 처리
            float currentTime = GetTickCount64() / 1000.0f;
            client->LastPingTime = currentTime;

            // 수신된 데이터 처리
            if (bytesTransferred >= sizeof(PacketHeader)) {
                PacketHeader* header = reinterpret_cast<PacketHeader*>(client->recvBuffer);

                // 패킷 타입에 따라 처리
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

                    // 다른 패킷 타입에 대한 처리 추가
                }
            }

            // 다음 수신 요청
            NetworkSessionManager::PostRecv(client);
        }
        // 송신 완료 처리
        else if (overlapped) {
            delete overlapped;
        }
    }

    LOG_INFO("IOCP 작업자 스레드 종료");
}