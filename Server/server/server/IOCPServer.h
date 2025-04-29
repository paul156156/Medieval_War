#pragma once
#include <unordered_map>
#include <vector>
#include <mutex>
#include "ClientSession.h"
#include "Logger.h"

class IOCPServer {
public:
    // ������ �� �Ҹ���
    IOCPServer();
    ~IOCPServer();

    // ���� �޼���
    bool Initialize(int port);  // ���� �ʱ�ȭ
    void Run();                 // ���� ����

private:
    // ��Ʈ��ũ ���� �޼���
    void AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr);  // �� Ŭ���̾�Ʈ ���� ó��
    bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context = "Unknown");  // ��Ŷ ����
    bool PostRecv(ClientSession* client);  // �񵿱� ���� ����
    void ProcessPacket(ClientSession* client, char* data, int length);  // ��Ŷ ó��

    // ���� �Լ�
    void SetSocketOptions(SOCKET socket);
    ClientSession* CreateSession(SOCKET socket, SOCKADDR_IN addr);
    bool RegisterToIOCP(ClientSession* client);
    void InitializeNewClientSession(ClientSession* client);

    // Ŭ���̾�Ʈ ���� �޼���
    void SendClientId(ClientSession* client);  // Ŭ���̾�Ʈ ID ����
	void SendInitialPosition(ClientSession* client);  // �ʱ� ��ġ ����
    void BroadcastNewPlayerJoin(ClientSession* newClient);  // �� �÷��̾� ���� ��ε�ĳ��Ʈ
    void SendExistingPlayerList(ClientSession* newClient);  // ���� �÷��̾� ���� ����
    void RemoveClient(int clientId);  // Ŭ���̾�Ʈ ����
    void NotifyClientDisconnect(int disconnectedClientId);  // Ŭ���̾�Ʈ ���� ���� �˸�
	void SendPong(ClientSession* client);  // Pong ��Ŷ ����

    // ���� ���� �޼���
    void HandleInputPacket(ClientSession* client, const InputPacket* packet);  // �Է� ��Ŷ ó��
    void Update(float DeltaTime);  // ���� ���� ������Ʈ
    void BroadcastPosition(ClientSession* sourceClient);  // ��ġ ���� ��ε�ĳ��Ʈ
    void SetupSpawnPositions();

    // ������ ���� �޼���
    void WorkerThread();  // �۾��� ������ ����
    static DWORD WINAPI WorkerThreadProc(LPVOID arg);  // �۾��� ������ ������
    void CleanUp();  // �ڿ� ����

    // ��ƿ��Ƽ �޼���
    std::string GetSocketErrorString(int error) const;
    int GetClientCount() const;

    // ��� ����
    SOCKET listenSocket;  // ������ ����
    HANDLE completionPort;  // IOCP �ڵ�
    int nextClientId;  // ���� Ŭ���̾�Ʈ ID
    bool isRunning;  // ���� ���� ����

    // �����̳� �� ����ȭ
    std::unordered_map<int, ClientSession*> clients;  // Ŭ���̾�Ʈ ��
    mutable std::mutex clientsMutex;  // Ŭ���̾�Ʈ ���� ���ؽ�
    // ���� ������ ���
    std::vector<Vec3> SpawnPositions;
};