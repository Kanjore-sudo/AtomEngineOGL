#include "AtomEngine.hpp"
#include "Logger.hpp"

using namespace AtomEngine;

AtomError::AtomError(const std::string& error, const char* file, int line, const char* func)
{
    std::string detailedError = "Archivo: " + std::string(file) +
                               ", Linea: " + std::to_string(line) +
                               ", Funcion: " + std::string(func) +
                               " - " + error;
    Logger::Log(Logger::ERROR, detailedError);
}
