#pragma once
#include "ClientSession.h"
#include "PacketTypes.h"
#include <unordered_map>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

class PacketDispatcher {
public:
    // 기본 패킷 전송
    static void SendClientId(ClientSession* client);
    //static void SendInitialPosition(ClientSession* client);
    static void SendPong(ClientSession* client);

    // 플레이어 정보 브로드캐스트
    static void BroadcastNewPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    static void SendExistingPlayer(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    static void BroadcastPlayerUpdate(ClientSession* sourceClient, const std::unordered_map<int, ClientSession*>& clients);

    // 연결 관리
    static void NotifyPlayerDisconnect(int disconnectedClientId, const std::unordered_map<int, ClientSession*>& clients);

	// 플레이어 상태 브로드캐스트
    static void BroadcastPlayerState(ClientSession* sourceClient, EPlayerState action, const std::unordered_map<int, ClientSession*>& clients);

	// 플레이어 액션 브로드캐스트
    static void BroadcastPlayerAction(ClientSession* sourceClient, EPlayerAction action, const std::unordered_map<int, ClientSession*>& clients);
    
    // 패킷 검증 및 처리
    static bool ProcessReceivedPacket(ClientSession* client, char* data, int length);

private:
    // 패킷 생성 헬퍼
    static ClientIdPacket CreateClientIdPacket(int clientId);
    static OutputPacket CreateOutputPacket(ClientSession* client);
    static PongPacket CreatePongPacket(ClientSession* client);
    static DisconnectPacket CreateDisconnectPacket(int clientId);

    // 패킷 검증
    static bool ValidatePacketHeader(const PacketHeader* header, size_t receivedSize);
    static bool ValidateInputPacket(const InputPacket* packet);
    static bool ValidateOutputPacket(const OutputPacket* packet);

    // 개별 패킷 처리기
    static void HandlePingPacket(ClientSession* client, const PingPacket* packet);
    static void HandleInputPacket(ClientSession* client, const InputPacket* packet);
    static void HandleInitPacket(ClientSession* client, const InitPacket* packet);
    static void HandleConnectPacket(ClientSession* client, const ConnectPacket* packet);
    static void HandleDisconnectPacket(ClientSession* client, const DisconnectPacket* packet);

    // 로깅 및 통계
    static void LogPacketSent(const char* packetType, int clientId, size_t size);
    static void LogPacketReceived(const char* packetType, int clientId, size_t size);
    static void LogBroadcastStats(const char* context, int successCount, int totalCount);

    // 기존 플레이어들의 ID를 새 클라이언트에게 전송
    static void SendExistingPlayerIDs(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);
    // 새 플레이어의 ID를 기존 클라이언트들에게 전송
    static void BroadcastNewPlayerID(ClientSession* newClient, const std::unordered_map<int, ClientSession*>& clients);

};