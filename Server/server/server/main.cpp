#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <mutex>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

// 패킷 타입 정의
enum class EPacketType : uint8_t
{
    MOVE = 0,
    JUMP = 1,
    POSITION_UPDATE = 2,
    CLIENT_ID = 3  // 클라이언트 ID 할당을 위한 패킷 타입 추가
};

// 패킷 구조체 정의
#pragma pack(push, 1)
struct PacketHeader
{
    uint16_t PacketSize;
    EPacketType PacketType;
};

struct MovePacket
{
    PacketHeader Header;
    float ForwardValue;
    float RightValue;
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
    struct { float X, Y, Z; } Velocity;  // 속도 정보 추가
};

struct JumpPacket
{
    PacketHeader Header;
    bool IsJumping;
    struct { float X, Y, Z; } Position;
    struct { float X, Y, Z; } Velocity;  // 속도 정보 추가
};

struct PositionUpdatePacket
{
    PacketHeader Header;
    int32_t ClientId;  // 클라이언트 ID 추가
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
    struct { float X, Y, Z; } Velocity;  // 속도 정보 추가
    bool IsJumping;
};

struct ClientIdPacket
{
    PacketHeader Header;
    int32_t ClientId;
};
#pragma pack(pop)

// IOCP를 위한 구조체
struct ClientSession
{
    SOCKET socket;
    SOCKADDR_IN addr;
    char recvBuffer[1024];
    WSAOVERLAPPED overlapped;
    WSABUF wsaBuf;
    int id;

    // 플레이어 상태
    struct
    {
        float X, Y, Z;
    } Position;

    struct
    {
        float Pitch, Yaw, Roll;
    } Rotation;

    struct
    {
        float X, Y, Z;
    } Velocity;  // 속도 정보 추가

    bool IsJumping;

    // 마지막 위치 저장 (속도 계산용)
    struct
    {
        float X, Y, Z;
    } LastPosition;

    // 마지막 업데이트 시간
    float LastUpdateTime;
};

class IOCPServer
{
public:
    IOCPServer() : listenSocket(INVALID_SOCKET), completionPort(NULL), nextClientId(1), isRunning(true)
    {
    }

    ~IOCPServer()
    {
        CleanUp();
    }

    bool Initialize(int port)
    {
        // 윈속 초기화
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            std::cerr << "WSAStartup failed" << std::endl;
            return false;
        }

        // 소켓 생성
        listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
        if (listenSocket == INVALID_SOCKET)
        {
            std::cerr << "Socket creation failed" << std::endl;
            CleanUp();
            return false;
        }

        // 바인딩
        SOCKADDR_IN serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        {
            std::cerr << "Bind failed" << std::endl;
            CleanUp();
            return false;
        }

        // 리슨
        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            std::cerr << "Listen failed" << std::endl;
            CleanUp();
            return false;
        }

        // IOCP 생성
        completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        if (completionPort == NULL)
        {
            std::cerr << "CreateIoCompletionPort failed" << std::endl;
            CleanUp();
            return false;
        }

        // CPU 개수 확인
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        int threadCount = sysInfo.dwNumberOfProcessors * 2;

        // 작업자 스레드 생성
        for (int i = 0; i < threadCount; i++)
        {
            HANDLE thread = CreateThread(NULL, 0, WorkerThreadProc, this, 0, NULL);
            if (thread == NULL)
            {
                std::cerr << "Worker thread creation failed" << std::endl;
                CleanUp();
                return false;
            }
            CloseHandle(thread);
        }

        return true;
    }

    void Run()
    {
        while (isRunning)
        {
            // 클라이언트 연결 수락
            SOCKADDR_IN clientAddr;
            int addrLen = sizeof(clientAddr);
            SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, NULL, 0);

            if (clientSocket == INVALID_SOCKET)
            {
                std::cerr << "Accept failed" << std::endl;
                continue;
            }

            // 클라이언트 세션 생성
            ClientSession* client = new ClientSession();
            client->socket = clientSocket;
            client->addr = clientAddr;
            client->id = nextClientId++;
            client->wsaBuf.buf = client->recvBuffer;
            client->wsaBuf.len = sizeof(client->recvBuffer);
            client->Position = { 0.0f, 0.0f, 0.0f };
            client->LastPosition = { 0.0f, 0.0f, 0.0f };
            client->Rotation = { 0.0f, 0.0f, 0.0f };
            client->Velocity = { 0.0f, 0.0f, 0.0f };
            client->IsJumping = false;
            client->LastUpdateTime = GetTickCount() / 1000.0f;
            ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

            // IOCP에 소켓 등록
            if (CreateIoCompletionPort((HANDLE)client->socket, completionPort, (ULONG_PTR)client, 0) == NULL)
            {
                std::cerr << "Failed to associate socket with IOCP" << std::endl;
                closesocket(client->socket);
                delete client;
                continue;
            }

            // 클라이언트 맵에 추가
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients[client->id] = client;
            }

            // 클라이언트 접속 정보 출력
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
            std::cout << "Client connected: " << clientIP << ":" << ntohs(clientAddr.sin_port) << " (ID: " << client->id << ")" << std::endl;

            // 클라이언트에게 ID 할당 패킷 전송
            SendClientId(client);

            // 새 플레이어 접속 정보를 다른 모든 클라이언트에게 전송
            BroadcastNewPlayer(client);

            // 이미 접속한 다른 플레이어 정보를 새 클라이언트에게 전송
            SendExistingPlayers(client);

            // 비동기 수신 시작
            StartRecv(client);
        }
    }

private:
    // 클라이언트에게 ID 할당 패킷 전송
    void SendClientId(ClientSession* client)
    {
        ClientIdPacket packet;
        packet.Header.PacketType = EPacketType::CLIENT_ID;
        packet.Header.PacketSize = sizeof(ClientIdPacket);
        packet.ClientId = client->id;

        WSABUF wsaBuf;
        wsaBuf.buf = reinterpret_cast<char*>(&packet);
        wsaBuf.len = sizeof(packet);

        WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
        ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

        DWORD sendBytes = 0;

        if (WSASend(client->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL) == SOCKET_ERROR)
        {
            if (WSAGetLastError() != WSA_IO_PENDING)
            {
                std::cerr << "Failed to send client ID packet: " << WSAGetLastError() << std::endl;
                delete overlapped;
            }
        }

        std::cout << "Sent client ID " << client->id << " to new client" << std::endl;
    }

    // 새 플레이어 정보를 다른 모든 클라이언트에게 전송
    void BroadcastNewPlayer(ClientSession* newClient)
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
            packet.Position.X = newClient->Position.X;
            packet.Position.Y = newClient->Position.Y;
            packet.Position.Z = newClient->Position.Z;
            packet.Rotation.Pitch = newClient->Rotation.Pitch;
            packet.Rotation.Yaw = newClient->Rotation.Yaw;
            packet.Rotation.Roll = newClient->Rotation.Roll;
            packet.Velocity.X = newClient->Velocity.X;
            packet.Velocity.Y = newClient->Velocity.Y;
            packet.Velocity.Z = newClient->Velocity.Z;
            packet.IsJumping = newClient->IsJumping;

            // 비동기 전송
            WSABUF wsaBuf;
            wsaBuf.buf = reinterpret_cast<char*>(&packet);
            wsaBuf.len = sizeof(packet);

            WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
            ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

            DWORD sendBytes = 0;

            if (WSASend(targetClient->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL) == SOCKET_ERROR)
            {
                if (WSAGetLastError() != WSA_IO_PENDING)
                {
                    std::cerr << "Failed to broadcast new player: " << WSAGetLastError() << std::endl;
                    delete overlapped;
                }
            }
        }
    }

    // 이미 접속한 다른 플레이어 정보를 새 클라이언트에게 전송
    void SendExistingPlayers(ClientSession* newClient)
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

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
            packet.Position.X = existingClient->Position.X;
            packet.Position.Y = existingClient->Position.Y;
            packet.Position.Z = existingClient->Position.Z;
            packet.Rotation.Pitch = existingClient->Rotation.Pitch;
            packet.Rotation.Yaw = existingClient->Rotation.Yaw;
            packet.Rotation.Roll = existingClient->Rotation.Roll;
            packet.Velocity.X = existingClient->Velocity.X;
            packet.Velocity.Y = existingClient->Velocity.Y;
            packet.Velocity.Z = existingClient->Velocity.Z;
            packet.IsJumping = existingClient->IsJumping;

            // 비동기 전송
            WSABUF wsaBuf;
            wsaBuf.buf = reinterpret_cast<char*>(&packet);
            wsaBuf.len = sizeof(packet);

            WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
            ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

            DWORD sendBytes = 0;

            if (WSASend(newClient->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL) == SOCKET_ERROR)
            {
                if (WSAGetLastError() != WSA_IO_PENDING)
                {
                    std::cerr << "Failed to send existing player: " << WSAGetLastError() << std::endl;
                    delete overlapped;
                }
            }
        }
    }

    // 비동기 수신 시작
    bool StartRecv(ClientSession* client)
    {
        DWORD recvBytes = 0;
        DWORD flags = 0;

        client->wsaBuf.buf = client->recvBuffer;
        client->wsaBuf.len = sizeof(client->recvBuffer);
        ZeroMemory(&client->overlapped, sizeof(WSAOVERLAPPED));

        int result = WSARecv(client->socket, &client->wsaBuf, 1, &recvBytes, &flags, &client->overlapped, NULL);

        if (result == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
        {
            std::cerr << "WSARecv failed: " << WSAGetLastError() << std::endl;
            RemoveClient(client->id);
            return false;
        }

        return true;
    }

    // 클라이언트 제거
    void RemoveClient(int clientId)
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        auto it = clients.find(clientId);
        if (it != clients.end())
        {
            ClientSession* client = it->second;
            closesocket(client->socket);
            std::cout << "Client disconnected (ID: " << client->id << ")" << std::endl;

            // 다른 클라이언트들에게 연결 끊김 알림
            NotifyClientDisconnect(clientId);

            clients.erase(it);
            delete client;
        }
    }

    // 클라이언트 연결 끊김을 다른 클라이언트들에게 알림
    void NotifyClientDisconnect(int disconnectedClientId)
    {
        // 여기서는 PositionUpdatePacket을 사용하여 위치를 무효한 값(-999999)으로 설정
        // 실제로는 별도의 디스커넥트 패킷 타입을 만드는 것이 더 좋음
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = disconnectedClientId;
        packet.Position.X = -999999.0f;  // 무효한 위치로 설정 - 클라이언트에서 이 값을 보고 제거
        packet.Position.Y = -999999.0f;
        packet.Position.Z = -999999.0f;
        packet.Rotation.Pitch = 0.0f;
        packet.Rotation.Yaw = 0.0f;
        packet.Rotation.Roll = 0.0f;
        packet.Velocity.X = 0.0f;
        packet.Velocity.Y = 0.0f;
        packet.Velocity.Z = 0.0f;
        packet.IsJumping = false;

        for (const auto& pair : clients)
        {
            ClientSession* targetClient = pair.second;

            // 연결이 끊긴 클라이언트는 제외
            if (targetClient->id == disconnectedClientId)
            {
                continue;
            }

            // 비동기 전송
            WSABUF wsaBuf;
            wsaBuf.buf = reinterpret_cast<char*>(&packet);
            wsaBuf.len = sizeof(packet);

            WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
            ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

            DWORD sendBytes = 0;

            if (WSASend(targetClient->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL) == SOCKET_ERROR)
            {
                if (WSAGetLastError() != WSA_IO_PENDING)
                {
                    std::cerr << "Failed to notify client disconnect: " << WSAGetLastError() << std::endl;
                    delete overlapped;
                }
            }
        }
    }

    // 패킷 처리
    void ProcessPacket(ClientSession* client, char* data, int length)
    {
        if (length < sizeof(PacketHeader))
        {
            return;
        }

        PacketHeader* header = reinterpret_cast<PacketHeader*>(data);

        switch (header->PacketType)
        {
        case EPacketType::MOVE:
        {
            if (length >= sizeof(MovePacket))
            {
                MovePacket* packet = reinterpret_cast<MovePacket*>(data);

                // 마지막 위치 저장 (속도 계산용)
                client->LastPosition.X = client->Position.X;
                client->LastPosition.Y = client->Position.Y;
                client->LastPosition.Z = client->Position.Z;

                // 클라이언트 상태 업데이트
                client->Position.X = packet->Position.X;
                client->Position.Y = packet->Position.Y;
                client->Position.Z = packet->Position.Z;
                client->Rotation.Pitch = packet->Rotation.Pitch;
                client->Rotation.Yaw = packet->Rotation.Yaw;
                client->Rotation.Roll = packet->Rotation.Roll;

                // 속도 정보 업데이트 (클라이언트에서 받은 속도 사용)
                client->Velocity.X = packet->Velocity.X;
                client->Velocity.Y = packet->Velocity.Y;
                client->Velocity.Z = packet->Velocity.Z;

                // 모든 클라이언트에게 위치 정보 전송
                BroadcastPosition(client);

                // 디버그 출력
                std::cout << "Client " << client->id << " moved: pos=("
                    << client->Position.X << "," << client->Position.Y << "," << client->Position.Z
                    << "), vel=(" << client->Velocity.X << "," << client->Velocity.Y << "," << client->Velocity.Z << ")" << std::endl;
            }
            break;
        }
        case EPacketType::JUMP:
        {
            if (length >= sizeof(JumpPacket))
            {
                JumpPacket* packet = reinterpret_cast<JumpPacket*>(data);

                // 클라이언트 점프 상태 업데이트
                client->IsJumping = packet->IsJumping;
                client->Position.X = packet->Position.X;
                client->Position.Y = packet->Position.Y;
                client->Position.Z = packet->Position.Z;
                client->Velocity.X = packet->Velocity.X;
                client->Velocity.Y = packet->Velocity.Y;
                client->Velocity.Z = packet->Velocity.Z;

                // 모든 클라이언트에게 위치 정보 전송
                BroadcastPosition(client);

                // 디버그 출력
                std::cout << "Client " << client->id << " jump state: "
                    << (client->IsJumping ? "jumping" : "landed") << std::endl;
            }
            break;
        }
        default:
            break;
        }
    }

    // 모든 클라이언트에게 위치 정보 전송
    void BroadcastPosition(ClientSession* sourceClient)
    {
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = sourceClient->id;  // 클라이언트 ID 포함
        packet.Position.X = sourceClient->Position.X;
        packet.Position.Y = sourceClient->Position.Y;
        packet.Position.Z = sourceClient->Position.Z;
        packet.Rotation.Pitch = sourceClient->Rotation.Pitch;
        packet.Rotation.Yaw = sourceClient->Rotation.Yaw;
        packet.Rotation.Roll = sourceClient->Rotation.Roll;
        packet.Velocity.X = sourceClient->Velocity.X;
        packet.Velocity.Y = sourceClient->Velocity.Y;
        packet.Velocity.Z = sourceClient->Velocity.Z;
        packet.IsJumping = sourceClient->IsJumping;

        std::lock_guard<std::mutex> lock(clientsMutex);

        for (const auto& pair : clients)
        {
            ClientSession* targetClient = pair.second;

            // 자신에게는 전송하지 않음 (클라이언트 권한에 따라 다르게 처리 가능)
            if (targetClient->id == sourceClient->id)
            {
                continue;
            }

            // 비동기 전송
            WSABUF wsaBuf;
            wsaBuf.buf = reinterpret_cast<char*>(&packet);
            wsaBuf.len = sizeof(packet);

            WSAOVERLAPPED* overlapped = new WSAOVERLAPPED();
            ZeroMemory(overlapped, sizeof(WSAOVERLAPPED));

            DWORD sendBytes = 0;

            if (WSASend(targetClient->socket, &wsaBuf, 1, &sendBytes, 0, overlapped, NULL) == SOCKET_ERROR)
            {
                if (WSAGetLastError() != WSA_IO_PENDING)
                {
                    std::cerr << "WSASend failed: " << WSAGetLastError() << std::endl;
                    delete overlapped;
                }
            }
        }
    }

    // 작업자 스레드 함수
    static DWORD WINAPI WorkerThreadProc(LPVOID arg)
    {
        IOCPServer* server = static_cast<IOCPServer*>(arg);
        server->WorkerThread();
        return 0;
    }

    // 작업자 스레드 구현
    void WorkerThread()
    {
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
                break;
            }

            // 에러 처리
            if (!result || bytesTransferred == 0)
            {
                if (client)
                {
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
    }

    // 자원 정리
    void CleanUp()
    {
        isRunning = false;

        // 작업자 스레드 종료 신호
        if (completionPort != NULL)
        {
            for (int i = 0; i < 16; i++)
            {
                PostQueuedCompletionStatus(completionPort, 0, 0, NULL);
            }
        }

        // 클라이언트 정리
        {
            std::lock_guard<std::mutex> lock(clientsMutex);

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
            closesocket(listenSocket);
            listenSocket = INVALID_SOCKET;
        }

        // IOCP 정리
        if (completionPort != NULL)
        {
            CloseHandle(completionPort);
            completionPort = NULL;
        }

        WSACleanup();
    }

    SOCKET listenSocket;
    HANDLE completionPort;
    int nextClientId;
    bool isRunning;

    std::unordered_map<int, ClientSession*> clients;
    std::mutex clientsMutex;
};

int main(int argc, char* argv[])
{
    // 포트 설정 (기본값 9000)
    int port = 9000;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }

    // 서버 생성 및 초기화
    IOCPServer server;
    if (!server.Initialize(port))
    {
        std::cerr << "Server initialization failed" << std::endl;
        return 1;
    }

    // 서버 실행
    std::cout << "서버 실행. 포트 번호: " << port << std::endl;
    std::cout << "IOCP 멀티플레이어 서버 시작됨..." << std::endl;

    server.Run();

    return 0;
}