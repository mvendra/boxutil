
#include "conversions.h"
#include "types.h"

#include "stringmanip.h"

#include <sstream>
#include <iomanip>

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill){
    std::stringstream stream;
    bool flipsign = false;
    if (i < 0){
        flipsign = true;
        i = abs(i);
    }
    if (bAutoFill)
        stream << std::setfill('0') << std::setw(abs(i) > 0xFF ? 4 : 2) << std::hex << i;
    else
        stream << std::hex << i;
    std::string tmp = stream.str();
    MakeUppercase(tmp);
    if (flipsign){
        tmp = "-" + tmp;
    }
    return tmp;
}

template< typename T >
T HexStrToNumber(const std::string &strSource){
    sint32 ret;
    std::stringstream(strSource) >> std::hex >> ret;
    return ret;
}

template< typename T >
std::string NumberToDecStr(T i){
    std::stringstream stream;
    stream << std::dec << i;
    std::string tmp = stream.str();
    return tmp;
}

template< typename T >
T DecStrToNumber(const std::string &strSource){
    T ret;
    std::stringstream(strSource) >> ret;
    return ret;
}

sint32 DecStrToInt(const std::string &strSource){
    return DecStrToNumber<sint32>(strSource);
}

uint32 DecStrToUint(const std::string &strSource){
    return DecStrToNumber<uint32>(strSource);
}

std::string IntToDecStr( sint32 i ){
    return NumberToDecStr<sint32>(i);
}

std::string UintToDecStr( uint32 i ){
    return NumberToDecStr<uint32>(i);
}

sint16 DecStrToShort(const std::string &strSource){
    return DecStrToNumber<sint16>(strSource);
}

uint16 DecStrToUshort(const std::string &strSource){
    return DecStrToNumber<uint16>(strSource);
}

std::string ShortToDecStr(sint16 i){
    return NumberToDecStr<sint16>(i);
}

std::string UshortToDecStr(uint16 i){
    return NumberToDecStr<uint16>(i);
}

fp32 DecStrToFloat(const std::string &strSource){
    return DecStrToNumber<fp32>(strSource);
}

std::string FloatToDecStr(fp32 i){
    return NumberToDecStr<fp32>(i);
}

fp64 DecStrToDouble(const std::string &strSource){
    return DecStrToNumber<fp64>(strSource);
}

std::string DoubleToDecStr(fp64 i){
    return NumberToDecStr<fp64>(i);
}

sint32 HexStrToInt(const std::string &strSource){
    return HexStrToNumber<sint32>(strSource);
}

uint32 HexStrToUint(const std::string &strSource){
    return HexStrToNumber<uint32>(strSource);
    
}

std::string IntToHexStr( sint32 i, bool bAutoFill){
    return NumberToHexStr<sint32>(i, bAutoFill);
}

std::string UintToHexStr( uint32 i, bool bAutoFill){
    return NumberToHexStr<uint32>(i, bAutoFill);
}

sint16 HexStrToShort(const std::string &strSource){
    return HexStrToNumber<sint16>(strSource);
}

uint16 HexStrToUshort(const std::string &strSource){
    return HexStrToNumber<uint16>(strSource);
}

std::string ShortToHexStr(sint16 i, bool bAutoFill){
    return NumberToHexStr<sint16>(i, bAutoFill);
}

std::string UshortToHexStr(uint16 i, bool bAutoFill){
    return NumberToHexStr<uint16>(i, bAutoFill);
}

fp32 HexStrToFloat(const std::string &strSource){
    return HexStrToNumber<fp32>(strSource);
}

fp64 HexStrToDouble(const std::string &strSource){
    return HexStrToNumber<sint64>(strSource);
}

std::string FloatToHexStr(fp32 i, bool bAutoFill){
    return NumberToHexStr<fp32>(i, bAutoFill);
}

std::string DoubleToHexStr(fp64 i, bool bAutoFill){
    return NumberToHexStr<fp64>(i, bAutoFill);
}
