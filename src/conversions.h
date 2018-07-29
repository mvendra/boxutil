
#ifndef __conversions_h__
#define __conversions_h__

#include "types.h"

#include <string>
#include <vector>

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill );
sint32 DecStrToInteger(const std::string &strSource);
std::string IntegerToDecStr( sint32 i );
sint32 HexStrToInteger(const std::string &strSource);

#endif // __conversions_h__
