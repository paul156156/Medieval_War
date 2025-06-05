#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>

// �α� ���� ����
enum class LogLevel {
    DEBUG_LEVEL = 0,
    INFO_LEVEL = 1,
    WARNING_LEVEL = 2,
    ERROR_LEVEL = 3
};

class Logger {
public:
    // �̱��� �ν��Ͻ� ��ȯ
    static Logger& GetInstance();

    // �ʱ�ȭ
    void Initialize(const std::string& filename = "server.log");

    // �α� ���
    void Log(LogLevel level, const std::string& message);

    // �α� ���� ����
    void SetLogLevel(LogLevel level);
    LogLevel GetLogLevel() const;

    // ���� �α� Ȱ��ȭ/��Ȱ��ȭ
    void SetFileLogging(bool enabled);
    void SetConsoleLogging(bool enabled);

    // �Ҹ���
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

// ���� ��ũ��
#define LOG_DEBUG(msg) Logger::GetInstance().Log(LogLevel::DEBUG_LEVEL, msg)
#define LOG_INFO(msg) Logger::GetInstance().Log(LogLevel::INFO_LEVEL, msg)
#define LOG_WARNING(msg) Logger::GetInstance().Log(LogLevel::WARNING_LEVEL, msg)
#define LOG_ERROR(msg) Logger::GetInstance().Log(LogLevel::ERROR_LEVEL, msg)

// ���Ǻ� �α� ��ũ��
#define LOG_DEBUG_IF(condition, msg) \
    do { if (condition) LOG_DEBUG(msg); } while(0)

#define LOG_INFO_IF(condition, msg) \
    do { if (condition) LOG_INFO(msg); } while(0)

// ���� �α� ����
template<typename... Args>
std::string FormatString(const std::string& format, Args... args) {
    std::ostringstream oss;
    ((oss << args), ...);
    return oss.str();
}