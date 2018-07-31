
#ifndef __BOXUTIL_SYSUTIL_H__
#define __BOXUTIL_SYSUTIL_H__

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
    
    int m_box_seconds;
    int m_box_minutes;
    int m_box_hours;
    int m_box_monthday;
    int m_box_month;
    int m_box_year;

};

bool FileExists(const std::string &strFileName);
bool FileDelete(const std::string &strFileName);
bool FileSize(const std::string &strFileName, unsigned int &filesize);
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
void GetTimeStampString(char **pstrBuf);
void GetTimeStampString(std::string &strTimestamp);

} // ns: boxutil

#endif // __BOXUTIL_SYSUTIL_H__
