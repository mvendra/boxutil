
#ifndef __BOXUTIL_STRINGMANIP_H__
#define __BOXUTIL_STRINGMANIP_H__

#include "types.h"

#include <string>
#include <vector>

namespace boxutil {

sint32 custom_strncpy_s(pchar8 dest, size_t dest_s, pcchar8 src, size_t src_s);

std::string GetNext(std::string &source, const std::string &delim = " ");
uint32 CountCharsInString(const std::string &strTarget, uchar8 chChar);
bool GetStringMidByBoundingChars(const std::string &strTarget, uchar8 chBound, std::string &strOutput);
std::string TxtStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize);
std::string HexStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize);

std::string PopExtension(const std::string &strFilename);
std::string GetExtension(const std::string &strFilename);

std::string MakeUppercase(const std::string &strTarget);
std::string MakeLowercase(const std::string &strTarget);
sint32 CompareNoCase(const std::string &strLeft, const std::string &strRight);
bool EqualsNoCase(const std::string &strLeft, const std::string &strRight);
bool ContainsNoCase(const std::string &strTarget, const std::string &strContent);
bool IsNumericString(const std::string &strElement);

bool IsAlpha(const std::string &strValue);
bool IsAlphaExt(const std::string &strValue);
bool IsBCD(const std::string &strValue);
bool IsHexStr(const std::string &strValue);
bool IsWithinBounds(const std::string &strValue, const uint32 min, const uint32 max);

void HexDump(const std::vector<unsigned char> &_buffer);

std::string RemoveComment(const std::string &_cmd, const std::string _cc);
std::string LTrim(const std::string &source);
std::string RTrim(const std::string &source);
std::string Trim(const std::string &source);

} // ns: boxutil

#endif // __BOXUTIL_STRINGMANIP_H__
