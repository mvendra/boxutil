
#include "conversions.h"
#include "types.h"

#include "stringmanip.h"

#include <sstream>
#include <iomanip>

template< typename T >
std::string NumberToHexStr( T i, bool bAutoFill ){
    std::stringstream stream;
    if (bAutoFill)
        stream << std::setfill('0') << std::setw((i > 0xFF ? 4 : 2)) << std::hex << i;
    else
        stream << std::hex << i;
    std::string tmp = stream.str();
    MakeUppercase(tmp);
    return tmp;
}

sint32 DecStrToInteger(const std::string &strSource){
    int ret;
    std::stringstream(strSource) >> ret;
    return ret;
}

std::string IntegerToDecStr( sint32 i ){
    std::stringstream stream;
    stream << std::dec << i;
    std::string tmp = stream.str();
    return tmp;
}

sint32 HexStrToInteger(const std::string &strSource){
    sint32 ret;
    std::stringstream(strSource) >> std::hex >> ret;
    return ret;
}
