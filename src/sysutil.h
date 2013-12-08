
#ifndef __sysutil_h__
#define __sysutil_h__

class SysTime { // this is a POD. sort of.
public:

    SysTime();
    SysTime(const SysTime &_other);
    virtual ~SysTime();
    
    SysTime& operator= (const SysTime &_other);

    void copy(const SysTime &_other);
    
    int iSeconds;
    int iMinutes;
    int iHours;
    int iMonthDay;
    int iMonth;
    int iYear;

};

SysTime GetSystemTime();
void GetTimeStampString(char **_pstrBuf);

#endif // __sysutil_h__
