
#ifndef __BOXUTIL_STRINGMANIP_H__
#define __BOXUTIL_STRINGMANIP_H__

#include <string>
#include <vector>

namespace boxutil {

#ifdef _WIN32
#define box_snprintf _snprintf_s
#else
#define box_snprintf std::snprintf
#endif

int custom_strncpy_s(char *dest, size_t dest_s, const char *src, size_t src_s);

template<typename T>
void Split(const std::string &s, char delim, T result);
std::vector<std::string> Split(const std::string &s, char delim);
std::string GetNext(std::string &source, const std::string &delim = " ");
unsigned int CountCharsInString(const std::string &strTarget, char chChar);
bool GetStringMidByBoundingChars(const std::string &strTarget, char chBound, std::string &strOutput);
std::string TxtStrFromBuffer(const unsigned char * pcbBuffer, const unsigned int iBuffSize);
std::string HexStrFromBuffer(const unsigned char * pcbBuffer, const unsigned int iBuffSize);

std::string PopSurroundingChar(const std::string &strSource, const char leftChar, const char rightChar);
std::string PopExtension(const std::string &strFilename);
std::string GetExtension(const std::string &strFilename);

std::string MakeUppercase(const std::string &strTarget);
std::string MakeLowercase(const std::string &strTarget);
int CompareNoCase(const std::string &strLeft, const std::string &strRight);
bool EqualsNoCase(const std::string &strLeft, const std::string &strRight);
bool ContainsNoCase(const std::string &strTarget, const std::string &strContent);
bool IsNumericString(const std::string &strElement);

bool IsAlpha(const std::string &strValue);
bool IsAlphaExt(const std::string &strValue);
bool IsBCD(const std::string &strValue);
bool IsHexStr(const std::string &strValue);
bool IsWithinBounds(const std::string &strValue, const unsigned int min, const unsigned int max);

void HexDump(const std::vector<unsigned char> &_buffer);

std::string RemoveComment(const std::string &_cmd, const std::string _cc);
std::string LTrim(const std::string &source);
std::string RTrim(const std::string &source);
std::string Trim(const std::string &source);

} // ns: boxutil

#endif // __BOXUTIL_STRINGMANIP_H__
