// IOCPWorkerPool.cpp

#include "IOCPWorkerPool.h"
#include "Logger.h"
#include "NetworkSessionManager.h"
#include "PacketDispatcher.h"
#include "PacketTypes.h"
#include <WinSock2.h>
#include <WS2tcpip.h>


IOCPWorkerPool::IOCPWorkerPool(HANDLE iocp, std::atomic<bool>& isRunning)
    : completionPort(iocp), runningFlag(isRunning)
{
}

void IOCPWorkerPool::Start(int threadCount)
{
    for (int i = 0; i < threadCount; ++i)
    {
        HANDLE hThread = CreateThread(nullptr, 0, WorkerThreadProc, this, 0, nullptr);
        if (hThread) CloseHandle(hThread);
    }
}

DWORD WINAPI IOCPWorkerPool::WorkerThreadProc(LPVOID arg)
{
    IOCPWorkerPool* pool = reinterpret_cast<IOCPWorkerPool*>(arg);
    pool->WorkerLoop();
    return 0;
}

void IOCPWorkerPool::WorkerLoop()
{
    DWORD bytesTransferred = 0;
    ULONG_PTR completionKey = 0;
    OVERLAPPED* overlapped = nullptr;

    while (runningFlag.load())
    {
        BOOL result = GetQueuedCompletionStatus(
            completionPort, &bytesTransferred, &completionKey, &overlapped, INFINITE);

        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        if (completionKey == 0 && overlapped == nullptr)
        {
            LOG_INFO("IOCP �۾��� ������ ���� ��û ����");
            break;
        }

        if (!result || bytesTransferred == 0)
        {
            if (client)
            {
                LOG_WARNING("Ŭ���̾�Ʈ ���� ���� �Ǵ� ���� - ID: " + std::to_string(client->id));
                closesocket(client->socket);
            }
            if (overlapped && overlapped != &client->overlapped)
            {
                delete overlapped;
            }
            continue;
        }

        if (overlapped == &client->overlapped)
        {
            PacketDispatcher::SendPong(client); // �ӽ�: �� ó�� ����
            NetworkSessionManager::PostRecv(client);
        }
        else
        {
            delete overlapped;
        }
    }
}