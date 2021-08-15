
#ifndef __BOXUTIL_TRACEUTIL_H__
#define __BOXUTIL_TRACEUTIL_H__

#include <cstdio>
#include <string.h>

#ifdef _WIN32
#define HELPER_FUNC __FUNCSIG__
#else
#define HELPER_FUNC __PRETTY_FUNCTION__
#endif

#define FUNCLINE HELPER_FUNC, __LINE__

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define PRINT_BREAKPOINT std::printf("%s:%d (%s): boxutil breakpoint\n", __FILENAME__, __LINE__, __FUNCTION__);
#define PRINT_BREAKPOINT_STR(VAR) std::printf("%s:%d (%s): boxutil breakpoint: [%s == \"%s\"]\n", __FILENAME__, __LINE__, __FUNCTION__, #VAR, VAR);
#define PRINT_BREAKPOINT_INT(VAR) std::printf("%s:%d (%s): boxutil breakpoint: [%s == %d]\n", __FILENAME__, __LINE__, __FUNCTION__, #VAR, VAR);
#define PRINT_BREAKPOINT_MSG(msg, ...) std::printf("%s:%d (%s): boxutil breakpoint: [" # msg, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__); std::printf("]\n");

#endif
