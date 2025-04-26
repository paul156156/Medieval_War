#pragma once
#include <unordered_map>
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
    void AcceptNewClients(SOCKET clientSocket, SOCKADDR_IN clientAddr);  // �� Ŭ���̾�Ʈ ���� ó��
    bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context = "Unknown");  // ��Ŷ ����
    bool StartRecv(ClientSession* client);  // �񵿱� ���� ����
    void ProcessPacket(ClientSession* client, char* data, int length);  // ��Ŷ ó��

    // Ŭ���̾�Ʈ ���� �޼���
    void SendClientId(ClientSession* client);  // Ŭ���̾�Ʈ ID ����
    void BroadcastNewPlayer(ClientSession* newClient);  // �� �÷��̾� ���� ��ε�ĳ��Ʈ
    void SendExistingPlayers(ClientSession* newClient);  // ���� �÷��̾� ���� ����
    void RemoveClient(int clientId);  // Ŭ���̾�Ʈ ����
    void NotifyClientDisconnect(int disconnectedClientId);  // Ŭ���̾�Ʈ ���� ���� �˸�

    // ���� ���� �޼���
    void HandleInputPacket(ClientSession* client, const InputPacket* packet);  // �Է� ��Ŷ ó��
    void Update(float DeltaTime);  // ���� ���� ������Ʈ
    void BroadcastPosition(ClientSession* sourceClient);  // ��ġ ���� ��ε�ĳ��Ʈ

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
};