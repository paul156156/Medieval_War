#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>

// 로그 레벨 정의
enum class LogLevel {
    DEBUG_LEVEL = 0,
    INFO_LEVEL = 1,
    WARNING_LEVEL = 2,
    ERROR_LEVEL = 3
};

class Logger {
public:
    // 싱글톤 인스턴스 반환
    static Logger& GetInstance();

    // 초기화
    void Initialize(const std::string& filename = "server.log");

    // 로그 출력
    void Log(LogLevel level, const std::string& message);

    // 로그 레벨 설정
    void SetLogLevel(LogLevel level);
    LogLevel GetLogLevel() const;

    // 파일 로깅 활성화/비활성화
    void SetFileLogging(bool enabled);
    void SetConsoleLogging(bool enabled);

    // 소멸자
    ~Logger();

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string GetTimestamp() const;
    std::string GetLevelString(LogLevel level) const;

    std::mutex logMutex;
    std::ofstream logFile;
    LogLevel currentLogLevel = LogLevel::INFO_LEVEL;
    bool fileLoggingEnabled = true;
    bool consoleLoggingEnabled = true;
    bool initialized = false;
};

// 편의 매크로
#define LOG_DEBUG(msg) Logger::GetInstance().Log(LogLevel::DEBUG_LEVEL, msg)
#define LOG_INFO(msg) Logger::GetInstance().Log(LogLevel::INFO_LEVEL, msg)
#define LOG_WARNING(msg) Logger::GetInstance().Log(LogLevel::WARNING_LEVEL, msg)
#define LOG_ERROR(msg) Logger::GetInstance().Log(LogLevel::ERROR_LEVEL, msg)

// 조건부 로깅 매크로
#define LOG_DEBUG_IF(condition, msg) \
    do { if (condition) LOG_DEBUG(msg); } while(0)

#define LOG_INFO_IF(condition, msg) \
    do { if (condition) LOG_INFO(msg); } while(0)

// 포맷 로깅 지원
template<typename... Args>
std::string FormatString(const std::string& format, Args... args) {
    std::ostringstream oss;
    ((oss << args), ...);
    return oss.str();
}