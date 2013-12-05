
#include "stringmanipexception.h"
#include "stringmanip.h"
#include <cstdio>
#include "types.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

#ifdef __linux__
#include <dirent.h>
#include <sys/stat.h>
#elif _WIN32
#include <windows.h>
#endif

uint32 CountCharsInString(const std::string &_strTarget, uchar8 _chChar){
	uint32 uiCount = 0;
	for (uint32 i=0; i<_strTarget.size(); i++){
		if (_strTarget[i] == _chChar){
			uiCount++;
		}
	}
	return uiCount;
}

std::string GetStringMidByBoundingChars(const std::string &_strTarget, uchar8 _chBound){

	if (CountCharsInString(_strTarget, _chBound) != 2){
		RAISE_EXCEPT(StringManipException, "Unable to crop string");
	}

	size_t pos1 = _strTarget.find(_chBound);
	size_t pos2 = _strTarget.find(_chBound, pos1+1);

	if (pos1 == std::string::npos || pos2 == std::string::npos){ // not found. raise hell
		RAISE_EXCEPT(StringManipException, "Unable to crop string");
	}

	std::string strRet = _strTarget.substr(pos1+1, pos2-pos1-1);
	return strRet;

}

std::string TxtStrFromBuffer(pcbyte _pcbBuffer, const uint32 _iBuffSize){
	std::string strRet = std::string(reinterpret_cast<const char *>(_pcbBuffer), _iBuffSize);
	return strRet;
}

std::string HexStrFromBuffer(pcbyte _pcbBuffer, const uint32 _iBuffSize){

	std::string strRet;
	char chAux[2] = {0};
	for (uint32 i = 0; i < _iBuffSize; i++){
		sprintf(chAux, "%02X", _pcbBuffer[i]);
		strRet += chAux;
	}
	return strRet;

}

std::string PopExtension(const std::string &_strFilename)
{

    size_t dotpos = _strFilename.rfind(".");
    std::string strExt;
    if (dotpos != std::string::npos && dotpos < _strFilename.size()-1){
        strExt = _strFilename.substr(0, dotpos);
    }
    return strExt;

}

std::string GetExtension(const std::string &_strFilename)
{

    size_t dotpos = _strFilename.rfind(".");
    std::string strExt;
    if (dotpos != std::string::npos && dotpos < _strFilename.size()-1){
        strExt = _strFilename.substr(dotpos+1);
    }
    return strExt;

}

bool FileExists(const std::string &_strFileName){

    bool bRet = false;
    FILE * fp = fopen(_strFileName.c_str(), "r+");
    if (fp){
        bRet = true;
        fclose(fp);
    }
    return bRet;
}

#if  defined(__linux__) || defined(_AIX)
void BuildFileList(const std::string &_strPath, const std::string &_strInputExt, StrVecCont &_svcFileList) {

	_svcFileList.Clear();
	DIR *dp;
   	struct dirent *dirp;
	std::string filepath;

	if((dp = opendir(_strPath.c_str())) == NULL) {
		RAISE_EXCEPT(StringManipException, "Unable to open dir for listing");
	}

	while ((dirp = readdir(dp)) != NULL) {
#ifdef __linux__
		if (dirp->d_type == DT_DIR)
			continue; // ignore folders
#else
		struct stat s;
		filepath = strPath + "/" + dirp->d_name;

		// If the file is a directory (or is in some way invalid) we'll skip it 
		if (stat( filepath.c_str(), &s )) continue;
		if (S_ISDIR( s.st_mode ))         continue;
#endif
		std::string strCurr = dirp->d_name;
		if (GetExtension(strCurr) == _strInputExt){
			_svcFileList.PushBack(strCurr);
		}
	}

	closedir(dp);

}
#endif

#ifdef _WIN32
void BuildFileList(const std::string &_strPath, const std::string &_strInputExt, StrVecCont &_svcFilelist){

	_svcFilelist.Clear();

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	DWORD dwError=0;

	std::string strPathWildcard = _strPath + "\\*";

	hFind = FindFirstFile(strPathWildcard.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind){
		RAISE_EXCEPT(StringManipException, "Unable to open dir for listing");
	}

	while (FindNextFile(hFind, &ffd) != 0){
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
			std::string strCurr = ffd.cFileName;
			if (GetExtension(strCurr) == _strInputExt){
				_svcFilelist.PushBack(strCurr);
			}
		}
	}

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		RAISE_EXCEPT(StringManipException, "Unknown error while listing dir");
	}

	FindClose(hFind);

}
#endif

#if  defined(__linux__) || defined(_AIX)
bool DirExists(const std::string &_strDirName){

    struct stat sb;
    if (stat(_strDirName.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
        return true;
    }

    return false;

}
#endif

#ifdef _WIN32
bool TSEDPPlusUtil::DirExists(const std::string &_strDirName)
{

    DWORD ftyp = GetFileAttributesA(_strDirName.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES){
	RAISE_EXCEPT(StringManipException, "Invalid path");
    }

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!

}
#endif


#if  defined(__linux__) || defined(_AIX)
bool HasWritePermission(const std::string &_strDirName){

    struct stat sb;

    if (stat(_strDirName.c_str(), &sb) != 0){
        return false;
    }

    if (sb.st_mode & S_IWUSR){
        return true;
    }

    return false;

}
#endif

#ifdef _WIN32
bool HasWritePermission(const std::string &_strDirName){
	RAISE_EXCEPT("This function is unimplemented for Windows");
	return false; // nag me not
}
#endif


#if  defined(__linux__) || defined(_AIX)
bool HasReadPermission(const std::string &_strDirName){

    struct stat sb;
    if (stat(_strDirName.c_str(), &sb) != 0){
        return false;
    }

    if (sb.st_mode & S_IRUSR){
        return true;
    }

    return false;

}
#endif

#ifdef _WIN32
bool HasReadPermission(const std::string &_strDirName)
{
    return true; // more or less safe to make such assumption for the time being.
}
#endif

template< typename T >
std::string NumberToHexStr( T _i, bool _bAutoFill )
{
    std::stringstream stream;
    if (_bAutoFill)
        stream << std::setfill('0') << std::setw((_i > 0xFF ? 4 : 2)) << std::hex << _i;
    else
        stream << std::hex << _i;
    std::string tmp = stream.str();
    MakeUppercase(tmp);
    return tmp;
}


sint32 DecStrToInteger(const std::string &_strSource){
    int ret;
    std::stringstream(_strSource) >> ret;
    return ret;
}

std::string IntegerToDecStr( sint32 _i )
{
    std::stringstream stream;
    stream << std::dec << _i;
    std::string tmp = stream.str();
    return tmp;
}

sint32 HexStrToInteger(const std::string &_strSource){
    sint32 ret;
    std::stringstream(_strSource) >> std::hex >> ret;
    return ret;
}


void MakeUppercase(std::string &_strTarget){
    std::transform(_strTarget.begin(), _strTarget.end(), _strTarget.begin(), ::toupper);
}

void MakeLowercase(std::string &_strTarget){
    std::transform(_strTarget.begin(), _strTarget.end(), _strTarget.begin(), ::tolower);
}


sint32 CompareNoCase(const std::string &_strLeft, const std::string &_strRight){
    std::string left = _strLeft;
    std::string right = _strRight;
    MakeLowercase(left);
    MakeLowercase(right);
    sint32 ret = left.compare(right);
    return ret;
}

bool EqualsNoCase(const std::string &_strLeft, const std::string &_strRight){
    if (CompareNoCase(_strLeft, _strRight) == 0)
        return true;
    else
        return false;
}

bool ContainsNoCase(const std::string &_strTarget, const std::string &_strContent){
    std::string target = _strTarget;
    std::string content = _strContent;
    MakeLowercase(target);
    MakeLowercase(content);
    size_t ret = target.find(content);
    if (ret == std::string::npos)
        return false;
    else
        return true;
}


bool IsNumericString(const std::string &_strElement) {

    std::istringstream ss(_strElement);
    sint32 num = 0;
    if(ss >> num) {
        return true;
    }
    return false;

}

