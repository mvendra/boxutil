
#ifndef __sysutil_h__
#define __sysutil_h__

#include "types.h"

class SysTime { // this is a POD. sort of.
public:

    SysTime();
    SysTime(const SysTime &other);
    virtual ~SysTime();
    
    SysTime& operator= (const SysTime &other);

    void Copy(const SysTime &other);
    
    sint32 m_seconds;
    sint32 m_minutes;
    sint32 m_hours;
    sint32 m_monthday;
    sint32 m_month;
    sint32 m_year;

};

SysTime GetSystemTime();
void GetTimeStampString(pchar8 *pstrBuf);

#endif // __sysutil_h__
