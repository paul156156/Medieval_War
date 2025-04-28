#include "IOCPServer.h"
#include "Logger.h"

DWORD WINAPI IOCPServer::WorkerThreadProc(LPVOID arg)
{
    IOCPServer* server = static_cast<IOCPServer*>(arg);
    server->WorkerThread();
    return 0;
}

void IOCPServer::WorkerThread()
{
    // ������ ID �α� (����� �뵵)
    DWORD threadId = GetCurrentThreadId();
    LOG_INFO("�۾��� ������ ���� (ThreadID: " + std::to_string(threadId) + ")");

    while (isRunning)
    {
        DWORD bytesTransferred = 0;
        ULONG_PTR completionKey = 0;
        OVERLAPPED* overlapped = nullptr;

        BOOL result = GetQueuedCompletionStatus(
            completionPort,
            &bytesTransferred,
            &completionKey,
            &overlapped,
            INFINITE);

        // Ŭ���̾�Ʈ ����
        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // ���� ����
        if (completionKey == 0 && overlapped == nullptr)
        {
            LOG_INFO("�۾��� ������ ���� ��ȣ ���� (ThreadID: " + std::to_string(threadId) + ")");
            break;
        }

        // ���� ó��
        if (!result || bytesTransferred == 0)
        {
            if (client)
            {
                // ���� �ڵ� �α�
                int lastError = WSAGetLastError();

                if (bytesTransferred == 0)
                {
                    LOG_INFO("Ŭ���̾�Ʈ�� ���������� ���� ������ - ID: " + std::to_string(client->id));
                }
                else if (!result)
                {
                    LOG_WARNING("Ŭ���̾�Ʈ ���� ���� �߻� - ID: " + std::to_string(client->id) +
                        ", ����: " + GetSocketErrorString(lastError));
                }

                RemoveClient(client->id);
            }

            if (overlapped && overlapped != &client->overlapped)
            {
                delete overlapped;
            }

            continue;
        }

        // ������ ���� ó��
        if (overlapped == &client->overlapped)
        {
            // �α� ���� (�ʹ� �ڼ��� �α״� ���ɿ� ������ �� �� �����Ƿ� ����� ��忡�� Ȱ��ȭ)
#ifdef _DEBUG
            LOG_DEBUG("������ ����: " + std::to_string(bytesTransferred) +
                " ����Ʈ, Ŭ���̾�Ʈ ID: " + std::to_string(client->id));
#endif

            // ��Ŷ ó��
            ProcessPacket(client, client->recvBuffer, bytesTransferred);

            // �ٽ� �񵿱� ���� ����
            PostRecv(client);
        }
        // ������ �۽� �Ϸ� ó��
        else
        {
            // �۽� �Ϸ� �� OVERLAPPED �޸� ����
            delete overlapped;
        }
    }

    LOG_INFO("�۾��� ������ ���� (ThreadID: " + std::to_string(threadId) + ")");
}
