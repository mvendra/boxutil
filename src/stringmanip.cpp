
#include "stringmanip.h"
#include "types.h"

#include <iomanip>
#include <algorithm>

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
    std::string strRet = std::string(reinterpret_cast<const char *>(pcbBuffer), iBuffSize);
    return strRet;
}

std::string HexStrFromBuffer(pcbyte pcbBuffer, const uint32 iBuffSize){

    std::string strRet;
    char chAux[3] = {0};
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

void MakeUppercase(std::string &strTarget){
    std::transform(strTarget.begin(), strTarget.end(), strTarget.begin(), ::toupper);
}

void MakeLowercase(std::string &strTarget){
    std::transform(strTarget.begin(), strTarget.end(), strTarget.begin(), ::tolower);
}

sint32 CompareNoCase(const std::string &strLeft, const std::string &strRight){
    std::string left = strLeft;
    std::string right = strRight;
    MakeLowercase(left);
    MakeLowercase(right);
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
    std::string target = strTarget;
    std::string content = strContent;
    MakeLowercase(target);
    MakeLowercase(content);
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
