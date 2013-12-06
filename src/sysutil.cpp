
#include "sysutil.h"

#include "exceptionbase.h"

#ifdef __linux__
//#include <time.h>
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

SysTime::SysTime(const SysTime &other){
    copy(other);
}

SysTime::~SysTime(){

}

SysTime::operator= (const SysTime &other){
    copy(other);
}

void SysTime::copy(const SysTime &other){
    this->iSeconds = other.iSeconds;
    this->iMinutes = other.iMinutes;
    this->iHours = other.iHours;
    this->iMonthDay = other.iMonthDay;
    this->iMonth = other.iMonth;
    this->iYear = other.iYear;
}

SysTime GetSystemTime(){

    SysTime sysTime;

#ifdef __linux__

    struct timeval tv;
    struct timezone tz;
    struct tm *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

    sysTime->iSeconds = tv.tv_usec;
    sysTime->iMinutes = tm->tm_min;
    sysTime->iHours = tm->tm_hour;
    sysTime->iMonthDay = tm->tm_mday;
    sysTime->iMonth = tm->tm_mon+1;
    sysTime->iYear = tm->tm_year%100;

#elif _WIN32
#else
    RAISE_EXCEPT(ExceptionBase, "Not implemented for this platform.")
#endif

    return sysTime;

}
