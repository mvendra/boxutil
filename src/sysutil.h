
#ifndef __BOXUTIL_SYSUTIL_H__
#define __BOXUTIL_SYSUTIL_H__

#include "types.h"
#include "strveccont.h"

#include <string>
#include <ostream>

namespace boxutil {

enum class Platform {Linux, Win32, Win64};

Platform GetPlatform();

class SysTime final {
public:

    SysTime();
    SysTime(const SysTime &other);
    SysTime(const SysTime &&other);
    ~SysTime();
    
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
bool FileDelete(const std::string &strFileName);
bool FileSize(const std::string &strFileName, uint32 &filesize);
bool GetFileContents(const std::string &strFileName, std::string &strContents);
bool SaveFileContents(const std::string &strFileName, const std::string &strContents);

bool DirExists(const std::string &strDirName, bool &answer);
bool HasWritePermission(const std::string &strDirName);
bool HasReadPermission(const std::string &strDirName);

bool GetAppWorkingDir(std::string &output);
std::string GetSysTmpDir();
std::string GetUserHomeFolder();

bool BuildFileList(const std::string &strPath, const std::string &strInputExt, StrVecCont &svcFilelist);

SysTime GetSystemTime();
void GetTimeStampString(pchar8 *pstrBuf);
void GetTimeStampString(std::string &strTimestamp);

} // ns: boxutil

#endif // __BOXUTIL_SYSUTIL_H__
