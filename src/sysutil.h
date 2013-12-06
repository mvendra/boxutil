
#ifndef __sysutil_h__
#define __sysutil_h__

class SysTime { // this is a POD
public:

    SysTime();
    SysTime(const SysTime &other);
    virtual ~SysTime();
    
    operator= (const SysTime &other);

    void copy(const SysTime &other);
    
    int iSeconds;
    int iMinutes;
    int iHours;
    int iMonthDay;
    int iMonth;
    int iYear;

};

SysTime GetSystemTime();


#endif // __sysutil_h__
