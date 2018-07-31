
#ifndef __BOXUTIL_CONVERSIONS_H__
#define __BOXUTIL_CONVERSIONS_H__

#include <string>
#include <vector>

namespace boxutil {

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill = true );

template< typename T >
T HexStrToNumber(const std::string &strSource);

template< typename T >
std::string NumberToDecStr(T i);

template< typename T >
T DecStrToNumber(const std::string &strSource);

int DecStrToInt(const std::string &strSource);
unsigned int DecStrToUint(const std::string &strSource);
std::string IntToDecStr( int i );
std::string UintToDecStr( unsigned int i );

short DecStrToShort(const std::string &strSource);
unsigned short DecStrToUshort(const std::string &strSource);
std::string ShortToDecStr(short i);
std::string UshortToDecStr(unsigned short i);

float DecStrToFloat(const std::string &strSource);
double DecStrToDouble(const std::string &strSource);
std::string FloatToDecStr(float i);
std::string DoubleToDecStr(double i);

int HexStrToInt(const std::string &strSource);
unsigned int HexStrToUint(const std::string &strSource);
std::string IntToHexStr( int i, bool bAutoFill = true );
std::string UintToHexStr( unsigned int i, bool bAutoFill = true );

short HexStrToShort(const std::string &strSource);
unsigned short HexStrToUshort(const std::string &strSource);
std::string ShortToHexStr(short i, bool bAutoFill = true);
std::string UshortToHexStr(unsigned short i, bool bAutoFill = true);

float HexStrToFloat(const std::string &strSource);
double HexStrToDouble(const std::string &strSource);
std::string FloatToHexStr(float i, bool bAutoFill = true);
std::string DoubleToHexStr(double i, bool bAutoFill = true);

int BytearrayFromHexString(const std::string &hs, unsigned char *buf, size_t max_buf_size);

} // ns: boxutil

#endif // __BOXUTIL_CONVERSIONS_H__
