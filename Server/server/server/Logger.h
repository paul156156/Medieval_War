#pragma once
#include <string>
#include <fstream>
#include <mutex>

// 로그 레벨 정의
enum class LogLevel {
    DEBUG_LEVEL,
    INFO_LEVEL,
    WARNING_LEVEL,
    ERROR_LEVEL
};

class Logger {
public:
    // 싱글톤 인스턴스 얻기
    static Logger& GetInstance();

    // 로그 초기화 및 설정
    void Initialize(const std::string& logDir = "Logs");
    void SetLogLevel(LogLevel level);
    bool IsEnabled() const;

    // 로그 함수
    void Debug(const std::string& message);
    void Info(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);

    // 파일 처리
    void Flush();
    void Shutdown();

private:
    // 생성자 및 소멸자
    Logger();
    ~Logger();

    // 복사 방지
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // 내부 유틸리티 함수
    void Log(LogLevel level, const std::string& message);
    std::string GetLevelString(LogLevel level) const;

    // 멤버 변수
    std::ofstream logFile;
    std::mutex logMutex;
    uint64_t lastFlushTime;
    bool enabled;
    LogLevel minLevel;
};

// 편의를 위한 매크로
#define LOG_DEBUG(message) Logger::GetInstance().Debug(message)
#define LOG_INFO(message) Logger::GetInstance().Info(message)
#define LOG_WARNING(message) Logger::GetInstance().Warning(message)
#define LOG_ERROR(message) Logger::GetInstance().Error(message)