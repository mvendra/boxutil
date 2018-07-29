
#ifndef __stringmanip_h__
#define __stringmanip_h__

#include "types.h"

#include <string>
#include <vector>

uint32 CountCharsInString(const std::string &strTarget, uchar8 chChar);
bool GetStringMidByBoundingChars(const std::string &strTarget, uchar8 chBound, std::string &strOutput);
std::string TxtStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize);
std::string HexStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize);

std::string PopExtension(const std::string &strFilename);
std::string GetExtension(const std::string &strFilename);

void MakeUppercase(std::string &strTarget);
void MakeLowercase(std::string &strTarget);
sint32 CompareNoCase(const std::string &strLeft, const std::string &strRight);
bool EqualsNoCase(const std::string &strLeft, const std::string &strRight);
bool ContainsNoCase(const std::string &strTarget, const std::string &strContent);
bool IsNumericString(const std::string &strElement);

bool IsAlpha(const std::string &strValue);
bool IsAlphaExt(const std::string &strValue);
bool IsBCD(const std::string &strValue);
bool IsHexStr(const std::string &strValue);
bool IsWithinBounds(const std::string &strValue, const uint32 min, const uint32 max);

#endif // __stringmanip_h__
