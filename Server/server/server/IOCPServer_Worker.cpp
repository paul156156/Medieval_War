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
    // 스레드 ID 로깅 (디버깅 용도)
    DWORD threadId = GetCurrentThreadId();
    LOG_INFO("작업자 스레드 시작 (ThreadID: " + std::to_string(threadId) + ")");

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

        // 클라이언트 세션
        ClientSession* client = reinterpret_cast<ClientSession*>(completionKey);

        // 서버 종료
        if (completionKey == 0 && overlapped == nullptr)
        {
            LOG_INFO("작업자 스레드 종료 신호 받음 (ThreadID: " + std::to_string(threadId) + ")");
            break;
        }

        // 에러 처리
        if (!result || bytesTransferred == 0)
        {
            if (client)
            {
                // 에러 코드 로깅
                int lastError = WSAGetLastError();

                if (bytesTransferred == 0)
                {
                    LOG_INFO("클라이언트가 정상적으로 연결 종료함 - ID: " + std::to_string(client->id));
                }
                else if (!result)
                {
                    LOG_WARNING("클라이언트 소켓 에러 발생 - ID: " + std::to_string(client->id) +
                        ", 에러: " + GetSocketErrorString(lastError));
                }

                RemoveClient(client->id);
            }

            if (overlapped && overlapped != &client->overlapped)
            {
                delete overlapped;
            }

            continue;
        }

        // 데이터 수신 처리
        if (overlapped == &client->overlapped)
        {
            // 로그 정보 (너무 자세한 로그는 성능에 영향을 줄 수 있으므로 디버그 모드에만 활성화)
#ifdef _DEBUG
            LOG_DEBUG("데이터 수신: " + std::to_string(bytesTransferred) +
                " 바이트, 클라이언트 ID: " + std::to_string(client->id));
#endif

            // 패킷 처리
            ProcessPacket(client, client->recvBuffer, bytesTransferred);

            // 다시 비동기 수신 시작
            PostRecv(client);
        }
        // 데이터 송신 완료 처리
        else
        {
            // 송신 완료 후 OVERLAPPED 메모리 해제
            delete overlapped;
        }
    }

    LOG_INFO("작업자 스레드 종료 (ThreadID: " + std::to_string(threadId) + ")");
}
