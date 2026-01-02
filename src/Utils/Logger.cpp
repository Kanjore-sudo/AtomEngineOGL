#include "Logger.hpp"
#include <ctime>

std::ofstream Logger::logFile;

void Logger::Log(Level level, const std::string& message) {
    std::string prefix;
    switch (level) {
        case INFO: prefix = "[INFO]"; break;
        case WARN: prefix = "[WARN]"; break;
        case ERROR: prefix = "[ERROR]"; break;
    }

    std::time_t now = std::time(nullptr);
    char timeStr[20];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    std::string logMsg = std::string(timeStr) + " " + prefix + " " + message;

    std::cout << logMsg << std::endl;
    if (logFile.is_open()) {
        logFile << logMsg << std::endl;
    }
}

void Logger::SetLogFile(const std::string& filename) {
    if (logFile.is_open()) logFile.close();
    logFile.open(filename, std::ios::app);
}
