#pragma once
#include <unordered_map>
#include <mutex>
#include "ClientSession.h"

class IOCPServer {
public:
    IOCPServer();
    ~IOCPServer();

    bool Initialize(int port);
    void Run();

private:
    bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context = "Unknown");
    void SendClientId(ClientSession* client);
    void BroadcastNewPlayer(ClientSession* newClient);
    void SendExistingPlayers(ClientSession* newClient);
    bool StartRecv(ClientSession* client);
    void RemoveClient(int clientId);
    void NotifyClientDisconnect(int disconnectedClientId);
    void ProcessPacket(ClientSession* client, char* data, int length);
    void BroadcastPosition(ClientSession* sourceClient);
    void WorkerThread();
    static DWORD WINAPI WorkerThreadProc(LPVOID arg);
    void CleanUp();

    SOCKET listenSocket;
    HANDLE completionPort;
    int nextClientId;
    bool isRunning;

    std::unordered_map<int, ClientSession*> clients;
    std::mutex clientsMutex;
};
