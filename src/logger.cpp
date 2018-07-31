
#include "logger.h"
#include "sysutil.h"
#include "stringmanip.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>

namespace boxutil {

Logger::Logger(const char *pszFilename):m_pszFilename(nullptr){
    size_t thesize = strlen(pszFilename);
    this->m_pszFilename = static_cast<char *>(calloc(thesize+1, sizeof(char)));
    custom_strncpy_s(this->m_pszFilename, thesize + 1, pszFilename, thesize);
}

Logger::~Logger(){
    free(m_pszFilename);
}

void Logger::LogDebug(const char * pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("DEBUG", pszMessage);
}

void Logger::LogInfo(const char * pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("INFO", pszMessage);
}

void Logger::LogWarning(const char * pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("WARNING", pszMessage);
}

void Logger::LogError(const char * pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("ERROR", pszMessage);
}

void Logger::LogCustom(const char * pszId, const char * pszMessage){

    if (pszId == nullptr) return;
    if (pszMessage == nullptr) return;

    char *pszTSBuff = nullptr;
    GetTimeStampString(&pszTSBuff);

    size_t idlen = strlen(pszId);
    size_t msglen = strlen(pszMessage);
    size_t tslen = strlen(pszTSBuff);
    
    size_t extralen = 6;
    size_t total_len = idlen + msglen + tslen + extralen;

    char * msgbuffer = static_cast<char *>(calloc(total_len+1,sizeof(char)));

    msgbuffer[0] = '[';
    custom_strncpy_s(msgbuffer + 1, total_len + 1, pszId, idlen);
    custom_strncpy_s(msgbuffer + (1 + idlen), total_len + 1, "] ", 2);
    custom_strncpy_s(msgbuffer + (idlen + 3), total_len + 1, pszTSBuff, tslen);
    custom_strncpy_s(msgbuffer + (3 + idlen + tslen), total_len + 1, ": ", 2);
    custom_strncpy_s(msgbuffer + (idlen + 5 + tslen), total_len + 1, pszMessage, msglen);
    custom_strncpy_s(msgbuffer + (idlen + 5 + msglen + tslen), total_len + 1, "\n", 1);

    Log(msgbuffer, total_len);

    free(msgbuffer);
    free(pszTSBuff);

}

#ifdef _WIN32
void Logger::Log(const char * pszMessage, unsigned int pszMsgLen){

    FILE *fp = nullptr;
    errno_t r = fopen_s(&fp, this->m_pszFilename, "a");
    if (r == 0){
        fwrite(pszMessage, sizeof(char), pszMsgLen, fp);
        fclose(fp);
    } 

}
#else
void Logger::Log(const char * pszMessage, unsigned int pszMsgLen) {

    FILE *fp = fopen(this->m_pszFilename, "a");
    if (fp != nullptr) {
        fwrite(pszMessage, sizeof(char), pszMsgLen, fp);
        fclose(fp);
    }

}
#endif

} // ns: boxutil
