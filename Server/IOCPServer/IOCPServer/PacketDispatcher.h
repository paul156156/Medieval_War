#pragma once
#include "ClientSession.h"
#include "PacketTypes.h"
#include <unordered_map>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

class PacketDispatcher {
public:
    // �⺻ ��Ŷ ����
    static void SendClientId(ClientSession* client);
    //static void SendInitialPosition(ClientSession* client);
    static void SendPong(ClientSession* client);

    // �÷��̾� ���� ��ε�ĳ��Ʈ
    static void BroadcastNewPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    static void SendExistingPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    static void BroadcastPlayerUpdate(ClientSession* sourceClient, const std::unordered_map<int, ClientSession*>& clients);

    // ���� ����
    static void NotifyPlayerDisconnect(int disconnectedClientId, const std::unordered_map<int, ClientSession*>& clients);

	// �÷��̾� ���� ��ε�ĳ��Ʈ
    static void BroadcastPlayerState(ClientSession* sourceClient, EPlayerState action, const std::unordered_map<int, ClientSession*>& clients);

	// �÷��̾� �׼� ��ε�ĳ��Ʈ
    static void BroadcastPlayerAction(ClientSession* sourceClient, EPlayerAction action, const std::unordered_map<int, ClientSession*>& clients);
    
    // ��Ŷ ���� �� ó��
    static bool ProcessReceivedPacket(ClientSession* client, char* data, int length);

private:
    // ��Ŷ ���� ����
    static ClientIdPacket CreateClientIdPacket(int clientId);
    static OutputPacket CreateOutputPacket(ClientSession* client);
    static PongPacket CreatePongPacket(ClientSession* client);
    static DisconnectPacket CreateDisconnectPacket(int clientId);

    // ��Ŷ ����
    static bool ValidatePacketHeader(const PacketHeader* header, size_t receivedSize);
    static bool ValidateInputPacket(const InputPacket* packet);
    static bool ValidateOutputPacket(const OutputPacket* packet);

    // ���� ��Ŷ ó����
    static void HandlePingPacket(ClientSession* client, const PingPacket* packet);
    static void HandleInputPacket(ClientSession* client, const InputPacket* packet);
    static void HandleInitPacket(ClientSession* client, const InitPacket* packet);
    static void HandleConnectPacket(ClientSession* client, const ConnectPacket* packet);
    static void HandleDisconnectPacket(ClientSession* client, const DisconnectPacket* packet);

    // �α� �� ���
    static void LogPacketSent(const char* packetType, int clientId, size_t size);
    static void LogPacketReceived(const char* packetType, int clientId, size_t size);
    static void LogBroadcastStats(const char* context, int successCount, int totalCount);

    // ���� �÷��̾���� ID�� �� Ŭ���̾�Ʈ���� ����
    static void SendExistingPlayerIDs(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    // �� �÷��̾��� ID�� ���� Ŭ���̾�Ʈ�鿡�� ����
    static void BroadcastNewPlayerID(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);

};