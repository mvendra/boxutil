
#ifndef __exceptionbase_h__
#define __exceptionbase_h__ 

#define RAISE_EXCEPT(CLASS,MSG) throw CLASS(MSG, __FUNCTION__, __LINE__);

#include <stddef.h>

#include "exceptionbase.h"
#include "types.h"

class ExceptionBase { 

public:

	ExceptionBase(const ExceptionBase &other);
	ExceptionBase(const char8 *msg, const char8 *func, uint32 line);
	const char *GetMessage() const;
	const char *GetFunction() const;
	uint32 GetLine() const;
	virtual ~ExceptionBase();

protected:

	char *m_message;
	char *m_function;
	uint32 m_line;

private:

	void SetMsg(const char8 *newmsg);
	void SetFunc(const char8 *newfunc);
	void SetLine(uint32 line);

	void operator=(const ExceptionBase &other); // forbidden attrib op
	ExceptionBase(); // forbidding unparametrised constructor
	void *operator new(size_t size); // forbidding heap allocation

};

#endif // __exceptionbase_h__

