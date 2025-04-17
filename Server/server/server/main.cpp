#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <mutex>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

// ��Ŷ Ÿ�� ����
enum class EPacketType : uint8_t
{
    MOVE = 0,
    JUMP = 1,
    POSITION_UPDATE = 2,
    CLIENT_ID = 3  // Ŭ���̾�Ʈ ID �Ҵ��� ���� ��Ŷ Ÿ�� �߰�
};

// ��Ŷ ����ü ����
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
    struct { float X, Y, Z; } Velocity;  // �ӵ� ���� �߰�
};

struct JumpPacket
{
    PacketHeader Header;
    bool IsJumping;
    struct { float X, Y, Z; } Position;
    struct { float X, Y, Z; } Velocity;  // �ӵ� ���� �߰�
};

struct PositionUpdatePacket
{
    PacketHeader Header;
    int32_t ClientId;  // Ŭ���̾�Ʈ ID �߰�
    struct { float X, Y, Z; } Position;
    struct { float Pitch, Yaw, Roll; } Rotation;
    struct { float X, Y, Z; } Velocity;  // �ӵ� ���� �߰�
    bool IsJumping;
};

struct ClientIdPacket
{
    PacketHeader Header;
    int32_t ClientId;
};
#pragma pack(pop)

// IOCP�� ���� ����ü
struct ClientSession
{
    SOCKET socket;
    SOCKADDR_IN addr;
    char recvBuffer[1024];
    WSAOVERLAPPED overlapped;
    WSABUF wsaBuf;
    int id;

    // �÷��̾� ����
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
    } Velocity;  // �ӵ� ���� �߰�

    bool IsJumping;

    // ������ ��ġ ���� (�ӵ� ����)
    struct
    {
        float X, Y, Z;
    } LastPosition;

    // ������ ������Ʈ �ð�
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
        // ���� �ʱ�ȭ
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            std::cerr << "WSAStartup failed" << std::endl;
            return false;
        }

        // ���� ����
        listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
        if (listenSocket == INVALID_SOCKET)
        {
            std::cerr << "Socket creation failed" << std::endl;
            CleanUp();
            return false;
        }

        // ���ε�
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

        // ����
        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            std::cerr << "Listen failed" << std::endl;
            CleanUp();
            return false;
        }

        // IOCP ����
        completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        if (completionPort == NULL)
        {
            std::cerr << "CreateIoCompletionPort failed" << std::endl;
            CleanUp();
            return false;
        }

        // CPU ���� Ȯ��
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        int threadCount = sysInfo.dwNumberOfProcessors * 2;

        // �۾��� ������ ����
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
            // Ŭ���̾�Ʈ ���� ����
            SOCKADDR_IN clientAddr;
            int addrLen = sizeof(clientAddr);
            SOCKET clientSocket = WSAAccept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen, NULL, 0);

            if (clientSocket == INVALID_SOCKET)
            {
                std::cerr << "Accept failed" << std::endl;
                continue;
            }

            // Ŭ���̾�Ʈ ���� ����
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

            // IOCP�� ���� ���
            if (CreateIoCompletionPort((HANDLE)client->socket, completionPort, (ULONG_PTR)client, 0) == NULL)
            {
                std::cerr << "Failed to associate socket with IOCP" << std::endl;
                closesocket(client->socket);
                delete client;
                continue;
            }

            // Ŭ���̾�Ʈ �ʿ� �߰�
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients[client->id] = client;
            }

            // Ŭ���̾�Ʈ ���� ���� ���
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
            std::cout << "Client connected: " << clientIP << ":" << ntohs(clientAddr.sin_port) << " (ID: " << client->id << ")" << std::endl;

            // Ŭ���̾�Ʈ���� ID �Ҵ� ��Ŷ ����
            SendClientId(client);

            // �� �÷��̾� ���� ������ �ٸ� ��� Ŭ���̾�Ʈ���� ����
            BroadcastNewPlayer(client);

            // �̹� ������ �ٸ� �÷��̾� ������ �� Ŭ���̾�Ʈ���� ����
            SendExistingPlayers(client);

            // �񵿱� ���� ����
            StartRecv(client);
        }
    }

private:
    // Ŭ���̾�Ʈ���� ID �Ҵ� ��Ŷ ����
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

    // �� �÷��̾� ������ �ٸ� ��� Ŭ���̾�Ʈ���� ����
    void BroadcastNewPlayer(ClientSession* newClient)
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

            // �񵿱� ����
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

    // �̹� ������ �ٸ� �÷��̾� ������ �� Ŭ���̾�Ʈ���� ����
    void SendExistingPlayers(ClientSession* newClient)
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

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

            // �񵿱� ����
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

    // �񵿱� ���� ����
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

    // Ŭ���̾�Ʈ ����
    void RemoveClient(int clientId)
    {
        std::lock_guard<std::mutex> lock(clientsMutex);

        auto it = clients.find(clientId);
        if (it != clients.end())
        {
            ClientSession* client = it->second;
            closesocket(client->socket);
            std::cout << "Client disconnected (ID: " << client->id << ")" << std::endl;

            // �ٸ� Ŭ���̾�Ʈ�鿡�� ���� ���� �˸�
            NotifyClientDisconnect(clientId);

            clients.erase(it);
            delete client;
        }
    }

    // Ŭ���̾�Ʈ ���� ������ �ٸ� Ŭ���̾�Ʈ�鿡�� �˸�
    void NotifyClientDisconnect(int disconnectedClientId)
    {
        // ���⼭�� PositionUpdatePacket�� ����Ͽ� ��ġ�� ��ȿ�� ��(-999999)���� ����
        // �����δ� ������ ��Ŀ��Ʈ ��Ŷ Ÿ���� ����� ���� �� ����
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = disconnectedClientId;
        packet.Position.X = -999999.0f;  // ��ȿ�� ��ġ�� ���� - Ŭ���̾�Ʈ���� �� ���� ���� ����
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

            // ������ ���� Ŭ���̾�Ʈ�� ����
            if (targetClient->id == disconnectedClientId)
            {
                continue;
            }

            // �񵿱� ����
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

    // ��Ŷ ó��
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

                // ������ ��ġ ���� (�ӵ� ����)
                client->LastPosition.X = client->Position.X;
                client->LastPosition.Y = client->Position.Y;
                client->LastPosition.Z = client->Position.Z;

                // Ŭ���̾�Ʈ ���� ������Ʈ
                client->Position.X = packet->Position.X;
                client->Position.Y = packet->Position.Y;
                client->Position.Z = packet->Position.Z;
                client->Rotation.Pitch = packet->Rotation.Pitch;
                client->Rotation.Yaw = packet->Rotation.Yaw;
                client->Rotation.Roll = packet->Rotation.Roll;

                // �ӵ� ���� ������Ʈ (Ŭ���̾�Ʈ���� ���� �ӵ� ���)
                client->Velocity.X = packet->Velocity.X;
                client->Velocity.Y = packet->Velocity.Y;
                client->Velocity.Z = packet->Velocity.Z;

                // ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
                BroadcastPosition(client);

                // ����� ���
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

                // Ŭ���̾�Ʈ ���� ���� ������Ʈ
                client->IsJumping = packet->IsJumping;
                client->Position.X = packet->Position.X;
                client->Position.Y = packet->Position.Y;
                client->Position.Z = packet->Position.Z;
                client->Velocity.X = packet->Velocity.X;
                client->Velocity.Y = packet->Velocity.Y;
                client->Velocity.Z = packet->Velocity.Z;

                // ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
                BroadcastPosition(client);

                // ����� ���
                std::cout << "Client " << client->id << " jump state: "
                    << (client->IsJumping ? "jumping" : "landed") << std::endl;
            }
            break;
        }
        default:
            break;
        }
    }

    // ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
    void BroadcastPosition(ClientSession* sourceClient)
    {
        PositionUpdatePacket packet;
        packet.Header.PacketType = EPacketType::POSITION_UPDATE;
        packet.Header.PacketSize = sizeof(PositionUpdatePacket);
        packet.ClientId = sourceClient->id;  // Ŭ���̾�Ʈ ID ����
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

            // �ڽſ��Դ� �������� ���� (Ŭ���̾�Ʈ ���ѿ� ���� �ٸ��� ó�� ����)
            if (targetClient->id == sourceClient->id)
            {
                continue;
            }

            // �񵿱� ����
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

    // �۾��� ������ �Լ�
    static DWORD WINAPI WorkerThreadProc(LPVOID arg)
    {
        IOCPServer* server = static_cast<IOCPServer*>(arg);
        server->WorkerThread();
        return 0;
    }

    // �۾��� ������ ����
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

            // Ŭ���̾�Ʈ ����
            ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

            // ���� ����
            if (completionKey == 0 && overlapped == nullptr)
            {
                break;
            }

            // ���� ó��
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

            // ������ ���� ó��
            if (overlapped == &client->overlapped)
            {
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
    }

    // �ڿ� ����
    void CleanUp()
    {
        isRunning = false;

        // �۾��� ������ ���� ��ȣ
        if (completionPort != NULL)
        {
            for (int i = 0; i < 16; i++)
            {
                PostQueuedCompletionStatus(completionPort, 0, 0, NULL);
            }
        }

        // Ŭ���̾�Ʈ ����
        {
            std::lock_guard<std::mutex> lock(clientsMutex);

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
            closesocket(listenSocket);
            listenSocket = INVALID_SOCKET;
        }

        // IOCP ����
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
    // ��Ʈ ���� (�⺻�� 9000)
    int port = 9000;
    if (argc > 1)
    {
        port = atoi(argv[1]);
    }

    // ���� ���� �� �ʱ�ȭ
    IOCPServer server;
    if (!server.Initialize(port))
    {
        std::cerr << "Server initialization failed" << std::endl;
        return 1;
    }

    // ���� ����
    std::cout << "���� ����. ��Ʈ ��ȣ: " << port << std::endl;
    std::cout << "IOCP ��Ƽ�÷��̾� ���� ���۵�..." << std::endl;

    server.Run();

    return 0;
}