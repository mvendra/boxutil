
#ifndef __exceptionbase_h__
#define __exceptionbase_h__ 

#define RAISE_EXCEPT(CLASS,MSG) throw CLASS(MSG, __FUNCTION__, __LINE__);

#include <stddef.h>

#include "exceptionbase.h"
#include "types.h"

class ExceptionBase { 

public:

	ExceptionBase(const ExceptionBase &_other);
	ExceptionBase(const char8 *_msg, const char8 *_func, uint32 _line);
	const char *GetMessage() const;
	const char *GetFunction() const;
	uint32 GetLine() const;
	virtual ~ExceptionBase();

protected:

	char *message;
	char *function;
	uint32 line;

private:

	void SetMsg(const char8 *_newmsg);
	void SetFunc(const char8 *_newfunc);
	void SetLine(uint32 _line);

	void operator=(const ExceptionBase &_other); // forbidden attrib op
	ExceptionBase(); // forbidding unparametrised constructor
	void *operator new(size_t _size); // forbidding heap allocation

};

#endif // __exceptionbase_h__

