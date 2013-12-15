
#ifndef __stringmanipexception_h__
#define __stringmanipexception_h__

#include "exceptionbase.h"

class StringManipException : public ExceptionBase {

public:
    StringManipException(const char8 *msg, const char8 *func, uint32 line);

};

#endif // __stringmanipexception_h__

