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

    std::cout << "���� ����. ��Ʈ ��ȣ: " << port << std::endl;
    std::cout << "IOCP ��Ƽ�÷��̾� ���� ���۵�..." << std::endl;

    server.Run();
    return 0;
}
