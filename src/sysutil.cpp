
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
    this->iSeconds = 0;
    this->iMinutes = 0;
    this->iHours = 0;
    this->iMonthDay = 0;
    this->iMonth = 0;
    this->iYear = 0;
}

SysTime::SysTime(const SysTime &_other){
    copy(_other);
}

SysTime::~SysTime(){

}

SysTime &SysTime::operator= (const SysTime &_other){
    if (this == &_other) return *this;
    copy(_other);
    return *this;
}

void SysTime::copy(const SysTime &_other){
    this->iSeconds = _other.iSeconds;
    this->iMinutes = _other.iMinutes;
    this->iHours = _other.iHours;
    this->iMonthDay = _other.iMonthDay;
    this->iMonth = _other.iMonth;
    this->iYear = _other.iYear;
}

SysTime GetSystemTime(){

    SysTime sysTime;

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    sysTime.iSeconds = tm->tm_sec;
    sysTime.iMinutes = tm->tm_min;
    sysTime.iHours = tm->tm_hour;
    sysTime.iMonthDay = tm->tm_mday;
    sysTime.iMonth = tm->tm_mon+1;
    sysTime.iYear = tm->tm_year%100;

#elif _WIN32
    SYSTEMTIME stSysTime;
    GetLocalTime(&stSysTime);

    sysTime.iSeconds = stSysTime.wSecond;
    sysTime.iMinutes = stSysTime.wMinute;
    sysTime.iHours = stSysTime.wHour;
    sysTime.iMonthDay = stSysTime.wDay;
    sysTime.iMonth = stSysTime.wMonth;
    sysTime.iYear = stSysTime.wYear%100;

#else
    RAISE_EXCEPT(ExceptionBase, "Not implemented for this platform.")
#endif

    return sysTime;

}

void GetTimeStampString(char **_pstrBuf){

    // mvtodo: assert pstrBuf is null here

    SysTime sysTime = GetSystemTime();
    char chAux[22] = {0}; // sample: "19:48:31 - 01/12/2013"

    sprintf(chAux, "%02d:%02d:%02d - %02d/%02d/%04d", sysTime.iHours, sysTime.iMinutes, sysTime.iSeconds, sysTime.iMonthDay, sysTime.iMonth, sysTime.iYear);
    
    *_pstrBuf = static_cast<char*>(calloc(22, sizeof(char)));
    strncpy(*_pstrBuf, chAux, sizeof(chAux)-1);

}
