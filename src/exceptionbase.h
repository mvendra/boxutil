
#ifndef __BOXUTIL_EXCEPTIONBASE_H__
#define __BOXUTIL_EXCEPTIONBASE_H__ 

#include "traceutil.h"

#define EX_RAISE(CLASS, MSG) throw CLASS(MSG, FUNCLINE);
#define NOTREACHED EX_RAISE(ExceptionBase, "Should not get here")

#include <stddef.h>

namespace boxutil {

class ExceptionBase { 

public:

    ExceptionBase(const ExceptionBase &other);
    ExceptionBase(const ExceptionBase &&other);
    ExceptionBase(const char *msg, const char *func, unsigned int line);
    const char *GetMessage() const;
    const char *GetFunction() const;
    unsigned int GetLine() const;
    virtual ~ExceptionBase();

    void operator=(const ExceptionBase &other) = delete;
    void operator=(const ExceptionBase &&other) = delete;
    ExceptionBase() = delete;
    void *operator new(size_t size) = delete;

protected:

    char *m_message;
    char *m_function;
    unsigned int m_line;

private:

    void SetMsg(const char *newmsg);
    void SetFunc(const char *newfunc);
    void SetLine(unsigned int line);

};

} // ns: boxutil

#endif // __BOXUTIL_EXCEPTIONBASE_H__
