
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

private:

    Logger(const Logger &other);
    void operator= (const Logger &other);
    char *pszFilename;
    
};

#endif // __logger_h__
