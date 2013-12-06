
#include "logger.h"

#include <cstdlib>
#include <cstring>

Logger::Logger(const char *_pszFilename):pszFilename(0){
    size_t thesize = strlen(_pszFilename);
    this->pszFilename = static_cast<char*>(calloc(thesize+1, sizeof(char)));
    strncpy(this->pszFilename, _pszFilename, thesize);
}

Logger::~Logger(){
    if (pszFilename){
        free(pszFilename);
    }
}

Logger::Logger(const Logger &other){
    // private
}

void Logger::operator= (const Logger &other){
    // private
}

void Logger::LogDebug(const char *_pszMessage){
    if (_pszMessage == 0) return;
    LogCustom("DEBUG", _pszMessage);
}

void Logger::LogInfo(const char *_pszMessage){
    if (_pszMessage == 0) return;
    LogCustom("INFO", _pszMessage);
}

void Logger::LogWarning(const char *_pszMessage){
    if (_pszMessage == 0) return;
    LogCustom("WARNING", _pszMessage);
}

void Logger::LogError(const char *_pszMessage){
    if (_pszMessage == 0) return;
    LogCustom("ERROR", _pszMessage);
}

void Logger::LogCustom(const char *_pszId, const char *_pszMessage){
    if (_pszId == 0) return;
    if (_pszMessage == 0) return;
    
}
