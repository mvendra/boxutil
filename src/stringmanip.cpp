
#include "stringmanip.h"
#include "types.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

namespace boxutil {

std::string GetNext(std::string &source, const std::string &delim) {

    if (source == "") {
        return "";
    }

    size_t n = source.find(delim);
    if (n == std::string::npos) {
        std::string ret = source;
        source = "";
        return ret;
    } else {
        std::string ret = source.substr(0, n);
        source = source.substr(n+1);
        return ret;
    }

}

uint32 CountCharsInString(const std::string &strTarget, uchar8 chChar){
    uint32 uiCount = 0;
    for (uint32 i=0; i<strTarget.size(); i++){
        if (strTarget[i] == chChar){
            uiCount++;
        }
    }
    return uiCount;
}

bool GetStringMidByBoundingChars(const std::string &strTarget, uchar8 chBound, std::string &strOutput){

    if (CountCharsInString(strTarget, chBound) != 2){
        return false;
    }

    size_t pos1 = strTarget.find(chBound);
    size_t pos2 = strTarget.find(chBound, pos1+1);

    if (pos1 == std::string::npos || pos2 == std::string::npos){
        return false;
    }

    strOutput = strTarget.substr(pos1+1, pos2-pos1-1);
    return true;

}

std::string TxtStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize){
    std::string strRet = std::string(reinterpret_cast<pcchar8>(pcbBuffer), iBuffSize);
    return strRet;
}

std::string HexStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize){

    std::string strRet;
    char8 chAux[3] = {0};
    for (uint32 i = 0; i < iBuffSize; i++){
        sprintf(chAux, "%02X", pcbBuffer[i]);
        strRet += chAux;
    }
    return strRet;

}

std::string PopExtension(const std::string &strFilename){

    size_t dotpos = strFilename.rfind(".");
    std::string strExt;
    if (dotpos != std::string::npos && dotpos < strFilename.size()-1){
        strExt = strFilename.substr(0, dotpos);
    }
    return strExt;

}

std::string GetExtension(const std::string &strFilename){

    size_t dotpos = strFilename.rfind(".");
    std::string strExt;
    if (dotpos != std::string::npos && dotpos < strFilename.size()-1){
        strExt = strFilename.substr(dotpos+1);
    }
    return strExt;

}

std::string MakeUppercase(const std::string &strTarget){
    std::string local = strTarget;
    std::transform(local.begin(), local.end(), local.begin(), ::toupper);
    return local;
}

std::string MakeLowercase(const std::string &strTarget){
    std::string local = strTarget;
    std::transform(local.begin(), local.end(), local.begin(), ::tolower);
    return local;
}

sint32 CompareNoCase(const std::string &strLeft, const std::string &strRight){
    std::string left = MakeLowercase(strLeft);
    std::string right = MakeLowercase(strRight);
    sint32 ret = left.compare(right);
    return ret;
}

bool EqualsNoCase(const std::string &strLeft, const std::string &strRight){
    if (CompareNoCase(strLeft, strRight) == 0)
        return true;
    else
        return false;
}

bool ContainsNoCase(const std::string &strTarget, const std::string &strContent){
    std::string target = MakeLowercase(strTarget);
    std::string content = MakeLowercase(strContent);
    size_t ret = target.find(content);
    if (ret == std::string::npos)
        return false;
    else
        return true;
}

bool IsNumericString(const std::string &strElement) {
    std::istringstream ss(strElement);
    sint32 num = 0;
    if(ss >> num) {
        return true;
    }
    return false;
}

bool IsAlpha(const std::string &strValue) {
    if (strValue.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos){
        return false;
    } 
    return true;
}

bool IsAlphaExt(const std::string &strValue) {
    if (strValue.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/.- ") != std::string::npos){
        return false;
    }
    return true;
}

bool IsBCD(const std::string &strValue) {
    if (strValue.find_first_not_of("0123456789") != std::string::npos){
        return false;
    }
    return true;
}

bool IsHexStr(const std::string &strValue) {
    if (strValue.find_first_not_of("abcdefABCDEF0123456789") != std::string::npos){
        return false;
    }
    return true;
}

bool IsWithinBounds(const std::string &strValue, const uint32 min, const uint32 max) {
    if (strValue.size() < min || strValue.size() > max){
        return false;
    }
    return true;
}

void HexDump(const std::vector<byte> &_buffer){

    std::cout << std::endl;

    size_t c = 0;
    uint32 offs = 0;
    printf("%04X   ", offs);

    for (size_t i = 0; i < _buffer.size(); i++){

        if (c == 16){
            std::cout << std::endl;
            offs += 16;
            printf("%04X   ", offs);
            c = 0;
        }

        printf("%02X ", _buffer[i]);
        c++;
    }
    std::cout << std::endl << std::endl;

}

sint32 custom_strncpy_s(pchar8 dest, size_t dest_s, pcchar8 src, size_t src_s){

#if defined(_WIN64) || defined(_WIN32)
    sint32 r = strncpy_s(dest, dest_s, src, src_s);
    return r;
#else
    pchar8 r = std::strncpy(dest, src, src_s);
    (void)r;
    (void)dest_s;
    return 0;
#endif

}

std::string RemoveComment(const std::string &_cmd, const std::string _cc){

    std::string localcmd = _cmd;
    size_t p = localcmd.find(_cc);
    if (p != std::string::npos){
        localcmd = localcmd.substr(0, p);
    }
    return localcmd;

}

std::string LTrim(const std::string &source){
    size_t n = source.find_first_not_of(' ');
    if (n == std::string::npos){
        return source;
    }
    return source.substr(n);
}

std::string RTrim(const std::string &source){
    if (source == ""){
        return "";
    }
    if (source[source.size()-1] != ' '){
        return source;
    }
    sint32 n = -1;
    for (sint32 i = source.size()-1; i!=-1; i--){
        if (source[i] != ' '){
            n = i;
            break;
        }
    }
    if (n == -1){
        return source;
    }
    return source.substr(0, n+1);
}

std::string Trim(const std::string &source){
    return LTrim(RTrim(source));
}

} // ns: boxutil
