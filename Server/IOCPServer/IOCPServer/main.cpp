#include <iostream>
#include <signal.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "IOCPServer.h"
#include "Logger.h"

// 타이머 해상도 개선
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

// 전역 서버 인스턴스 (시그널 핸들러에서 사용)
IOCPServer* g_server = nullptr;

// Ctrl+C 시그널 핸들러 (Graceful Shutdown)
BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType) {
    switch (dwCtrlType) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        LOG_INFO("서버 종료 신호 수신됨");
        if (g_server) {
            g_server->Stop();
        }
        return TRUE;
    default:
        return FALSE;
    }
}

void PrintUsage(const char* programName) {
    std::cout << "사용법: " << programName << " [옵션]\n";
    std::cout << "옵션:\n";
    std::cout << "  -p, --port <포트번호>    서버 포트 (기본값: 9000)\n";
    std::cout << "  -l, --log <레벨>         로그 레벨 (DEBUG, INFO, WARNING, ERROR)\n";
    std::cout << "  -h, --help               이 도움말 표시\n";
    std::cout << "\n예시:\n";
    std::cout << "  " << programName << " --port 8080 --log INFO\n";
}

LogLevel ParseLogLevel(const std::string& level) {
    if (level == "DEBUG") return LogLevel::DEBUG_LEVEL;
    if (level == "INFO") return LogLevel::INFO_LEVEL;
    if (level == "WARNING") return LogLevel::WARNING_LEVEL;
    if (level == "ERROR") return LogLevel::ERROR_LEVEL;
    return LogLevel::INFO_LEVEL; // 기본값
}

int main(int argc, char* argv[]) {
	// 타이머 해상도 개선 (1ms 단위로 설정)
    timeBeginPeriod(1);
    // 기본 설정
    int port = 9000;
    LogLevel logLevel = LogLevel::DEBUG_LEVEL;

    // 명령행 인수 파싱
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
                    std::cerr << "오류: 유효하지 않은 포트 번호: " << port << std::endl;
                    return 1;
                }
            }
            else {
                std::cerr << "오류: 포트 번호가 지정되지 않았습니다." << std::endl;
                return 1;
            }
        }
        else if (arg == "-l" || arg == "--log") {
            if (i + 1 < argc) {
                logLevel = ParseLogLevel(argv[++i]);
            }
            else {
                std::cerr << "오류: 로그 레벨이 지정되지 않았습니다." << std::endl;
                return 1;
            }
        }
        else {
            std::cerr << "오류: 알 수 없는 옵션: " << arg << std::endl;
            PrintUsage(argv[0]);
            return 1;
        }
    }

    // 로거 설정
    Logger::GetInstance().SetLogLevel(logLevel);
    Logger::GetInstance().SetConsoleLogging(true);
    Logger::GetInstance().SetFileLogging(true);

#ifdef _DEBUG
    // 디버그 빌드에서는 더 자세한 로깅
    Logger::GetInstance().SetLogLevel(LogLevel::DEBUG_LEVEL);
    LOG_INFO("디버그 모드로 실행됨");
#endif

    // 시작 메시지
    LOG_INFO("================================================");
    LOG_INFO("       IOCP 멀티플레이어 게임 서버 v1.0         ");
    LOG_INFO("================================================");
    LOG_INFO("포트: " + std::to_string(port));
    LOG_INFO("로그 레벨: " + std::to_string(static_cast<int>(logLevel)));
    LOG_INFO("빌드 시간: " + std::string(__DATE__) + " " + std::string(__TIME__));

    try {
        // 서버 인스턴스 생성
        IOCPServer server;
        g_server = &server;

        // Ctrl+C 핸들러 등록
        if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
            LOG_WARNING("콘솔 제어 핸들러 등록 실패");
        }

        // 서버 초기화
        if (!server.Initialize(port)) {
            LOG_ERROR("서버 초기화 실패");
            return 1;
        }

        LOG_INFO("서버 시작됨. 연결을 기다리는 중...");
        LOG_INFO("종료하려면 Ctrl+C를 누르세요.");

        // 서버 실행
        server.Run();

        LOG_INFO("서버가 정상적으로 종료되었습니다.");

    }
    catch (const std::exception& e) {
        LOG_ERROR("예외 발생: " + std::string(e.what()));
        return 1;
    }
    catch (...) {
        LOG_ERROR("알 수 없는 예외 발생");
        return 1;
    }

    LOG_INFO("프로그램 종료");

	// 타이머 해상도 복원
    timeEndPeriod(1);

    return 0;
}