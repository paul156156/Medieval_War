// IOCPWorkerPool.h
#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "ClientSession.h"
#include "Logger.h"
#include <atomic>
#include <Windows.h>

class IOCPWorkerPool
{
public:
    IOCPWorkerPool(HANDLE iocp, std::atomic<bool>& isRunning);
    void Start(int threadCount);

private:
    static DWORD WINAPI WorkerThreadProc(LPVOID arg);
    void WorkerLoop();

    HANDLE completionPort;
    std::atomic<bool>& runningFlag;
};