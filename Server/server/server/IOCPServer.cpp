#include "IOCPServer.h"
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include "PacketTypes.h"

IOCPServer::IOCPServer() : listenSocket(INVALID_SOCKET), completionPort(NULL), nextClientId(1), isRunning(true) {}

IOCPServer::~IOCPServer() {
	CleanUp();
}

bool IOCPServer::Initialize(int port)
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

void IOCPServer::Run()
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
		client->State = EPlayerState::IDLE;
		client->LastUpdateTime = GetTickCount64() / 1000.0f;
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

bool IOCPServer::SendPacket(ClientSession* client, const void* data, size_t size, const char* context)
{
	if (!client || size == 0)
	{
		std::cerr << "[SendPacket] Invalid parameters. Context: " << context << std::endl;
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
			std::cerr << "[SendPacket] WSASend failed. Error: " << error
				<< ", Context: " << context
				<< ", ClientId: " << client->id << std::endl;

			delete overlapped;
			return false;
		}
	}

	return true;
}

// Ŭ���̾�Ʈ���� ID �Ҵ� ��Ŷ ����
void IOCPServer::SendClientId(ClientSession* client)
{
	ClientIdPacket packet;
	packet.Header.PacketType = EPacketType::CLIENT_ID;
	packet.Header.PacketSize = sizeof(ClientIdPacket);
	packet.ClientId = client->id;

	SendPacket(client, &packet, sizeof(packet), "SendClientId");

	std::cout << "Sent client ID " << client->id << " to new client" << std::endl;
}

// �� �÷��̾� ������ �ٸ� ��� Ŭ���̾�Ʈ���� ����
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
		packet.Rotation = newClient->Rotation;
		packet.Velocity = newClient->Velocity;
		packet.State = newClient->State;

		// �񵿱� ����
		SendPacket(targetClient, &packet, sizeof(packet), "BroadcastNewPlayer");
	}
}

// �̹� ������ �ٸ� �÷��̾� ������ �� Ŭ���̾�Ʈ���� ����
void IOCPServer::SendExistingPlayers(ClientSession* newClient)
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
		packet.Position = existingClient->Position;
		packet.Rotation = existingClient->Rotation;
		packet.Velocity = existingClient->Velocity;
		packet.State = existingClient->State;

		// �񵿱� ����
		SendPacket(newClient, &packet, sizeof(packet), "SendExistingPlayers");
	}
}

// �񵿱� ���� ����
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
		std::cerr << "WSARecv failed: " << WSAGetLastError() << std::endl;
		RemoveClient(client->id);
		return false;
	}

	return true;
}

// Ŭ���̾�Ʈ ����
void IOCPServer::RemoveClient(int clientId)
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
void IOCPServer::NotifyClientDisconnect(int disconnectedClientId)
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
	packet.State = EPlayerState::IDLE;

	for (const auto& pair : clients)
	{
		ClientSession* targetClient = pair.second;

		// ������ ���� Ŭ���̾�Ʈ�� ����
		if (targetClient->id == disconnectedClientId)
		{
			continue;
		}

		// �񵿱� ����
		SendPacket(targetClient, &packet, sizeof(packet), "NotifyClientDisconnect");
	}
}

// ��Ŷ ó��
void IOCPServer::ProcessPacket(ClientSession* client, char* data, int length)
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
			client->LastPosition = client->Position;

			// Ŭ���̾�Ʈ ���� ������Ʈ
			client->Position = packet->Position;
			client->Rotation = packet->Rotation;
			client->Velocity = packet->Velocity;
			client->State = packet->State;

			// ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
			BroadcastPosition(client);

			std::lock_guard<std::mutex> lock(logMutex);
			// ����� ���
			std::cout << "Client " << client->id << " moved: pos=("
				<< client->Position.X << "," << client->Position.Y << "," << client->Position.Z
				<< ") vel=("
				<< client->Velocity.X << "," << client->Velocity.Y << "," << client->Velocity.Z
				<< ") state=" << static_cast<int>(client->State) << std::endl;
		}
		break;
	}
	case EPacketType::JUMP:
	{
		if (length >= sizeof(JumpPacket))
		{
			JumpPacket* packet = reinterpret_cast<JumpPacket*>(data);

			// Ŭ���̾�Ʈ ���� ���� ������Ʈ
			client->Position = packet->Position;
			client->State = packet->State;

			// ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
			BroadcastPosition(client);

			// ����� ���
			std::cout << "Client " << client->id << " jump state: "
				<< static_cast<int>(client->State) << std::endl;
		}
		break;
	}
	case EPacketType::ATTACK:
	{
		if (length >= sizeof(AttackPacket))
		{
			AttackPacket* packet = reinterpret_cast<AttackPacket*>(data);

			// Ŭ���̾�Ʈ ���� ���� ������Ʈ
			client->Position = packet->Position;
			client->State = packet->State;

			// ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
			BroadcastPosition(client);

			// ����� ���
			std::cout << "Client " << client->id << " attack state: "
				<< static_cast<int>(client->State) << std::endl;
		}
		break;
	}
	default:
		break;
	}
}

// ��� Ŭ���̾�Ʈ���� ��ġ ���� ����
void IOCPServer::BroadcastPosition(ClientSession* sourceClient)
{
	PositionUpdatePacket packet;
	packet.Header.PacketType = EPacketType::POSITION_UPDATE;
	packet.Header.PacketSize = sizeof(PositionUpdatePacket);
	packet.ClientId = sourceClient->id;
	packet.Position = sourceClient->Position;
	packet.Rotation = sourceClient->Rotation;
	packet.Velocity = sourceClient->Velocity;
	packet.State = sourceClient->State;

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
		SendPacket(targetClient, &packet, sizeof(packet), "BroadcastPosition");
	}
}

// �۾��� ������ �Լ�
DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg)
{
	IOCPServer* server = static_cast<IOCPServer*>(arg);
	server->WorkerThread();
	return 0;
}

// �۾��� ������ ����
void IOCPServer::WorkerThread()
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
void IOCPServer::CleanUp()
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