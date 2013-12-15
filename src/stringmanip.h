
#ifndef __stringmanip_h__
#define __stringmanip_h__

#include "strveccont.h"
#include "exceptionbase.h"

#include <string>
#include <vector>

uint32 CountCharsInString(const std::string &strTarget, uchar8 chChar);
std::string GetStringMidByBoundingChars(const std::string &strTarget, uchar8 chBound);
std::string TxtStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize);
std::string HexStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize);

std::string PopExtension(const std::string &strFilename);
std::string GetExtension(const std::string &strFilename);
bool FileExists(const std::string &strFileName);

void BuildFileList(const std::string &strPath, const std::string &strInputExt, StrVecCont &svcFilelist);

bool DirExists(const std::string &strDirName);
bool HasWritePermission(const std::string &strDirName);
bool HasReadPermission(const std::string &strDirName);

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill );
sint32 DecStrToInteger(const std::string &strSource);
std::string IntegerToDecStr( sint32 i );
sint32 HexStrToInteger(const std::string &strSource);

void MakeUppercase(std::string &strTarget);
void MakeLowercase(std::string &strTarget);
sint32 CompareNoCase(const std::string &strLeft, const std::string &strRight);
bool EqualsNoCase(const std::string &strLeft, const std::string &strRight);
bool ContainsNoCase(const std::string &strTarget, const std::string &strContent);
bool IsNumericString(const std::string &strElement);

#endif // __stringmanip_h__

