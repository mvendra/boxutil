
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

unsigned int test_bytearray(){

    unsigned int r {0};

    byte testinput[9] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    ByteArray bar(testinput, sizeof(testinput));

    ByteArray bar2;
    bar2 = bar;

    testforecho::test_eq(r, "ByteArray: Should match", bar.GetHexString(), bar2.GetHexString());
    testforecho::test_eq(r, "ByeArray: Size must be 9", bar.GetLength(), 9);
    testforecho::test_eq(r, "ByeArray: Size must not have changed", bar2.GetLength(), 9);
    testforecho::test_false(r, "ByteArray: Must not have changed", bar2.EraseSection(10, 1));
    testforecho::test_true(r, "ByteArray: Must have changed", bar2.EraseSection(0, 1));
    testforecho::test_eq(r, "ByteArray: Size must be 8", bar2.GetLength(), 8);

    byte p0 = 112;
    byte p1;
    bar2.Append(&p0, 1);
    testforecho::test_false(r, "ByeArray: Should not be able to get last byte", bar.GetByte(9, p1));
    testforecho::test_true(r, "ByeArray: Should be able to get last byte", bar2.GetByte(8, p1));
    testforecho::test_eq(r, "ByeArray: Last byte should be 112", p1, 112);
    ByteArray bar3;
    testforecho::test_true(r, "ByeArray: Should be able to get section", bar2.GetSection(0, 3, bar3));
    testforecho::test_eq(r, "ByeArray: Hex strings should match", bar3.GetHexString(), "223344");

    return r;

}

unsigned int test_bfl(){
    
    unsigned int r {0};
    
    StrVecCont svcTest;
    BuildFileList("../../testprops/folder", "txt", svcTest);

    testforecho::test_eq(r, "BuildFileList: Size should be 3", svcTest.Size(), 3);

    testforecho::test_true(r, "BuildFileList: Should have element", (svcTest.HasElement("one.txt")));
    testforecho::test_true(r, "BuildFileList: Should have element", (svcTest.HasElement("two.txt")));
    testforecho::test_true(r, "BuildFileList: Should have element", (svcTest.HasElement("three.txt")));

    return r;
    
}

unsigned int test_strveccont(){

    unsigned int r {0};
    
    StrVecCont v1, v2;
    v1.PushBack("first");
    v1.PushBack("second");

    v2.PushBack("neither");

    testforecho::test_false(r, "StrVecCont: Should not match", (v1 == v2));

    v2.Clear();
    v2.PushBack("first");
    v2.PushBack("second");

    testforecho::test_true(r, "StrVecCont: Should match", (v1 == v2));

    return r;

}

unsigned int test_logger(){

    // mvtodo: requires file caps (read and autodelete) for tests

    unsigned int r {0};
    Logger logger("./debug.txt");
    logger.LogInfo("test for echo");
    return r;

}

unsigned int test_crop_goodinput(){

    unsigned int r {0};
    
    std::string strTeste = "jajaja*mvresult*jejeje";

    /*try {
        std::string strResult = GetStringMidByBoundingChars(strTeste, '*');
        printresult(strResult);
    } catch (const ExceptionBase &sme){
        std::cout << "bugged..." << std::endl;
    }*/

    return r;

}

unsigned int test_crop_badinput(){

    unsigned int r {0};
    
    std::string strTeste = "idontcare";

    /*try {
        std::string strResult = GetStringMidByBoundingChars(strTeste, '!');
        printresult(strResult);
    } catch (const StringManipException &sme){
        std::cout << "bugged, derived" << std::endl;
    } catch (const ExceptionBase &eb){
        std::cout << "bugged, base" << std::endl;
    }*/

    return r;

}

unsigned int test_crop_badinput2(){

    unsigned int r {0};
    
    std::string strTeste = "three@arrobas@see@now";

    /*try {
        std::string strResult = GetStringMidByBoundingChars(strTeste, '@');
        printresult(strResult);
    } catch (const ExceptionBase &sme){
        std::cout << "bugged..." << std::endl;
    }*/

    return r;

}


int main(int argc, char *argv[]){

    (void)argc; (void)argv;

    unsigned int r {0};

    r += test_timestamp();
    r += test_bytearray();
    r += test_bfl();
    r += test_strveccont();
    //r += test_logger();
    r += test_crop_goodinput();
    r += test_crop_badinput();
    r += test_crop_badinput2();

    if (r > 0){
        std::cout << r << " tests failed." << std::endl;
    } else {
        std::cout << "All tests passed." << std::endl;
    }

    return 0;

}
