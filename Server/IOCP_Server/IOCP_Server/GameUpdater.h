// GameUpdater.h
#pragma once
#include "ClientSession.h"
#include <mutex>
#include <unordered_map>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

class GameUpdater
{
public:
    void UpdateClients(float DeltaTime, std::unordered_map<int, ClientSession*>& clients, std::mutex& clientsMutex);

private:
    void UpdateClient(ClientSession* client, float DeltaTime, float currentTime);
    void BroadcastPosition(ClientSession* sourceClient, std::unordered_map<int, ClientSession*>& clients);
};