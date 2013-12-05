
#ifndef __stringmanip_h__
#define __stringmanip_h__

#include "strveccont.h"
#include "exceptionbase.h"

#include <string>
#include <vector>

uint32 CountCharsInString(const std::string &_strTarget, uchar8 _chChar);
std::string GetStringMidByBoundingChars(const std::string &_strTarget, uchar8 _chBound);
std::string TxtStrFromBuffer(pcbyte _pcbBuffer, const uint32 _iBuffSize);
std::string HexStrFromBuffer(pcbyte _pcbBuffer, const uint32 _iBuffSize);

std::string PopExtension(const std::string &_strFilename);
std::string GetExtension(const std::string &_strFilename);
bool FileExists(const std::string &_strFileName);

void BuildFileList(const std::string &_strPath, const std::string &_strInputExt, StrVecCont &_svcFilelist);

bool DirExists(const std::string &_strDirName);
bool HasWritePermission(const std::string &_strDirName);
bool HasReadPermission(const std::string &_strDirName);

template< typename T >
std::string NumberToHexStr( T _i, bool _bAutoFill );
sint32 DecStrToInteger(const std::string &_strSource);
std::string IntegerToDecStr( sint32 _i );
sint32 HexStrToInteger(const std::string &_strSource);

void MakeUppercase(std::string &_strTarget);
void MakeLowercase(std::string &_strTarget);
sint32 CompareNoCase(const std::string &_strLeft, const std::string &_strRight);
bool EqualsNoCase(const std::string &_strLeft, const std::string &_strRight);
bool ContainsNoCase(const std::string &_strTarget, const std::string &_strContent);
bool IsNumericString(const std::string &_strElement);

#endif // __stringmanip_h__

