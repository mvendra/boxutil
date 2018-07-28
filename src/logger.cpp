
#include "logger.h"
#include "sysutil.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>

Logger::Logger(pcchar8 pszFilename):m_pszFilename(nullptr){
    size_t thesize = strlen(pszFilename);
    this->m_pszFilename = static_cast<pchar8>(calloc(thesize+1, sizeof(char8)));
    strncpy(this->m_pszFilename, pszFilename, thesize);
}

Logger::~Logger(){
    free(m_pszFilename);
}

void Logger::LogDebug(pcchar8 pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("DEBUG", pszMessage);
}

void Logger::LogInfo(pcchar8 pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("INFO", pszMessage);
}

void Logger::LogWarning(pcchar8 pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("WARNING", pszMessage);
}

void Logger::LogError(pcchar8 pszMessage){
    if (pszMessage == nullptr) return;
    LogCustom("ERROR", pszMessage);
}

void Logger::LogCustom(pcchar8 pszId, pcchar8 pszMessage){

    if (pszId == nullptr) return;
    if (pszMessage == nullptr) return;

    pchar8 pszTSBuff;
    GetTimeStampString(&pszTSBuff);

    size_t idlen = strlen(pszId);
    size_t msglen = strlen(pszMessage);
    size_t tslen = strlen(pszTSBuff);
    
    size_t extralen = 6;
    size_t total_len = idlen + msglen + tslen + extralen;

    pchar8 msgbuffer = static_cast<pchar8>(calloc(total_len+1,sizeof(char8)));

    strncpy(msgbuffer, "[", 1);
    strncpy(msgbuffer+1, pszId, idlen);
    strncpy(msgbuffer+(1+idlen), "] ", 2);
    strncpy(msgbuffer+(idlen+3), pszTSBuff, tslen);
    strncpy(msgbuffer+(3+idlen+tslen), ": ", 2);
    strncpy(msgbuffer+(idlen+5+tslen), pszMessage, msglen);
    strncpy(msgbuffer+(idlen+5+msglen+tslen), "\n", 1);

    Log(msgbuffer, total_len);

    free(msgbuffer);
    free(pszTSBuff);

}

void Logger::Log(pcchar8 pszMessage, uint32 pszMsgLen){

    FILE *fp = fopen(this->m_pszFilename, "a");
    if (fp != nullptr){
        fwrite(pszMessage, sizeof(char8), pszMsgLen, fp);
        fclose(fp);
    } 

}
