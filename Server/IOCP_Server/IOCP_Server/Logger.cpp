#include "Logger.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <Windows.h>

// �̱��� �ν��Ͻ�
Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

// ������
Logger::Logger()
    : lastFlushTime(0), enabled(false), minLevel(LogLevel::INFO_LEVEL)
{
}

// �Ҹ���
Logger::~Logger() {
    Shutdown();
}

// ���� Ȯ��
bool Logger::IsEnabled() const {
    return enabled;
}

// �ʱ�ȭ
void Logger::Initialize(const std::string& logDir) {
    {
        std::lock_guard<std::mutex> lock(logMutex);

        try {
            // �α� ���丮 ����
            std::filesystem::create_directory(logDir);

            // ���� �ð� ��������
            auto now = std::chrono::system_clock::now();
            auto now_time = std::chrono::system_clock::to_time_t(now);
            struct tm timeInfo;
            localtime_s(&timeInfo, &now_time);

            // ���ϸ� �ð� ����
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", &timeInfo);

            // �α� ���� ����
            std::string logFileName = logDir + "/Server_" + std::string(buffer) + ".log";
            logFile.open(logFileName, std::ios::out | std::ios::app);

            if (!logFile.is_open()) {
                std::cerr << "�α� ������ �� �� �����ϴ�: " << logFileName << std::endl;
                enabled = false;
                return;
            }
            else {
                enabled = true;
                lastFlushTime = GetTickCount64();
            }
        }
        catch (const std::exception& e) {
            std::cerr << "�α� �ý��� �ʱ�ȭ �� ���� �߻�: " << e.what() << std::endl;
            enabled = false;
            return;
        }
    } // ���⼭ ���� ������

    // ���� ������ �Ŀ� Info ȣ��
    if (enabled) {
        Info("�α� �ý��� �ʱ�ȭ��");
    }
}

// �α� ���� ����
void Logger::SetLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    minLevel = level;
    Info("�α� ���� �����: " + GetLevelString(level));
}

// �α� �Լ���
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

// ���� �α� �Լ�
void Logger::Log(LogLevel level, const std::string& message) {
    if (!enabled) return;
    if (level < minLevel) return;

    std::lock_guard<std::mutex> lock(logMutex);

    // ���� �ð� ��������
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    struct tm timeInfo;
    localtime_s(&timeInfo, &now_time);

    // �ð� ���ڿ� �����
    std::stringstream timeStr;
    timeStr << std::setfill('0') << std::setw(2) << timeInfo.tm_hour << ":"
        << std::setfill('0') << std::setw(2) << timeInfo.tm_min << ":"
        << std::setfill('0') << std::setw(2) << timeInfo.tm_sec << "."
        << std::setfill('0') << std::setw(3) << now_ms.count();

    // �α� ���� ���ڿ�
    std::string levelStr = GetLevelString(level);

    // �α� ����: [�ð�] [����] �޽���
    std::stringstream ss;
    ss << "[" << timeStr.str() << "] [" << levelStr << "] " << message;

    std::string formattedMessage = ss.str();

    // �ֿܼ� ��� (���� ����)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD originalAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    originalAttrs = csbi.wAttributes;

    // �α� ������ ���� ���� ����
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

    // �ֿܼ� ���
    std::cout << formattedMessage << std::endl;

    // ���� �������� ����
    SetConsoleTextAttribute(hConsole, originalAttrs);

    // ���Ͽ� ���
    if (logFile.is_open()) {
        logFile << formattedMessage << std::endl;

        // �ֱ������� ���� ���� ����
        uint64_t currentTime = GetTickCount64();
        if (currentTime - lastFlushTime > 5000) { // 5�ʸ��� ���� ����
            Flush();
            lastFlushTime = currentTime;
        }
    }
}

// �α� ���� ���ڿ� ��ȯ
std::string Logger::GetLevelString(LogLevel level) const {
    switch (level) {
    case LogLevel::DEBUG_LEVEL:   return "DEBUG";
    case LogLevel::INFO_LEVEL:    return "INFO";
    case LogLevel::WARNING_LEVEL: return "WARNING";
    case LogLevel::ERROR_LEVEL:   return "ERROR";
    default:                return "UNKNOWN";
    }
}

// ���� ����
void Logger::Flush() {
    if (logFile.is_open()) {
        logFile.flush();
    }
}

// ���� ó��
void Logger::Shutdown() {
    if (enabled) {
        Info("�α� �ý��� �����");
        Flush();
        if (logFile.is_open()) {
            logFile.close();
        }
        enabled = false;
    }
}