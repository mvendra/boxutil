
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

unsigned int test_managedbuffer(){

    unsigned int r {0};

    ManagedBuffer <char>mb {16};

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

unsigned int test_datehelper(){

    unsigned int r {0};

    testforecho::test_true(r, "Date should be valid", DateHelper::isValidDate(22, 6, 1997));
    testforecho::test_true(r, "Date should be valid", DateHelper::isValidDate(22, 6, 1997));
    testforecho::test_false(r, "Date should be invalid", DateHelper::isValidDate(32, 6, 1997));
    testforecho::test_true(r, "Date should be valid", DateHelper::isValidDate("05/08/2001"));
    testforecho::test_false(r, "Date should be invalid", DateHelper::isValidDate("05/13/1985"));
    testforecho::test_eq(r, "Conversion should succeed", "06/03/2002", DateHelper::convertFromNumbers(6, 3, 2002));

    {
        unsigned short d{0}, m{0}, y{0};
        DateHelper::convertFromText("07/02/2003", d, m, y);
        testforecho::test_eq(r, "Conversion should succeed", 7, d);
        testforecho::test_eq(r, "Conversion should succeed", 2, m);
        testforecho::test_eq(r, "Conversion should succeed", 2003, y);
    }

    {
        unsigned short d{3}, m{4}, y{2005};
        DateHelper::convertFromText("nope", d, m, y);
        testforecho::test_neq(r, "Conversion should fail", 3, d);
        testforecho::test_neq(r, "Conversion should fail", 4, m);
        testforecho::test_neq(r, "Conversion should fail", 2005, y);
    }

    {
        DateHelper dh{7, 80, 1978};
        testforecho::test_eq(r, "Should be in an invalid state", dh.getDateString(), "00/00/0000");
    }

    {
        DateHelper dh{7, 5, 1985}; 
        testforecho::test_false(r, "Should fail to set bad date", dh.setDate("35/20/2000"));
    }

    {
        const std::string templ {"03/03/1993"};
        DateHelper dh{templ};
        testforecho::test_eq(r, "Init date and later fetched date should match", templ, dh.getDateString());
    }

    {
        DateHelper dh{7, 5, 1985}; dh.setDate("35/20/2000");
        testforecho::test_eq(r, "Should be in an invalid state", dh.getDateString(), "00/00/0000");
    }

    {
        DateHelper dh{7, 5, 1985};
        testforecho::test_eq(r, "Should be in a valid state", dh.getDateString(), "07/05/1985");
    }

    {
        DateHelper dh{};
        testforecho::test_true(r, "Auto-built date should be valid", DateHelper::isValidDate(dh.getDateString()));
    }

    {
        DateHelper dh1{"01/01/2004"};
        DateHelper dh2 = dh1;
        testforecho::test_eq(r, "Should match by the attribute copy", dh1.getDateString(), dh2.getDateString());
        DateHelper dh3{dh2};
        testforecho::test_eq(r, "Should match by the copy constructor", dh2.getDateString(), dh3.getDateString());
    }

    return r;

}

unsigned int test_conversions(){

    unsigned int r {0};

    testforecho::test_eq(r, "Conversion from decstr to int should work", DecStrToInt("-21"), -21);
    testforecho::test_eq(r, "Conversion from decstr to uint should work", DecStrToUint("4294967200"), 4294967200);
    testforecho::test_eq(r, "Conversion from decstr to short should work", DecStrToShort("-250"), -250);
    testforecho::test_eq(r, "Conversion from decstr to ushort should work", DecStrToUshort("220"), 220);
    testforecho::test_true(r, "Conversion from decstr to float should work", (DecStrToFloat("32.1") > 32.09 && DecStrToFloat("32.1") < 32.11) );
    testforecho::test_true(r, "Conversion from decstr to double should work", (DecStrToDouble("500.32") > 500.31 && DecStrToDouble("500.32") < 500.33 ));

    testforecho::test_eq(r, "Conversion from int to decstr should work", IntToDecStr(-21), "-21");
    testforecho::test_eq(r, "Conversion from uint to decstr should work", UintToDecStr(4294967200), "4294967200");
    testforecho::test_eq(r, "Conversion from short to decstr should work", ShortToDecStr(-250), "-250");
    testforecho::test_eq(r, "Conversion from ushort to decstr should work", UshortToDecStr(220), "220");
    testforecho::test_eq(r, "Conversion from float to decstr should work", FloatToDecStr(32.1), "32.1");
    testforecho::test_eq(r, "Conversion from double to decstr should work", DoubleToDecStr(500.32), "500.32");

    testforecho::test_eq(r, "Conversion from hexstr to int should work", HexStrToInt("-28"), -40);
    testforecho::test_eq(r, "Conversion from hexstr to uint should work", HexStrToUint("15"), 21);
    testforecho::test_eq(r, "Conversion from hexstr to short should work", HexStrToShort("-FA"), -250);
    testforecho::test_eq(r, "Conversion from hexstr to ushort should work", HexStrToUshort("DC"), 220);
    testforecho::test_eq(r, "Conversion from hexstr to float should work", HexStrToFloat("A"), 10);
    testforecho::test_eq(r, "Conversion from hexstr to double should work", HexStrToDouble("B"), 11);

    testforecho::test_eq(r, "Conversion from int to hexstr should work", IntToHexStr(-2), "-02");
    testforecho::test_eq(r, "Conversion from uint to hexstr should work", UintToHexStr(10), "0A");
    testforecho::test_eq(r, "Conversion from short to hexstr should work", ShortToHexStr(-1), "-01");
    testforecho::test_eq(r, "Conversion from ushort to hexstr should work", UshortToHexStr(0xDC), "DC");
    testforecho::test_eq(r, "Conversion from float to hexstr should work", FloatToHexStr(32.1), "32.1");
    testforecho::test_eq(r, "Conversion from double to hexstr should work", DoubleToHexStr(500.32), "500.32");

    return r;

}

int main(int argc, char *argv[]){

    (void)argc; (void)argv;

    unsigned int r {0};

    r += test_timestamp();
    r += test_bytearray();
    r += test_bfl();
    r += test_strveccont();
    r += test_managedbuffer();
    r += test_datehelper();
    r += test_conversions();
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
