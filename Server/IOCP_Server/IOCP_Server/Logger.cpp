#include "Logger.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <Windows.h>

// 싱글톤 인스턴스
Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

// 생성자
Logger::Logger()
    : lastFlushTime(0), enabled(false), minLevel(LogLevel::INFO_LEVEL)
{
}

// 소멸자
Logger::~Logger() {
    Shutdown();
}

// 상태 확인
bool Logger::IsEnabled() const {
    return enabled;
}

// 초기화
void Logger::Initialize(const std::string& logDir) {
    {
        std::lock_guard<std::mutex> lock(logMutex);

        try {
            // 로그 디렉토리 생성
            std::filesystem::create_directory(logDir);

            // 현재 시간 가져오기
            auto now = std::chrono::system_clock::now();
            auto now_time = std::chrono::system_clock::to_time_t(now);
            struct tm timeInfo;
            localtime_s(&timeInfo, &now_time);

            // 파일명에 시간 포함
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &timeInfo);

            // 로그 파일 열기
            std::string logFileName = logDir + "/Server_" + std::string(buffer) + ".log";
            logFile.open(logFileName, std::ios::out | std::ios::app);

            if (!logFile.is_open()) {
                std::cerr << "로그 파일을 열 수 없습니다: " << logFileName << std::endl;
                enabled = false;
                return;
            }
            else {
                enabled = true;
                lastFlushTime = GetTickCount64();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "로그 시스템 초기화 중 오류 발생: " << e.what() << std::endl;
            enabled = false;
            return;
        }
    } // 여기서 락이 해제됨

    // 락이 해제된 후에 Info 호출
    if (enabled) {
        Info("로깅 시스템 초기화됨");
    }
}

// 로그 레벨 설정
void Logger::SetLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    minLevel = level;
    Info("로그 레벨 변경됨: " + GetLevelString(level));
}

// 로그 함수들
void Logger::Debug(const std::string& message) {
    Log(LogLevel::DEBUG_LEVEL, message);
}

void Logger::Info(const std::string& message) {
    Log(LogLevel::INFO_LEVEL, message);
}

void Logger::Warning(const std::string& message) {
    Log(LogLevel::WARNING_LEVEL, message);
}

void Logger::Error(const std::string& message) {
    Log(LogLevel::ERROR_LEVEL, message);
}

// 내부 로그 함수
void Logger::Log(LogLevel level, const std::string& message) {
    if (!enabled) return;
    if (level < minLevel) return;

    std::lock_guard<std::mutex> lock(logMutex);

    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    struct tm timeInfo;
    localtime_s(&timeInfo, &now_time);

    // 시간 문자열 만들기
    std::stringstream timeStr;
    timeStr << std::setfill('0') << std::setw(2) << timeInfo.tm_hour << ":"
        << std::setfill('0') << std::setw(2) << timeInfo.tm_min << ":"
        << std::setfill('0') << std::setw(2) << timeInfo.tm_sec << "."
        << std::setfill('0') << std::setw(3) << now_ms.count();

    // 로그 레벨 문자열
    std::string levelStr = GetLevelString(level);

    // 로그 포맷: [시간] [레벨] 메시지
    std::stringstream ss;
    ss << "[" << timeStr.str() << "] [" << levelStr << "] " << message;

    std::string formattedMessage = ss.str();

    // 콘솔에 출력 (색상 적용)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD originalAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    originalAttrs = csbi.wAttributes;

    // 로그 레벨에 따른 색상 설정
    switch (level) {
    case LogLevel::DEBUG_LEVEL:
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        break;
    case LogLevel::INFO_LEVEL:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case LogLevel::WARNING_LEVEL:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case LogLevel::ERROR_LEVEL:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    }

    // 콘솔에 출력
    std::cout << formattedMessage << std::endl;

    // 원래 색상으로 복원
    SetConsoleTextAttribute(hConsole, originalAttrs);

    // 파일에 기록
    if (logFile.is_open()) {
        logFile << formattedMessage << std::endl;

        // 주기적으로 파일 버퍼 비우기
        uint64_t currentTime = GetTickCount64();
        if (currentTime - lastFlushTime > 5000) { // 5초마다 버퍼 비우기
            Flush();
            lastFlushTime = currentTime;
        }
    }
}

// 로그 레벨 문자열 반환
std::string Logger::GetLevelString(LogLevel level) const {
    switch (level) {
    case LogLevel::DEBUG_LEVEL:   return "DEBUG";
    case LogLevel::INFO_LEVEL:    return "INFO";
    case LogLevel::WARNING_LEVEL: return "WARNING";
    case LogLevel::ERROR_LEVEL:   return "ERROR";
    default:                return "UNKNOWN";
    }
}

// 버퍼 비우기
void Logger::Flush() {
    if (logFile.is_open()) {
        logFile.flush();
    }
}

// 종료 처리
void Logger::Shutdown() {
    if (enabled) {
        Info("로깅 시스템 종료됨");
        Flush();
        if (logFile.is_open()) {
            logFile.close();
        }
        enabled = false;
    }
}