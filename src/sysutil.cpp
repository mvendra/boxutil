
#include "sysutil.h"
#include "stringmanip.h"
#include "managedbuffer.h"
#include "exceptionbase.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#elif _WIN32
#include <windows.h>
#endif

namespace boxutil {

Platform GetPlatform(){
    #ifdef __linux__
        return Platform::Linux;
    #elif _WIN32
        return Platform::Win32;
    #elif _WIN64
        return Platform::Win64;
    #else
        #error "Unsupported Platform"
    #endif
}

SysTime::SysTime():
m_box_seconds{0}, m_box_minutes{0}, m_box_hours{0},
m_box_monthday{0}, m_box_month{0}, m_box_year{0}
{
}

SysTime::SysTime(const SysTime &other):
m_box_seconds{0}, m_box_minutes{0}, m_box_hours{0},
m_box_monthday{0}, m_box_month{0}, m_box_year{0}
{
    Copy(other);
}

SysTime::~SysTime(){

}

SysTime::SysTime(const SysTime &&other):
m_box_seconds{0}, m_box_minutes{0}, m_box_hours{0},
m_box_monthday{0}, m_box_month{0}, m_box_year{0}
{
    Copy(other);
}

SysTime &SysTime::operator= (const SysTime &other){
    if (this == &other) return *this;
    Copy(other);
    return *this;
}

bool SysTime::operator== (const SysTime &other){
    if (this->m_box_seconds == other.m_box_seconds &&
        this->m_box_minutes == other.m_box_minutes &&
        this->m_box_hours == other.m_box_hours &&
        this->m_box_monthday == other.m_box_monthday &&
        this->m_box_month == other.m_box_month &&
        this->m_box_year == other.m_box_year)
    {
        return true;
    }
    return false;
}

std::string SysTime::ToString(){
    char chAux[32] = {0}; // sample: "19:48:31 - 01/12/2013"
    box_snprintf(chAux, 32, "%02d:%02d:%02d - %02d/%02d/%04d", m_box_hours, m_box_minutes, m_box_seconds, m_box_monthday, m_box_month, m_box_year);
    return chAux;
}

void SysTime::Copy(const SysTime &other){
    this->m_box_seconds = other.m_box_seconds;
    this->m_box_minutes = other.m_box_minutes;
    this->m_box_hours = other.m_box_hours;
    this->m_box_monthday = other.m_box_monthday;
    this->m_box_month = other.m_box_month;
    this->m_box_year = other.m_box_year;
}

SysTime GetSystemTime(){

    SysTime sysTime;

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    sysTime.m_box_seconds = tm->tm_sec;
    sysTime.m_box_minutes = tm->tm_min;
    sysTime.m_box_hours = tm->tm_hour;
    sysTime.m_box_monthday = tm->tm_mday;
    sysTime.m_box_month = tm->tm_mon+1;
    sysTime.m_box_year = tm->tm_year%100;

#elif _WIN32
    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);

    sysTime.m_box_seconds = stSysTime.wSecond;
    sysTime.m_box_minutes = stSysTime.wMinute;
    sysTime.m_box_hours = stSysTime.wHour;
    sysTime.m_box_monthday = stSysTime.wDay;
    sysTime.m_box_month = stSysTime.wMonth;
    sysTime.m_box_year = stSysTime.wYear;

#else
    #error "Not implemented for this platform."
#endif

    return sysTime;

}

#ifdef _WIN32
bool FileExists(const std::string &strFileName) {

    bool bRet = false;
    FILE * fp = nullptr;
    errno_t r = fopen_s(&fp, strFileName.c_str(), "r+");
    if (r == 0) {
        bRet = true;
        fclose(fp);
    }
    return bRet;

}
#else
bool FileExists(const std::string &strFileName){

    bool bRet = false;
    FILE * fp = fopen(strFileName.c_str(), "r+");
    if (fp){
        bRet = true;
        fclose(fp);
    }
    return bRet;

}
#endif

bool FileDelete(const std::string &fn){
#ifdef _WIN32
    std::string stemp = std::string(fn.begin(), fn.end());
    BOOL r = DeleteFile(stemp.c_str());
    if (r == 0) {
        int v = GetLastError();
    }
    return r;
#else
    return !(std::remove(fn.c_str()));
#endif
}

bool FileSize(const std::string &strFileName, unsigned int &filesize){

    std::ifstream file;
    file.open(strFileName.c_str());
    if (!file.is_open()){
        return false;
    }

    file.seekg (0, file.end);
    filesize = file.tellg();
    file.seekg (0, file.beg);

    return true;
}

bool GetFileContents(const std::string &strFileName, std::string &contents){

    std::ifstream file;
    file.open(strFileName.c_str());
    if (!file.is_open()){
        return false;
    }

    unsigned int fs;
    if (!FileSize(strFileName, fs)) return false;
    ManagedBuffer<char> mb { fs+1 };
    std::memset(mb.buffer, 0x00, mb.length);
    file.read(mb.buffer, mb.length);
    contents = mb.buffer;

    return true;
}

bool SaveFileContents(const std::string &strFileName, const std::string &strContents){

    std::ofstream file;
    file.open(strFileName.c_str(), std::ios_base::out);
    if (!file.is_open()){
        return false;
    }
    file << strContents;

    return true;
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
    EX_RAISE(ExceptionBase, "This function is unimplemented for Windows")
    return false; // unimplemented on windows
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

bool GetAppWorkingDir(std::string &output){

#ifdef __linux__
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        output = cwd;
        return true;
    } else {
        return false;
    }
#elif _WIN32
    ManagedBuffer<CHAR> mb{2048};
    memset(mb.buffer, 0x00, 2048);
    if (GetCurrentDirectory(2048, mb.buffer) > 0) {
        output = mb.buffer;
        return true;
    } else {
        return false;
    }
#else
    #error "Working directory detection not implemented on this platform"
#endif

    NOTREACHED

}

std::string GetSysTmpDir() {
#ifdef _WIN32
    return "C:\\tmp\\";
#else
    return "/tmp/";
#endif
}

std::string GetUserHomeFolder(){

    char *homedir = nullptr;

#if defined(_WIN64) || defined(_WIN32)
    size_t sz{ 0 };
    if (_dupenv_s(&homedir, &sz, "USERPROFILE") == 0 && homedir != nullptr){
        std::string ret = homedir;
        free(homedir);
        return ret;
    } else {
        return "";
    }
#else 
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    return homedir;
#endif

    return "";

}

void GetTimeStampString(char **pstrBuf){
    SysTime sysTime = GetSystemTime();
    *pstrBuf = static_cast<char *>(calloc(22, sizeof(char)));
    std::string sysTimeStr = sysTime.ToString();
    custom_strncpy_s(*pstrBuf, 22, sysTimeStr.c_str(), sysTimeStr.size());
}

void GetTimeStampString(std::string &strTimestamp){
    SysTime sysTime = GetSystemTime();
    strTimestamp = sysTime.ToString();
}

} // ns: boxutil
