
#include "sysutil.h"
#include "stringmanip.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>
#elif _WIN32
#include <windows.h>
#endif

SysTime::SysTime():
m_seconds{0}, m_minutes{0}, m_hours{0},
m_monthday{0}, m_month{0}, m_year{0}
{
}

SysTime::SysTime(const SysTime &other):
m_seconds{0}, m_minutes{0}, m_hours{0},
m_monthday{0}, m_month{0}, m_year{0}
{
    Copy(other);
}

SysTime::~SysTime(){

}

SysTime::SysTime(const SysTime &&other):
m_seconds{0}, m_minutes{0}, m_hours{0},
m_monthday{0}, m_month{0}, m_year{0}
{
    Copy(other);
}

SysTime &SysTime::operator= (const SysTime &other){
    if (this == &other) return *this;
    Copy(other);
    return *this;
}

bool SysTime::operator== (const SysTime &other){
    if (this->m_seconds == other.m_seconds &&
        this->m_minutes == other.m_minutes &&
        this->m_hours == other.m_hours &&
        this->m_monthday == other.m_monthday &&
        this->m_month == other.m_month &&
        this->m_year == other.m_year)
    {
        return true;
    }
    return false;
}

std::string SysTime::ToString(){
    char8 chAux[22] = {0}; // sample: "19:48:31 - 01/12/2013"
    std::sprintf(chAux, "%02d:%02d:%02d - %02d/%02d/%04d", m_hours, m_minutes, m_seconds, m_monthday, m_month, m_year);
    return chAux;
}

void SysTime::Copy(const SysTime &other){
    this->m_seconds = other.m_seconds;
    this->m_minutes = other.m_minutes;
    this->m_hours = other.m_hours;
    this->m_monthday = other.m_monthday;
    this->m_month = other.m_month;
    this->m_year = other.m_year;
}

SysTime GetSystemTime(){

    SysTime sysTime;

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    sysTime.m_seconds = tm->tm_sec;
    sysTime.m_minutes = tm->tm_min;
    sysTime.m_hours = tm->tm_hour;
    sysTime.m_monthday = tm->tm_mday;
    sysTime.m_month = tm->tm_mon+1;
    sysTime.m_year = tm->tm_year%100;

#elif _WIN32
    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);

    sysTime.m_seconds = stSysTime.wSecond;
    sysTime.m_minutes = stSysTime.wMinute;
    sysTime.m_hours = stSysTime.wHour;
    sysTime.m_monthday = stSysTime.wDay;
    sysTime.m_month = stSysTime.wMonth;
    sysTime.m_year = stSysTime.wYear%100;

#else
    #error "Not implemented for this platform."
#endif

    return sysTime;

}

bool FileExists(const std::string &strFileName){

    bool bRet = false;
    FILE * fp = fopen(strFileName.c_str(), "r+");
    if (fp){
        bRet = true;
        fclose(fp);
    }
    return bRet;

}

#if defined(__linux__) || defined(_AIX)
bool BuildFileList(const std::string &strPath, const std::string &strInputExt, StrVecCont &svcFileList) {

    svcFileList.Clear();
    DIR *dp;
    struct dirent *dirp;
    std::string filepath;

    if((dp = opendir(strPath.c_str())) == nullptr) {
        return false;
    }

    while ((dirp = readdir(dp)) != nullptr) {
#ifdef __linux__
        if (dirp->d_type == DT_DIR) continue; // ignore folders
#else
        struct stat s;
        filepath = strPath + "/" + dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it 
        if (stat( filepath.c_str(), &s )) continue;
        if (S_ISDIR( s.st_mode )) continue;
#endif
        std::string strCurr = dirp->d_name;
        if (GetExtension(strCurr) == strInputExt){
            svcFileList.PushBack(strCurr);
        }
    }

    closedir(dp);
    return true;

}
#endif

#ifdef _WIN32
bool BuildFileList(const std::string &strPath, const std::string &strInputExt, StrVecCont &svcFilelist){

    svcFilelist.Clear();

    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    DWORD dwError=0;

    std::string strPathWildcard = strPath + "\\*";

    hFind = FindFirstFile(strPathWildcard.c_str(), &ffd);

    if (INVALID_HANDLE_VALUE == hFind){
        return false;
    }

    while (FindNextFile(hFind, &ffd) != 0){
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
            std::string strCurr = ffd.cFileName;
            if (GetExtension(strCurr) == strInputExt){
                svcFilelist.PushBack(strCurr);
            }
        }
    }

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) {
        return false;
    }

    FindClose(hFind);
    return true;

}
#endif

#if defined(__linux__) || defined(_AIX)
bool DirExists(const std::string &strDirName){

    struct stat sb;
    if (stat(strDirName.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }
    return false;

}
#endif

#ifdef _WIN32
bool DirExists(const std::string &strDirName, bool &answer){

    DWORD ftyp = GetFileAttributesA(strDirName.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES){
        return false; // invalid path - operation failed
    }

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
        answer = true;   // this is a directory!
    } else {
        answer = false;    // this is not a directory!
    }

    return true; // operation succeeded

}
#endif


#if defined(__linux__) || defined(_AIX)
bool HasWritePermission(const std::string &strDirName){

    struct stat sb;

    if (stat(strDirName.c_str(), &sb) != 0){
        return false;
    }
    if (sb.st_mode & S_IWUSR){
        return true;
    }

    return false;

}
#endif

#ifdef _WIN32
bool HasWritePermission(const std::string &strDirName){
    #error "This function is unimplemented for Windows";
    return false; // nag me not
}
#endif


#if defined(__linux__) || defined(_AIX)
bool HasReadPermission(const std::string &strDirName){

    struct stat sb;
    if (stat(strDirName.c_str(), &sb) != 0){
        return false;
    }

    if (sb.st_mode & S_IRUSR){
        return true;
    }

    return false;

}
#endif

#ifdef _WIN32
bool HasReadPermission(const std::string &strDirName){
    return true; // more or less safe to make such assumption for the time being.
}
#endif

void GetTimeStampString(pchar8 *pstrBuf){
    SysTime sysTime = GetSystemTime();
    *pstrBuf = static_cast<pchar8>(calloc(22, sizeof(char8)));
    std::string sysTimeStr = sysTime.ToString();
    strncpy(*pstrBuf, sysTimeStr.c_str(), sysTimeStr.size());
}

void GetTimeStampString(std::string &strTimestamp){
    SysTime sysTime = GetSystemTime();
    strTimestamp = sysTime.ToString();
}
