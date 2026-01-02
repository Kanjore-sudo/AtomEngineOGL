#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <fstream>

class Logger {
private:
    static std::ofstream logFile;
public:
    enum Level { INFO, WARN, ERROR };

    static void Log(Level level, const std::string& message);
    static void SetLogFile(const std::string& filename);
};

#endif
