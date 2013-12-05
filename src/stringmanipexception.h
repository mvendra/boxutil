
#ifndef __stringmanipexception_h__
#define __stringmanipexception_h__

#include "exceptionbase.h"

class StringManipException : public ExceptionBase {

	public:
		StringManipException(const char8 *_msg, const char8 *_func, uint32 _line);

};

#endif // __stringmanipexception_h__

