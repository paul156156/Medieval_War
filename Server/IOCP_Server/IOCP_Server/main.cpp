// main.cpp (리팩토링된 버전)
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "IOCPServer.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
    int port = 9000;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

#ifdef _DEBUG
    Logger::GetInstance().SetLogLevel(LogLevel::INFO_LEVEL);
#endif

    IOCPServer server;
    if (!server.Initialize(port)) {
        LOG_ERROR("서버 초기화 실패");
        return 1;
    }

    LOG_INFO("서버 실행. 포트 번호: " + std::to_string(port));
    server.Run();
    return 0;
}
