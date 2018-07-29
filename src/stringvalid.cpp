
#include "stringvalid.h"

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

