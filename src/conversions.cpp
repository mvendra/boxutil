
#include "conversions.h"

#include "stringmanip.h"

#include <sstream>
#include <iomanip>
#include <cmath>

namespace boxutil {

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill){
    std::stringstream stream;
    bool flipsign = false;
    if (i < 0){
        flipsign = true;
        i = std::fabs(i);
    }
    if (bAutoFill)
        stream << std::setfill('0') << std::setw(std::fabs(i) > 0xFF ? 4 : 2) << std::hex << i;
    else
        stream << std::hex << i;
    std::string tmp = stream.str();
    tmp = MakeUppercase(tmp);
    if (flipsign){
        tmp = "-" + tmp;
    }
    return tmp;
}

template< typename T >
T HexStrToNumber(const std::string &strSource){
    int ret;
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

int DecStrToInt(const std::string &strSource){
    return DecStrToNumber<int>(strSource);
}

unsigned int DecStrToUint(const std::string &strSource){
    return DecStrToNumber<unsigned int>(strSource);
}

std::string IntToDecStr( int i ){
    return NumberToDecStr<int>(i);
}

std::string UintToDecStr( unsigned int i ){
    return NumberToDecStr<unsigned int>(i);
}

short DecStrToShort(const std::string &strSource){
    return DecStrToNumber<short>(strSource);
}

unsigned short DecStrToUshort(const std::string &strSource){
    return DecStrToNumber<unsigned short>(strSource);
}

std::string ShortToDecStr(short i){
    return NumberToDecStr<short>(i);
}

std::string UshortToDecStr(unsigned short i){
    return NumberToDecStr<unsigned short>(i);
}

float DecStrToFloat(const std::string &strSource){
    return DecStrToNumber<float>(strSource);
}

std::string FloatToDecStr(float i){
    return NumberToDecStr<float>(i);
}

double DecStrToDouble(const std::string &strSource){
    return DecStrToNumber<double>(strSource);
}

std::string DoubleToDecStr(double i){
    return NumberToDecStr<double>(i);
}

int HexStrToInt(const std::string &strSource){
    return HexStrToNumber<int>(strSource);
}

unsigned int HexStrToUint(const std::string &strSource){
    return HexStrToNumber<unsigned int>(strSource);
    
}

std::string IntToHexStr( int i, bool bAutoFill){
    return NumberToHexStr<int>(i, bAutoFill);
}

std::string UintToHexStr( unsigned int i, bool bAutoFill){
    return NumberToHexStr<unsigned int>(i, bAutoFill);
}

short HexStrToShort(const std::string &strSource){
    return HexStrToNumber<short>(strSource);
}

unsigned short HexStrToUshort(const std::string &strSource){
    return HexStrToNumber<unsigned short>(strSource);
}

std::string ShortToHexStr(short i, bool bAutoFill){
    return NumberToHexStr<short>(i, bAutoFill);
}

std::string UshortToHexStr(unsigned short i, bool bAutoFill){
    return NumberToHexStr<unsigned short>(i, bAutoFill);
}

float HexStrToFloat(const std::string &strSource){
    return HexStrToNumber<float>(strSource);
}

double HexStrToDouble(const std::string &strSource){
    return HexStrToNumber<double>(strSource);
}

std::string FloatToHexStr(float i, bool bAutoFill){
    return NumberToHexStr<float>(i, bAutoFill);
}

std::string DoubleToHexStr(double i, bool bAutoFill){
    return NumberToHexStr<double>(i, bAutoFill);
}

int BytearrayFromHexString(const std::string &hs, unsigned char *buf, size_t max_buf_size){

    if (hs.size() % 2 != 0){
        return -1;
    }
    if (max_buf_size < hs.size()/2){
        return -1;
    }

    unsigned short u = 0;
    char c[3]; c[0] = 0; c[1] = 0; c[2] = 0;
    for (size_t i=0; i<hs.size(); i += 2){
        c[0] = hs[i]; c[1] = hs[i+1];
        buf[u++] = HexStrToInt(c);
    }
    return (hs.size()/2);

}

} // ns: boxutil
