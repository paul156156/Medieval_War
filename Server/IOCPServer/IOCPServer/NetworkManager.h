#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include "Logger.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    // �ʱ�ȭ �� ����
    bool InitializeSocket(int port);
    bool SetupIOCP();
    void Shutdown();

    // ������
    SOCKET GetListenSocket() const;
    HANDLE GetCompletionPort() const;

    // ��ƿ��Ƽ
    std::string GetSocketErrorString(int error) const;
    bool IsValidSocket(SOCKET socket) const;

private:
    SOCKET listenSocket;
    HANDLE completionPort;
    bool initialized;

    // ���� �ɼ� ����
    bool SetListenSocketOptions();

    // ���� �޽��� ó��
    void LogSocketError(const std::string& operation, int error) const;
};