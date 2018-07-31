
#ifndef __BOXUTIL_EXCEPTIONBASE_H__
#define __BOXUTIL_EXCEPTIONBASE_H__ 

#ifdef _WIN32
#define EX_RAISE(CLASS, MSG) throw CLASS(MSG, __FUNCSIG__, __LINE__);
#else
#define EX_RAISE(CLASS, MSG) throw CLASS(MSG, __PRETTY_FUNCTION__, __LINE__);
#endif

#define NOTREACHED EX_RAISE(ExceptionBase, "Should not get here")

#include <stddef.h>

#include "exceptionbase.h"
#include "types.h"

namespace boxutil {

class ExceptionBase { 

public:

    ExceptionBase(const ExceptionBase &other);
    ExceptionBase(const ExceptionBase &&other);
    ExceptionBase(const char8 *msg, const char8 *func, uint32 line);
    pcchar8 GetMessage() const;
    pcchar8 GetFunction() const;
    uint32 GetLine() const;
    virtual ~ExceptionBase();

    void operator=(const ExceptionBase &other) = delete;
    void operator=(const ExceptionBase &&other) = delete;
    ExceptionBase() = delete;
    void *operator new(size_t size) = delete;

protected:

    pchar8 m_message;
    pchar8 m_function;
    uint32 m_line;

private:

    void SetMsg(const char8 *newmsg);
    void SetFunc(const char8 *newfunc);
    void SetLine(uint32 line);

};

} // ns: boxutil

#endif // __BOXUTIL_EXCEPTIONBASE_H__
