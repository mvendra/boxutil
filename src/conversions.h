
#ifndef __conversions_h__
#define __conversions_h__

#include "types.h"

#include <string>
#include <vector>

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill = true );

template< typename T >
T HexStrToNumber(const std::string &strSource);

template< typename T >
std::string NumberToDecStr(T i);

template< typename T >
T DecStrToNumber(const std::string &strSource);

sint32 DecStrToInt(const std::string &strSource);
uint32 DecStrToUint(const std::string &strSource);
std::string IntToDecStr( sint32 i );
std::string UintToDecStr( uint32 i );

sint16 DecStrToShort(const std::string &strSource);
uint16 DecStrToUshort(const std::string &strSource);
std::string ShortToDecStr(sint16 i);
std::string UshortToDecStr(uint16 i);

fp32 DecStrToFloat(const std::string &strSource);
fp64 DecStrToDouble(const std::string &strSource);
std::string FloatToDecStr(fp32 i);
std::string DoubleToDecStr(fp64 i);

sint32 HexStrToInt(const std::string &strSource);
uint32 HexStrToUint(const std::string &strSource);
std::string IntToHexStr( sint32 i, bool bAutoFill = true );
std::string UintToHexStr( uint32 i, bool bAutoFill = true );

sint16 HexStrToShort(const std::string &strSource);
uint16 HexStrToUshort(const std::string &strSource);
std::string ShortToHexStr(sint16 i, bool bAutoFill = true);
std::string UshortToHexStr(uint16 i, bool bAutoFill = true);

fp32 HexStrToFloat(const std::string &strSource);
fp64 HexStrToDouble(const std::string &strSource);
std::string FloatToHexStr(fp32 i, bool bAutoFill = true);
std::string DoubleToHexStr(fp64 i, bool bAutoFill = true);

sint32 BytearrayFromHexString(const std::string &hs, pbyte buf, size_t max_buf_size);

#endif // __conversions_h__
