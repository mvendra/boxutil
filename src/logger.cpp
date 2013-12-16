
#include "logger.h"
#include "sysutil.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>

Logger::Logger(pcchar8 pszFilename):m_pszFilename(NULL){
    size_t thesize = strlen(pszFilename);
    this->m_pszFilename = static_cast<pchar8>(calloc(thesize+1, sizeof(char8)));
    strncpy(this->m_pszFilename, pszFilename, thesize);
}

Logger::~Logger(){
    if (m_pszFilename){
        free(m_pszFilename);
    }
}

Logger::Logger(const Logger &other){
    // private
}

void Logger::operator= (const Logger &other){
    // private
}

void Logger::LogDebug(pcchar8 pszMessage){
    if (pszMessage == NULL) return;
    LogCustom("DEBUG", pszMessage);
}

void Logger::LogInfo(pcchar8 pszMessage){
    if (pszMessage == NULL) return;
    LogCustom("INFO", pszMessage);
}

void Logger::LogWarning(pcchar8 pszMessage){
    if (pszMessage == NULL) return;
    LogCustom("WARNING", pszMessage);
}

void Logger::LogError(pcchar8 pszMessage){
    if (pszMessage == NULL) return;
    LogCustom("ERROR", pszMessage);
}

void Logger::LogCustom(pcchar8 pszId, pcchar8 pszMessage){

    if (pszId == NULL) return;
    if (pszMessage == NULL) return;

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
    
    FILE *fp = fopen(this->m_pszFilename, "a");
    if (fp != NULL){
        fwrite(msgbuffer, sizeof(char8), total_len, fp);
    } else {
        goto cppfinally;
    }
    fclose(fp);
   
cppfinally:
    free(msgbuffer);
    free(pszTSBuff);
    return;
}
