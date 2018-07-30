
#ifndef __exceptionbase_h__
#define __exceptionbase_h__ 

#ifdef _WIN32
#define EX_RAISE(CLASS, MSG) throw CLASS(MSG, __FUNCSIG__, __LINE__);
#else
#define EX_RAISE(CLASS, MSG) throw CLASS(MSG, __PRETTY_FUNCTION__, __LINE__);
#endif

#define NOTREACHED EX_RAISE(ExceptionBase, "Should not get here")

#include <stddef.h>

#include "exceptionbase.h"
#include "types.h"

class ExceptionBase { 

public:

    ExceptionBase(const ExceptionBase &other);
    ExceptionBase(const ExceptionBase &&other);
    ExceptionBase(const char8 *msg, const char8 *func, uint32 line);
    const char *GetMessage() const;
    const char *GetFunction() const;
    uint32 GetLine() const;
    virtual ~ExceptionBase();

    void operator=(const ExceptionBase &other) = delete;
    void operator=(const ExceptionBase &&other) = delete;
    ExceptionBase() = delete;
    void *operator new(size_t size) = delete;

protected:

    char *m_message;
    char *m_function;
    uint32 m_line;

private:

    void SetMsg(const char8 *newmsg);
    void SetFunc(const char8 *newfunc);
    void SetLine(uint32 line);

};

#endif // __exceptionbase_h__
