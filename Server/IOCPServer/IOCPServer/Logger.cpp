#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <Windows.h>

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::Initialize(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);

    if (initialized) {
        return;
    }

    if (fileLoggingEnabled) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Warning: Could not open log file: " << filename << std::endl;
            fileLoggingEnabled = false;
        }
    }

    initialized = true;
    //Log(LogLevel::INFO_LEVEL, "Logger initialized");
    if (consoleLoggingEnabled) {
        std::cout << "[" << GetTimestamp() << "] [INFO] Logger initialized" << std::endl;
    }

    if (fileLoggingEnabled && logFile.is_open()) {
        logFile << "[" << GetTimestamp() << "] [INFO] Logger initialized" << std::endl;
        logFile.flush();
    }
}

void Logger::Log(LogLevel level, const std::string& message) {
    if (level < currentLogLevel) {
        return;
    }

    std::lock_guard<std::mutex> lock(logMutex);

    std::string timestamp = GetTimestamp();
    std::string levelStr = GetLevelString(level);
    std::string fullMessage = "[" + timestamp + "] [" + levelStr + "] " + message;

    // 콘솔 출력
    if (consoleLoggingEnabled) {
        // 윈도우 콘솔 색상 설정
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD originalColor = 7; // 기본 흰색

        switch (level) {
        case LogLevel::DEBUG_LEVEL:
            SetConsoleTextAttribute(hConsole, 8); // 회색
            break;
        case LogLevel::INFO_LEVEL:
            SetConsoleTextAttribute(hConsole, 7); // 흰색
            break;
        case LogLevel::WARNING_LEVEL:
            SetConsoleTextAttribute(hConsole, 14); // 노란색
            break;
        case LogLevel::ERROR_LEVEL:
            SetConsoleTextAttribute(hConsole, 12); // 빨간색
            break;
        }

        std::cout << fullMessage << std::endl;
        SetConsoleTextAttribute(hConsole, originalColor);
    }

    // 파일 출력
    if (fileLoggingEnabled && logFile.is_open()) {
        logFile << fullMessage << std::endl;
        logFile.flush();
    }
}

void Logger::SetLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentLogLevel = level;
}

LogLevel Logger::GetLogLevel() const {
    return currentLogLevel;
}

void Logger::SetFileLogging(bool enabled) {
    std::lock_guard<std::mutex> lock(logMutex);
    fileLoggingEnabled = enabled;
}

void Logger::SetConsoleLogging(bool enabled) {
    std::lock_guard<std::mutex> lock(logMutex);
    consoleLoggingEnabled = enabled;
}

Logger::~Logger() {
    if (logFile.is_open()) {
        Log(LogLevel::INFO_LEVEL, "Logger shutdown");
        logFile.close();
    }
}

//std::string Logger::GetTimestamp() const {
//    auto now = std::chrono::system_clock::now();
//    auto time_t = std::chrono::system_clock::to_time_t(now);
//    tm* timeinfo;
//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
//        now.time_since_epoch()) % 1000;
//
//    std::ostringstream oss;
//    oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
//    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
//
//    return oss.str();
//}

std::string Logger::GetTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    tm timeinfo{};
#ifdef _WIN32
    localtime_s(&timeinfo, &time_t);  // Windows 안전 버전
#else
    localtime_r(&time_t, &timeinfo);  // POSIX 시스템에서 안전 버전
#endif

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

std::string Logger::GetLevelString(LogLevel level) const {
    switch (level) {
    case LogLevel::DEBUG_LEVEL: return "DEBUG";
    case LogLevel::INFO_LEVEL: return "INFO";
    case LogLevel::WARNING_LEVEL: return "WARN";
    case LogLevel::ERROR_LEVEL: return "ERROR";
    default: return "UNKNOWN";
    }
}