
#include "sysutil.h"

#include "exceptionbase.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef __linux__
#include <time.h>
#include <sys/time.h>
#elif _WIN32
#include <windows.h>
#endif

SysTime::SysTime(){
    this->m_seconds = 0;
    this->m_minutes = 0;
    this->m_hours = 0;
    this->m_monthday = 0;
    this->m_month = 0;
    this->m_year = 0;
}

SysTime::SysTime(const SysTime &other){
    Copy(other);
}

SysTime::~SysTime(){

}

SysTime &SysTime::operator= (const SysTime &other){
    if (this == &other) return *this;
    Copy(other);
    return *this;
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
    RAISE_EXCEPT(ExceptionBase, "Not implemented for this platform.")
#endif

    return sysTime;

}

void GetTimeStampString(pchar8 *pstrBuf){

    // mvtodo: assert pstrBuf is null here

    SysTime sysTime = GetSystemTime();
    char8 chAux[22] = {0}; // sample: "19:48:31 - 01/12/2013"

    sprintf(chAux, "%02d:%02d:%02d - %02d/%02d/%04d", sysTime.m_hours, sysTime.m_minutes, sysTime.m_seconds, sysTime.m_monthday, sysTime.m_month, sysTime.m_year);
    
    *pstrBuf = static_cast<pchar8>(calloc(22, sizeof(char8)));
    strncpy(*pstrBuf, chAux, sizeof(chAux)-1);

}
