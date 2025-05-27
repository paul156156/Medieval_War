#pragma once
#include "ClientSession.h"
#include "Logger.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <memory>

class NetworkSessionManager {
public:
    // 소켓 옵션 설정
    static void SetSocketOptions(SOCKET socket);

    // IOCP 등록
    static bool RegisterToIOCP(HANDLE iocpHandle, ClientSession* client);

    // 비동기 수신 시작
    static bool PostRecv(ClientSession* client);

    // 패킷 전송
    static bool SendPacket(ClientSession* client, const void* data, size_t size, const char* context);

    // 안전한 패킷 전송 (스마트 포인터 사용)
    static bool SendPacketSafe(ClientSession* client, const void* data, size_t size, const char* context);

    // 소켓 상태 확인
    static bool IsSocketConnected(SOCKET socket);

    // 클라이언트 연결 종료
    static void DisconnectClient(ClientSession* client);

    // 에러 처리
    static std::string GetNetworkErrorString(int error);

private:
    // OVERLAPPED 구조체 래퍼
    struct OverlappedWrapper {
        WSAOVERLAPPED overlapped;
        enum class OperationType { SEND, RECV } type;

        OverlappedWrapper(OperationType opType) : type(opType) {
            ZeroMemory(&overlapped, sizeof(WSAOVERLAPPED));
        }
    };

    // 에러 로깅
    static void LogNetworkError(const std::string& operation, int error, int clientId = -1);
};