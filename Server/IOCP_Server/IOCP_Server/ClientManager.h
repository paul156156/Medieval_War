// ClientManager.h
#pragma once
#include "ClientSession.h"
#include <mutex>
#include <unordered_map>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

class ClientManager
{
public:
    ClientManager();
    ~ClientManager();

    ClientSession* CreateSession(SOCKET socket, SOCKADDR_IN addr);
    void RemoveClient(int clientId);
    void NotifyClientDisconnect(int disconnectedClientId);

    std::unordered_map<int, ClientSession*>& GetClients();
    std::mutex& GetClientsMutex();

private:
    std::unordered_map<int, ClientSession*> clients;
    std::mutex clientsMutex;
    int nextClientId;

    void SetupSpawnPositions();
    std::vector<Vec3> SpawnPositions;
};