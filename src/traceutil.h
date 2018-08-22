
#ifndef __BOXUTIL_TRACEUTIL_H__
#define __BOXUTIL_TRACEUTIL_H__

#ifdef _WIN32
#define HELPER_FUNC __FUNCSIG__
#else
#define HELPER_FUNC __PRETTY_FUNCTION__
#endif

#define FUNCLINE HELPER_FUNC, __LINE__

#endif
