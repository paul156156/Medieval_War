#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "Logger.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    // 초기화 및 정리
    bool InitializeSocket(int port);
    bool SetupIOCP();
    void Shutdown();

    // 접근자
    SOCKET GetListenSocket() const;
    HANDLE GetCompletionPort() const;

    // 유틸리티
    std::string GetSocketErrorString(int error) const;
    bool IsValidSocket(SOCKET socket) const;

private:
    SOCKET listenSocket;
    HANDLE completionPort;
    bool initialized;

    // 소켓 옵션 설정
    bool SetListenSocketOptions();

    // 오류 메시지 처리
    void LogSocketError(const std::string& operation, int error) const;
};