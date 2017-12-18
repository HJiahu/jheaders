#include"catch.h"
#include"../filesystem.h"

namespace jh = jheaders;

TEST_CASE ("test filesystem readfile2mem")
{
    std::string file_path{R"(D:\jheaders\jheaders\test\makefile)"};
    
    if (!jh::exists (file_path))
    {
        std::string file_in_test{ "./makefile" };
        
        if (jh::exists (file_in_test))
        {
            file_path = file_in_test;
        }
        
        else
        {
            EZLOG_ (fatal) << R"(please a test file for TEST_CASE "test filesystem readfile2mem")";
        }
    }
    
    auto file_info = jh::readfile2mem (file_path);
    REQUIRE (file_info.first != nullptr);
    REQUIRE (file_info.second == jh::Path (file_path).file_size());
}

TEST_CASE ("test filesystem readfile2str")
{
    std::string file_path{ R"(D:\jheaders\jheaders\test\test_files\test_file_for_filesystem.txt)" };
    
    if (!jh::exists (file_path))
    {
        std::string file_in_test{ "./test_files/test_file_for_filesystem.txt" };
        
        if (jh::exists (file_in_test))
        {
            file_path = file_in_test;
        }
        
        else
        {
            EZLOG_ (fatal) << R"(please add a test file for TEST_CASE "test filesystem readfile2mem")";
        }
    }
    
    std::string str_buf;
    jh::readfile2str (file_path, str_buf);
    REQUIRE (str_buf == "this is a test file.");
}
