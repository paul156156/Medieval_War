#pragma once
#include <string>
#include <fstream>
#include <mutex>

// �α� ���� ����
enum class LogLevel {
    DEBUG_LEVEL,
    INFO_LEVEL,
    WARNING_LEVEL,
    ERROR_LEVEL
};

class Logger {
public:
    // �̱��� �ν��Ͻ� ���
    static Logger& GetInstance();

    // �α� �ʱ�ȭ �� ����
    void Initialize(const std::string& logDir = "Logs");
    void SetLogLevel(LogLevel level);
    bool IsEnabled() const;

    // �α� �Լ�
    void Debug(const std::string& message);
    void Info(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);

    // ���� ó��
    void Flush();
    void Shutdown();

private:
    // ������ �� �Ҹ���
    Logger();
    ~Logger();

    // ���� ����
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // ���� ��ƿ��Ƽ �Լ�
    void Log(LogLevel level, const std::string& message);
    std::string GetLevelString(LogLevel level) const;

    // ��� ����
    std::ofstream logFile;
    std::mutex logMutex;
    uint64_t lastFlushTime;
    bool enabled;
    LogLevel minLevel;
};

// ���Ǹ� ���� ��ũ��
#define LOG_DEBUG(message) Logger::GetInstance().Debug(message)
#define LOG_INFO(message) Logger::GetInstance().Info(message)
#define LOG_WARNING(message) Logger::GetInstance().Warning(message)
#define LOG_ERROR(message) Logger::GetInstance().Error(message)