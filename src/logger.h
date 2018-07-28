
#ifndef __logger_h__
#define __logger_h__

#include "types.h"

class Logger {

public:
    
    explicit Logger(pcchar8 pszFilename);
    
    void LogDebug(pcchar8 pszMessage);
    void LogInfo(pcchar8 pszMessage);
    void LogWarning(pcchar8 pszMessage);
    void LogError(pcchar8 pszMessage);
    void LogCustom(pcchar8 pszId, pcchar8 pszMessage);

    virtual ~Logger();

    Logger(const Logger &other) = delete;
    void operator= (const Logger &other) = delete;

private:

    void Log(pcchar8 pszMessage, uint32 pszMsgLen);
    pchar8 m_pszFilename;
    
};

#endif // __logger_h__
