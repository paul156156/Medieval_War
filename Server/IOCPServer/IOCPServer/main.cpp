#include <iostream>
#include <signal.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "IOCPServer.h"
#include "Logger.h"

// Ÿ�̸� �ػ� ����
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

// ���� ���� �ν��Ͻ� (�ñ׳� �ڵ鷯���� ���)
IOCPServer* g_server = nullptr;

// Ctrl+C �ñ׳� �ڵ鷯 (Graceful Shutdown)
BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType) {
    switch (dwCtrlType) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        LOG_INFO("���� ���� ��ȣ ���ŵ�");
        if (g_server) {
            g_server->Stop();
        }
        return TRUE;
    default:
        return FALSE;
    }
}

void PrintUsage(const char* programName) {
    std::cout << "����: " << programName << " [�ɼ�]\n";
    std::cout << "�ɼ�:\n";
    std::cout << "  -p, --port <��Ʈ��ȣ>    ���� ��Ʈ (�⺻��: 9000)\n";
    std::cout << "  -l, --log <����>         �α� ���� (DEBUG, INFO, WARNING, ERROR)\n";
    std::cout << "  -h, --help               �� ���� ǥ��\n";
    std::cout << "\n����:\n";
    std::cout << "  " << programName << " --port 8080 --log INFO\n";
}

LogLevel ParseLogLevel(const std::string& level) {
    if (level == "DEBUG") return LogLevel::DEBUG_LEVEL;
    if (level == "INFO") return LogLevel::INFO_LEVEL;
    if (level == "WARNING") return LogLevel::WARNING_LEVEL;
    if (level == "ERROR") return LogLevel::ERROR_LEVEL;
    return LogLevel::INFO_LEVEL; // �⺻��
}

int main(int argc, char* argv[]) {
	// Ÿ�̸� �ػ� ���� (1ms ������ ����)
    timeBeginPeriod(1);
    // �⺻ ����
    int port = 9000;
    LogLevel logLevel = LogLevel::DEBUG_LEVEL;

    // ����� �μ� �Ľ�
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            PrintUsage(argv[0]);
            return 0;
        }
        else if (arg == "-p" || arg == "--port") {
            if (i + 1 < argc) {
                port = atoi(argv[++i]);
                if (port <= 0 || port > 65535) {
                    std::cerr << "����: ��ȿ���� ���� ��Ʈ ��ȣ: " << port << std::endl;
                    return 1;
                }
            }
            else {
                std::cerr << "����: ��Ʈ ��ȣ�� �������� �ʾҽ��ϴ�." << std::endl;
                return 1;
            }
        }
        else if (arg == "-l" || arg == "--log") {
            if (i + 1 < argc) {
                logLevel = ParseLogLevel(argv[++i]);
            }
            else {
                std::cerr << "����: �α� ������ �������� �ʾҽ��ϴ�." << std::endl;
                return 1;
            }
        }
        else {
            std::cerr << "����: �� �� ���� �ɼ�: " << arg << std::endl;
            PrintUsage(argv[0]);
            return 1;
        }
    }

    // �ΰ� ����
    Logger::GetInstance().SetLogLevel(logLevel);
    Logger::GetInstance().SetConsoleLogging(true);
    Logger::GetInstance().SetFileLogging(true);

#ifdef _DEBUG
    // ����� ���忡���� �� �ڼ��� �α�
    Logger::GetInstance().SetLogLevel(LogLevel::DEBUG_LEVEL);
    LOG_INFO("����� ���� �����");
#endif

    // ���� �޽���
    LOG_INFO("================================================");
    LOG_INFO("       IOCP ��Ƽ�÷��̾� ���� ���� v1.0         ");
    LOG_INFO("================================================");
    LOG_INFO("��Ʈ: " + std::to_string(port));
    LOG_INFO("�α� ����: " + std::to_string(static_cast<int>(logLevel)));
    LOG_INFO("���� �ð�: " + std::string(__DATE__) + " " + std::string(__TIME__));

    try {
        // ���� �ν��Ͻ� ����
        IOCPServer server;
        g_server = &server;

        // Ctrl+C �ڵ鷯 ���
        if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
            LOG_WARNING("�ܼ� ���� �ڵ鷯 ��� ����");
        }

        // ���� �ʱ�ȭ
        if (!server.Initialize(port)) {
            LOG_ERROR("���� �ʱ�ȭ ����");
            return 1;
        }

        LOG_INFO("���� ���۵�. ������ ��ٸ��� ��...");
        LOG_INFO("�����Ϸ��� Ctrl+C�� ��������.");

        // ���� ����
        server.Run();

        LOG_INFO("������ ���������� ����Ǿ����ϴ�.");

    }
    catch (const std::exception& e) {
        LOG_ERROR("���� �߻�: " + std::string(e.what()));
        return 1;
    }
    catch (...) {
        LOG_ERROR("�� �� ���� ���� �߻�");
        return 1;
    }

    LOG_INFO("���α׷� ����");

	// Ÿ�̸� �ػ� ����
    timeEndPeriod(1);

    return 0;
}