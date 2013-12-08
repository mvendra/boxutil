
#include "logger.h"
#include "sysutil.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>

Logger::Logger(const char *_pszFilename):pszFilename(NULL){
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
    if (_pszMessage == NULL) return;
    LogCustom("DEBUG", _pszMessage);
}

void Logger::LogInfo(const char *_pszMessage){
    if (_pszMessage == NULL) return;
    LogCustom("INFO", _pszMessage);
}

void Logger::LogWarning(const char *_pszMessage){
    if (_pszMessage == NULL) return;
    LogCustom("WARNING", _pszMessage);
}

void Logger::LogError(const char *_pszMessage){
    if (_pszMessage == NULL) return;
    LogCustom("ERROR", _pszMessage);
}

void Logger::LogCustom(const char *_pszId, const char *_pszMessage){

    if (_pszId == NULL) return;
    if (_pszMessage == NULL) return;

    char *pszTSBuff;
    GetTimeStampString(&pszTSBuff);

    size_t idlen = strlen(_pszId);
    size_t msglen = strlen(_pszMessage);
    size_t tslen = strlen(pszTSBuff);
    
    size_t extralen = 6;
    size_t total_len = idlen + msglen + tslen + extralen;

    char *msgbuffer = static_cast<char*>(calloc(total_len+1,sizeof(char)));

    strncpy(msgbuffer, "[", 1);
    strncpy(msgbuffer+1, _pszId, idlen);
    strncpy(msgbuffer+(1+idlen), "] ", 2);
    strncpy(msgbuffer+(idlen+3), pszTSBuff, tslen);
    strncpy(msgbuffer+(3+idlen+tslen), ": ", 2);
    strncpy(msgbuffer+(idlen+5+tslen), _pszMessage, msglen);
    strncpy(msgbuffer+(idlen+5+msglen+tslen), "\n", 1);
    
    FILE *fp = fopen(this->pszFilename, "a");
    if (fp != NULL){
        fwrite(msgbuffer, sizeof(char), total_len, fp);
    } else {
        goto cppfinally;
    }
    fclose(fp);
   
cppfinally:
    free(msgbuffer);
    free(pszTSBuff);
    return;
}
