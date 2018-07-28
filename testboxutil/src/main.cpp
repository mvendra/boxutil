
#include <iostream>
#include <string>

#include "boxutil.h"
#include "testforecho.h"

unsigned int test_timestamp(){

    unsigned int r {0};

    std::string strts;
    GetTimeStampString(strts);
    testforecho::test_neq(r, "SysTime: Should be able to get timestamp", strts, "");

    SysTime st1 = GetSystemTime();
    SysTime st2 = st1;
    testforecho::test_eq(r, "SysTime: Timestamps should match", st1.ToString(), st2.ToString());

    return r;

}

unsigned int test_logger(){

    unsigned int r {0};
    Logger logger("./debug.txt");
    logger.LogInfo("test for echo");
    return r;

}

unsigned int test_bytearray(){

    unsigned int r {0};
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

    return r;

}

unsigned int test_bfl(){
    
    unsigned int r {0};
    
    StrVecCont svcTest;
    BuildFileList("./testfolders", "txt", svcTest);
    StrVecCont svc2;
    svc2 = svcTest;
    for (uint16 i = 0; i < svc2.Size(); i++){
        std::cout << svc2.Get(i) << std::endl;
    }
    
    return r;
    
}

void printresult(const std::string &strMsg){
    std::cout << "Result: [" << strMsg << "]" << std::endl;
}

unsigned int test_crop_goodinput(){

    unsigned int r {0};
    
    std::string strTeste = "jajaja*mvresult*jejeje";

    try {
        std::string strResult = GetStringMidByBoundingChars(strTeste, '*');
        printresult(strResult);
    } catch (const ExceptionBase &sme){
        std::cout << "bugged..." << std::endl;
    }

    return r;

}

unsigned int test_crop_badinput(){

    unsigned int r {0};
    
    std::string strTeste = "idontcare";

    try {
        std::string strResult = GetStringMidByBoundingChars(strTeste, '!');
        printresult(strResult);
    } catch (const StringManipException &sme){
        std::cout << "bugged, derived" << std::endl;
    } catch (const ExceptionBase &eb){
        std::cout << "bugged, base" << std::endl;
    }

    return r;

}

unsigned int test_crop_badinput2(){

    unsigned int r {0};
    
    std::string strTeste = "three@arrobas@see@now";

    try {
        std::string strResult = GetStringMidByBoundingChars(strTeste, '@');
        printresult(strResult);
    } catch (const ExceptionBase &sme){
        std::cout << "bugged..." << std::endl;
    }

    return r;

}


int main(int argc, char *argv[]){

    (void)argc; (void)argv;

    unsigned int r {0};

    r += test_timestamp();
    r += test_crop_goodinput();
    r += test_crop_badinput();
    r += test_crop_badinput2();
    r += test_bfl();
    r += test_bytearray();
    r += test_logger();

    if (r > 0){
        std::cout << r << " tests failed." << std::endl;
    } else {
        std::cout << "All tests passed." << std::endl;
    }

    return 0;

}
