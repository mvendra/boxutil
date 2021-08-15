
#include <iostream>
#include <string>

#include <boxutil.h>
#include <testforecho.h>

unsigned int test_timestamp(){

    unsigned int r {0};

    std::string strts;
    boxutil::GetTimeStampString(strts);
    testforecho::test_neq(r, "SysTime: Should be able to get timestamp", strts, "");

    boxutil::SysTime st1 = boxutil::GetSystemTime();
    boxutil::SysTime st2 = st1;
    testforecho::test_eq(r, "SysTime: Timestamps should match", st1.ToString(), st2.ToString());

    return r;

}

unsigned int test_bytearray(){

    unsigned int r {0};

    unsigned char testinput[9] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    boxutil::ByteArray bar(testinput, sizeof(testinput));

    boxutil::ByteArray bar2;
    bar2 = bar;

    testforecho::test_eq(r, "ByteArray: Should match", bar.GetHexString(), bar2.GetHexString());
    testforecho::test_eq(r, "ByeArray: Size must be 9", bar.GetLength(), static_cast<unsigned int>(9));
    testforecho::test_eq(r, "ByeArray: Size must not have changed", bar2.GetLength(), static_cast<unsigned int>(9));
    testforecho::test_false(r, "ByteArray: Must not have changed", bar2.EraseSection(10, 1));
    testforecho::test_true(r, "ByteArray: Must have changed", bar2.EraseSection(0, 1));
    testforecho::test_eq(r, "ByteArray: Size must be 8", bar2.GetLength(), static_cast<unsigned int>(8));

    unsigned char p0 = 112;
    unsigned char p1;
    bar2.Append(&p0, 1);
    testforecho::test_false(r, "ByeArray: Should not be able to get last byte", bar.GetByte(9, p1));
    testforecho::test_true(r, "ByeArray: Should be able to get last byte", bar2.GetByte(8, p1));
    testforecho::test_eq(r, "ByeArray: Last byte should be 112", p1, 112);
    boxutil::ByteArray bar3;
    testforecho::test_true(r, "ByeArray: Should be able to get section", bar2.GetSection(0, 3, bar3));
    testforecho::test_eq(r, "ByeArray: Hex strings should match", bar3.GetHexString(), "223344");

    return r;

}

unsigned int test_bfl(){
    
    unsigned int r {0};
    
    boxutil::StrVecCont svcTest;
    testforecho::test_true(r, "BuldFileList: Should be able to make file list", boxutil::BuildFileList("../../testprops/folder", "txt", svcTest));
    testforecho::test_eq(r, "BuildFileList: Size should be 3", svcTest.Size(), static_cast<unsigned int>(3));

    testforecho::test_true(r, "BuildFileList: Should have element", (svcTest.HasElement("one.txt")));
    testforecho::test_true(r, "BuildFileList: Should have element", (svcTest.HasElement("two.txt")));
    testforecho::test_true(r, "BuildFileList: Should have element", (svcTest.HasElement("three.txt")));

    return r;
    
}

unsigned int test_strveccont(){

    unsigned int r {0};
    
    boxutil::StrVecCont v1, v2;
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

    unsigned int r {0};

    std::string logfn = "./debug.txt";
    boxutil::ManagedFile mf {logfn};
    boxutil::Logger logger(logfn.c_str());
    logger.LogInfo("day of the dog");
    std::string contents;
    boxutil::GetFileContents(logfn, contents);
    testforecho::test_true(r, "Logger: Should be able to log and retrieve", boxutil::ContainsNoCase(contents, "dog"));

    return r;

}

unsigned int test_stringmanip(){

    unsigned int r {0};

    std::string strTeste = "aaa*uuu*bbb";
    std::string strOut;
    testforecho::test_true(r, "StringManip: extremes trim, should be able to extract mid", boxutil::GetStringMidByBoundingChars(strTeste, '*', strOut));
    testforecho::test_eq(r, "StringManip: extremes trim", strOut, "uuu");

    testforecho::test_eq(r, "StringManip: Should count chars in string", boxutil::CountCharsInString("aaaaazaaaaaaza", 'z'), static_cast<unsigned int>(2));

    strTeste = "a b c";
    testforecho::test_eq(r, "StringManip: Should get next", boxutil::GetNext(strTeste), "a");
    testforecho::test_eq(r, "StringManip: Should get next", boxutil::GetNext(strTeste), "b");
    testforecho::test_eq(r, "StringManip: Should get next", boxutil::GetNext(strTeste), "c");
    testforecho::test_eq(r, "StringManip: Should get next", boxutil::GetNext(strTeste), "");

    unsigned char p[1]; p[0] = 112;
    testforecho::test_eq(r, "StringManip: Should convert from byte buffer to string", boxutil::TxtStrFromBuffer(p, 1), "p");

    p[0] = 0xaa;
    testforecho::test_eq(r, "StringManip: Should convert from byte buffer to hexstring", boxutil::HexStrFromBuffer(p, 1), "AA");

    testforecho::test_eq(r, "StringManip: Should be able to pop file extension", boxutil::PopExtension("file.txt"), "file");
    testforecho::test_eq(r, "StringManip: Should be able to get file extension", boxutil::GetExtension("file.txt"), "txt");

    testforecho::test_eq(r, "StringManip: Should be able to make uppercase", boxutil::MakeUppercase("abc"), "ABC");
    testforecho::test_eq(r, "StringManip: Should be able to make lowercase", boxutil::MakeLowercase("ABC"), "abc");

    testforecho::test_eq(r, "StringManip: Should be able to compare with no case", boxutil::CompareNoCase("border", "BOrder"), 0);
    testforecho::test_true(r, "StringManip: Should be able to check for containment", boxutil::ContainsNoCase("border", "or"));

    testforecho::test_true(r, "StringManip: Should be able to check numeric string", boxutil::IsNumericString("123"));
    testforecho::test_true(r, "StringManip: Should be able to check alphanumeric string", boxutil::IsAlpha("abc"));
    testforecho::test_true(r, "StringManip: Should be able to check alphanumeric(ext) string", boxutil::IsAlphaExt("abc..."));
    testforecho::test_true(r, "StringManip: Should be able to check bcd string", boxutil::IsBCD("1230"));
    testforecho::test_true(r, "StringManip: Should be able to check hex string", boxutil::IsHexStr("aabbcc"));
    testforecho::test_true(r, "StringManip: Should be able to check string boundaries string", boxutil::IsWithinBounds("bigstring", 2, 15));

    testforecho::test_eq(r, "StringManip: Should right-trim", boxutil::RTrim("abc   "), "abc");
    testforecho::test_eq(r, "StringManip: Should left-trim", boxutil::LTrim("   abc"), "abc");
    testforecho::test_eq(r, "StringManip: Should trim", boxutil::Trim("   abc   "), "abc");

    return r;

}

unsigned int test_datehelper(){

    unsigned int r {0};

    testforecho::test_true(r, "Datehelper: Date should be valid", boxutil::DateHelper::IsValidDate(22, 6, 1997));
    testforecho::test_true(r, "Datehelper: Date should be valid", boxutil::DateHelper::IsValidDate(22, 6, 1997));
    testforecho::test_false(r, "Datehelper: Date should be invalid", boxutil::DateHelper::IsValidDate(32, 6, 1997));
    testforecho::test_true(r, "Datehelper: Date should be valid", boxutil::DateHelper::IsValidDate("05/08/2001"));
    testforecho::test_false(r, "Datehelper: Date should be invalid", boxutil::DateHelper::IsValidDate("05/13/1985"));
    testforecho::test_eq(r, "Datehelper: Conversion should succeed", "06/03/2002", boxutil::DateHelper::ConvertFromNumbers(6, 3, 2002));

    {
        unsigned short d{0}, m{0}, y{0};
        boxutil::DateHelper::ConvertFromText("07/02/2003", d, m, y);
        testforecho::test_eq(r, "Datehelper: Conversion should succeed", 7, d);
        testforecho::test_eq(r, "Datehelper: Conversion should succeed", 2, m);
        testforecho::test_eq(r, "Datehelper: Conversion should succeed", 2003, y);
    }

    {
        unsigned short d{3}, m{4}, y{2005};
        boxutil::DateHelper::ConvertFromText("nope", d, m, y);
        testforecho::test_neq(r, "Datehelper: Conversion should fail", 3, d);
        testforecho::test_neq(r, "Datehelper: Conversion should fail", 4, m);
        testforecho::test_neq(r, "Datehelper: Conversion should fail", 2005, y);
    }

    {
        boxutil::DateHelper dh{7, 80, 1978};
        testforecho::test_eq(r, "Datehelper: Should be in an invalid state", dh.GetDateString(), "00/00/0000");
    }

    {
        boxutil::DateHelper dh{7, 5, 1985}; 
        testforecho::test_false(r, "Datehelper: Should fail to set bad date", dh.SetDate("35/20/2000"));
    }

    {
        const std::string templ {"03/03/1993"};
        boxutil::DateHelper dh{templ};
        testforecho::test_eq(r, "Datehelper: Init date and later fetched date should match", templ, dh.GetDateString());
    }

    {
        boxutil::DateHelper dh{7, 5, 1985}; dh.SetDate("35/20/2000");
        testforecho::test_eq(r, "Datehelper: Should be in an invalid state", dh.GetDateString(), "00/00/0000");
    }

    {
        boxutil::DateHelper dh{7, 5, 1985};
        testforecho::test_eq(r, "Datehelper: Should be in a valid state", dh.GetDateString(), "07/05/1985");
    }

    {
        boxutil::DateHelper dh{};
        testforecho::test_true(r, "Datehelper: Auto-built date should be valid", boxutil::DateHelper::IsValidDate(dh.GetDateString()));
    }

    {
        boxutil::DateHelper dh1{"01/01/2004"};
        boxutil::DateHelper dh2 = dh1;
        testforecho::test_eq(r, "Datehelper: Should match by the attribute copy", dh1.GetDateString(), dh2.GetDateString());
        boxutil::DateHelper dh3{dh2};
        testforecho::test_eq(r, "Datehelper: Should match by the copy constructor", dh2.GetDateString(), dh3.GetDateString());
    }

    return r;

}

unsigned int test_conversions(){

    unsigned int r {0};

    testforecho::test_eq(r, "Conversions: Conversion from decstr to int should work", boxutil::DecStrToInt("-21"), -21);
    testforecho::test_eq(r, "Conversions: Conversion from decstr to uint should work", boxutil::DecStrToUint("4294967200"), 4294967200);
    testforecho::test_eq(r, "Conversions: Conversion from decstr to short should work", boxutil::DecStrToShort("-250"), -250);
    testforecho::test_eq(r, "Conversions: Conversion from decstr to ushort should work", boxutil::DecStrToUshort("220"), 220);
    testforecho::test_true(r, "Conversions: Conversion from decstr to float should work", (boxutil::DecStrToFloat("32.1") > 32.09 && boxutil::DecStrToFloat("32.1") < 32.11) );
    testforecho::test_true(r, "Conversions: Conversion from decstr to double should work", (boxutil::DecStrToDouble("500.32") > 500.31 && boxutil::DecStrToDouble("500.32") < 500.33 ));

    testforecho::test_eq(r, "Conversions: Conversion from int to decstr should work", boxutil::IntToDecStr(-21), "-21");
    testforecho::test_eq(r, "Conversions: Conversion from uint to decstr should work", boxutil::UintToDecStr(4294967200), "4294967200");
    testforecho::test_eq(r, "Conversions: Conversion from short to decstr should work", boxutil::ShortToDecStr(-250), "-250");
    testforecho::test_eq(r, "Conversions: Conversion from ushort to decstr should work", boxutil::UshortToDecStr(220), "220");
    testforecho::test_eq(r, "Conversions: Conversion from float to decstr should work", boxutil::FloatToDecStr(32.1), "32.1");
    testforecho::test_eq(r, "Conversions: Conversion from double to decstr should work", boxutil::DoubleToDecStr(500.32), "500.32");

    testforecho::test_eq(r, "Conversions: Conversion from hexstr to int should work", boxutil::HexStrToInt("-28"), -40);
    testforecho::test_eq(r, "Conversions: Conversion from hexstr to uint should work", boxutil::HexStrToUint("15"), static_cast<unsigned int>(21));
    testforecho::test_eq(r, "Conversions: Conversion from hexstr to short should work", boxutil::HexStrToShort("-FA"), -250);
    testforecho::test_eq(r, "Conversions: Conversion from hexstr to ushort should work", boxutil::HexStrToUshort("DC"), 220);
    testforecho::test_eq(r, "Conversions: Conversion from hexstr to float should work", boxutil::HexStrToFloat("A"), 10);
    testforecho::test_eq(r, "Conversions: Conversion from hexstr to double should work", boxutil::HexStrToDouble("B"), 11);

    testforecho::test_eq(r, "Conversions: Conversion from int to hexstr should work", boxutil::IntToHexStr(-2), "-02");
    testforecho::test_eq(r, "Conversions: Conversion from uint to hexstr should work", boxutil::UintToHexStr(10), "0A");
    testforecho::test_eq(r, "Conversions: Conversion from short to hexstr should work", boxutil::ShortToHexStr(-1), "-01");
    testforecho::test_eq(r, "Conversions: Conversion from ushort to hexstr should work", boxutil::UshortToHexStr(0xDC), "DC");
    testforecho::test_eq(r, "Conversions: Conversion from float to hexstr should work", boxutil::FloatToHexStr(32.1), "32.1");
    testforecho::test_eq(r, "Conversions: Conversion from double to hexstr should work", boxutil::DoubleToHexStr(500.32), "500.32");

    return r;

}

unsigned int test_managedfile(){

    unsigned int r {0};

    std::string strFilename = "./testfile.txt";
    testforecho::test_false(r, "ManagedFile: File should not pre-exist", boxutil::FileExists(strFilename));
    boxutil::SaveFileContents(strFilename, "one");
    testforecho::test_true(r, "ManagedFile: File should exist now", boxutil::FileExists(strFilename));
    std::string s;
    testforecho::test_true(r, "ManagedFile: File should be readable", boxutil::GetFileContents(strFilename, s));
    testforecho::test_eq(r, "ManagedFile: File content should match", s, "one");
    testforecho::test_true(r, "ManagedFile: File should have been created", boxutil::FileExists(strFilename));
    {
        boxutil::ManagedFile mf {strFilename};
    }
    testforecho::test_false(r, "ManagedFile: File should have been deleted", boxutil::FileExists(strFilename));

    return r;

}

int main(int argc, char *argv[]){

    (void)argc; (void)argv;

    unsigned int r {0};

    PRINT_BREAKPOINT
    std::string test_string = "the-test-string";
    PRINT_BREAKPOINT_STR(test_string.c_str())
    int test_integer = 21;
    PRINT_BREAKPOINT_INT(test_integer)
    PRINT_BREAKPOINT_MSG("custom message: [%f]", 1.1f)

    r += test_timestamp();
    r += test_bytearray();
    r += test_bfl();
    r += test_strveccont();
    r += test_datehelper();
    r += test_conversions();
    r += test_stringmanip();
    r += test_managedfile();
    r += test_logger();

    if (r > 0){
        std::cout << r << " tests failed." << std::endl;
    } else {
        std::cout << "All tests passed." << std::endl;
    }

    return 0;

}
