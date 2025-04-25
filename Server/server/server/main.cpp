#include <iostream>
#include "IOCPServer.h"

int main(int argc, char* argv[]) {
    int port = 9000;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    IOCPServer server;
    if (!server.Initialize(port)) {
        std::cerr << "Server initialization failed" << std::endl;
        return 1;
    }

    std::cout << "서버 실행. 포트 번호: " << port << std::endl;
    std::cout << "IOCP 멀티플레이어 서버 시작됨..." << std::endl;

    server.Run();
    return 0;
}
