
#ifndef __stringvalid_h__
#define __stringvalid_h__

#include <string>
#include "types.h"

bool IsAlpha(const std::string &strValue);
bool IsAlphaExt(const std::string &strValue);
bool IsBCD(const std::string &strValue);
bool IsHexStr(const std::string &strValue);
bool IsWithinBounds(const std::string &strValue, const uint32 min, const uint32 max);

#endif // __stringvalid_h__

