
#ifndef __stringvalid_h__
#define __stringvalid_h__

#include <string>
#include "types.h"

bool IsAlpha(const std::string &_strValue);
bool IsAlphaExt(const std::string &_strValue);
bool IsBCD(const std::string &_strValue);
bool IsHexStr(const std::string &_strValue);
bool IsWithinBounds(const std::string &_strValue, const uint32 _min, const uint32 _max);

#endif // __stringvalid_h__

