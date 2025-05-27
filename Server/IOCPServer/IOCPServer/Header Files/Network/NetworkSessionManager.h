#pragma once
#include "ClientSession.h"
#include "Logger.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <memory>

class NetworkSessionManager {
public:
    // ���� �ɼ� ����
    static void SetSocketOptions(SOCKET socket);

    // IOCP ���
    static bool RegisterToIOCP(HANDLE iocpHandle, ClientSession* client);

    // �񵿱� ���� ����
    static bool PostRecv(ClientSession* client);

    // ��Ŷ ����
    static bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context);

    // ������ ��Ŷ ���� (����Ʈ ������ ���)
    static bool SendPacketSafe(ClientSession* client, const void* data, size_t size, const char* context);

    // ���� ���� Ȯ��
    static bool IsSocketConnected(SOCKET socket);

    // Ŭ���̾�Ʈ ���� ����
    static void DisconnectClient(ClientSession* client);

    // ���� ó��
    static std::string GetNetworkErrorString(int error);

private:
    // OVERLAPPED ����ü ����
    struct OverlappedWrapper {
        WSAOVERLAPPED overlapped;
        enum class OperationType { SEND, RECV } type;

        OverlappedWrapper(OperationType opType) : type(opType) {
            ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));
        }
    };

    // ���� �α�
    static void LogNetworkError(const std::string& operation, int error, int clientId = -1);
};