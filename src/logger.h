
#ifndef __logger_h__
#define __logger_h__

class Logger {

public:
    
    explicit Logger(const char *_pszFilename);
    
    void LogDebug(const char *_pszMessage);
    void LogInfo(const char *_pszMessage);
    void LogWarning(const char *_pszMessage);
    void LogError(const char *_pszMessage);
    void LogCustom(const char *_pszId, const char *_pszMessage);

    virtual ~Logger();

private:

    Logger(const Logger &other);
    void operator= (const Logger &other);
    char *pszFilename;
    
};

#endif // __logger_h__
