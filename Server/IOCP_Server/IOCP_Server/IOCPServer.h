// IOCPServer.h (리팩토링된 버전)
#pragma once
#include "ClientSession.h"
#include "NetworkManager.h"
#include <mutex>
#include <unordered_map>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

class IOCPServer {
public:
    IOCPServer();
    ~IOCPServer();

    bool Initialize(int port);
    void Run();
    void CleanUp();

    void AcceptClient(SOCKET clientSocket, SOCKADDR_IN clientAddr);
    void Update(float DeltaTime);

    int GetClientCount() const;
    std::string GetSocketErrorString(int error) const;

    static DWORD WINAPI WorkerThreadProc(LPVOID arg);
    void WorkerThread();

private:
    std::unordered_map<int, ClientSession*> clients;
    mutable std::mutex clientsMutex;

    NetworkManager networkManager;

    bool isRunning;
    int nextClientId;
};