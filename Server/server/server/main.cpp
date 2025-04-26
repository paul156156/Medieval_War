#include <iostream>
#include "IOCPServer.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
    int port = 9000;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    // ����� ��忡���� �� �α� Ȱ��ȭ
#ifdef _DEBUG
    Logger::GetInstance().SetLogLevel(LogLevel::INFO_LEVEL);
#endif

    IOCPServer server;
    if (!server.Initialize(port)) {
        LOG_ERROR("���� �ʱ�ȭ ����");
        return 1;
    }

    LOG_INFO("���� ����. ��Ʈ ��ȣ: " + std::to_string(port));
    LOG_INFO("IOCP ��Ƽ�÷��̾� ���� ���۵�...");

    server.Run();
    return 0;
}