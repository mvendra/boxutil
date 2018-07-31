
#ifndef __BOXUTIL_LOGGER_H__
#define __BOXUTIL_LOGGER_H__

namespace boxutil {

class Logger {

public:
    
    explicit Logger(const char *pszFilename);
    
    void LogDebug(const char *pszMessage);
    void LogInfo(const char *pszMessage);
    void LogWarning(const char *pszMessage);
    void LogError(const char *pszMessage);
    void LogCustom(const char *pszId, const char *pszMessage);

    virtual ~Logger();

    Logger(const Logger &other) = delete;
    Logger(const Logger &&other) = delete;
    void operator= (const Logger &other) = delete;
    void operator= (const Logger &&other) = delete;

private:

    void Log(const char *pszMessage, unsigned int pszMsgLen);
    char *m_pszFilename;
    
};

} // ns: boxutil

#endif // __BOXUTIL_LOGGER_H__
