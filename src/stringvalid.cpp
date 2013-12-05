
#include "stringvalid.h"

bool IsAlpha(const std::string &_strValue) {
	if (_strValue.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos){
		return false;
	} 
	return true;
}

bool IsAlphaExt(const std::string &_strValue) {
	if (_strValue.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/.- ") != std::string::npos){
		return false;
	}
	return true;
}

bool IsBCD(const std::string &_strValue) {
	if (_strValue.find_first_not_of("0123456789") != std::string::npos){
		return false;
	}
	return true;
}

bool IsHexStr(const std::string &_strValue) {
	if (_strValue.find_first_not_of("abcdefABCDEF0123456789") != std::string::npos){
		return false;
	}
	return true;
}

bool IsWithinBounds(const std::string &_strValue, const uint32 _min, const uint32 _max) {
	if (_strValue.size() < _min || _strValue.size() > _max){
		return false;
	}
	return true;
}

