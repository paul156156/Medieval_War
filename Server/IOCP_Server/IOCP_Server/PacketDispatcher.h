// PacketDispatcher.h
#pragma once
#include "ClientSession.h"
#include "PacketTypes.h"
#include <unordered_map>
#include <WinSock2.h>
#include <WS2tcpip.h>


class PacketDispatcher
{
public:
    static void SendClientId(ClientSession* client);
    static void SendInitialPosition(ClientSession* client);
    static void BroadcastNewPlayerJoin(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    static void SendExistingPlayerList(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    static void SendPong(ClientSession* client);
};