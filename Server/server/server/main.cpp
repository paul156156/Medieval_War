#include <iostream>
#include "IOCPServer.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
    int port = 9000;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    // 디버그 모드에서는 상세 로그 활성화
#ifdef _DEBUG
    Logger::GetInstance().SetLogLevel(LogLevel::INFO_LEVEL);
#endif

    IOCPServer server;
    if (!server.Initialize(port)) {
        LOG_ERROR("서버 초기화 실패");
        return 1;
    }

    LOG_INFO("서버 실행. 포트 번호: " + std::to_string(port));
    LOG_INFO("IOCP 멀티플레이어 서버 시작됨...");

    server.Run();
    return 0;
}