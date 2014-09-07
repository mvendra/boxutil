
#include <iostream>

#include <string>

#include "boxutil.h"

using namespace std;

void test_timestamp(){
    
    SysTime sysTime = GetSystemTime();

}

void test_logger(){

    Logger logger("./debug.txt");
    logger.LogInfo("test for echo");
    
}

void test_bytearray(){

	byte testinput[9] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
	ByteArray bar(testinput, sizeof(testinput));

    //ByteArray bar2;
    //bar2 = bar;
    bar = bar;
    
	//byte ti2[2] = {0xaa, 0xbb};
	//byte ti3[4] = {0xde, 0xad, 0xbe, 0xef};

	//uint32 testinputlen = sizeof(testinput);
	//ByteArray bar = ByteArray(testinput, testinputlen);

	//bar.Append(ByteArray(ti2, sizeof(ti2)));
	//bar.Append(ti2, sizeof(ti2));
	//ByteArray bar2(ti2, sizeof(ti2));
	//bar.Append(bar2);

	//bar.Append(ti3, sizeof(ti3));

	//ByteArray bar2 = bar.GetSection(0, 3);

	//bar.EraseSection(2, 4);
	//cout << bar.GetHexString() << endl;

}

void test_bfl(){
	StrVecCont svcTest;
	BuildFileList("./testfolders", "txt", svcTest);
	StrVecCont svc2;
	svc2 = svcTest;
	for (uint16 i = 0; i < svc2.Size(); i++){
		cout << svc2.Get(i) << endl;
	}
}

void printresult(const std::string &strMsg){
	std::cout << "Result: [" << strMsg << "]" << std::endl;
}

void test_crop_goodinput(){

	std::string strTeste = "jajaja*mvresult*jejeje";

	try {
		std::string strResult = GetStringMidByBoundingChars(strTeste, '*');
		printresult(strResult);
	} catch (const ExceptionBase &sme){
		cout << "bugged..." << endl;
	}

}


void test_crop_badinput(){

	std::string strTeste = "idontcare";

	try {
		std::string strResult = GetStringMidByBoundingChars(strTeste, '!');
		printresult(strResult);
	} catch (const StringManipException &sme){
		cout << "bugged, derived" << endl;
	} catch (const ExceptionBase &eb){
		cout << "bugged, base" << endl;
	}

}


void test_crop_badinput2(){

	std::string strTeste = "three@arrobas@see@now";

	try {
		std::string strResult = GetStringMidByBoundingChars(strTeste, '@');
		printresult(strResult);
	} catch (const ExceptionBase &sme){
		cout << "bugged..." << endl;
	}

}


int main(int argc, char *argv[]){

	//cout << "testing stringmanip..." << endl;

	test_crop_goodinput();
	//test_crop_badinput();
	//test_crop_badinput2();
	//test_bfl();
	//test_bytearray();
    //test_timestamp();
    //test_logger();

	return 0;

}

