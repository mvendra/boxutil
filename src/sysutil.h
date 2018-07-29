
#ifndef __sysutil_h__
#define __sysutil_h__

#include "types.h"
#include "strveccont.h"

#include <string>
#include <ostream>

class SysTime {
public:

    SysTime();
    SysTime(const SysTime &other);
    SysTime(const SysTime &&other);
    virtual ~SysTime();
    
    SysTime& operator= (const SysTime &other);
    SysTime& operator= (const SysTime &&other) = delete;
    bool operator== (const SysTime &other);
    std::string ToString();

    void Copy(const SysTime &other);
    
    sint32 m_seconds;
    sint32 m_minutes;
    sint32 m_hours;
    sint32 m_monthday;
    sint32 m_month;
    sint32 m_year;

};

bool FileExists(const std::string &strFileName);
bool BuildFileList(const std::string &strPath, const std::string &strInputExt, StrVecCont &svcFilelist);

bool DirExists(const std::string &strDirName, bool &answer);
bool HasWritePermission(const std::string &strDirName);
bool HasReadPermission(const std::string &strDirName);

SysTime GetSystemTime();
void GetTimeStampString(pchar8 *pstrBuf);
void GetTimeStampString(std::string &strTimestamp);

#endif // __sysutil_h__
