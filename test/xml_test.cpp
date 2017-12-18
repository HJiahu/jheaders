#include"catch.h"
#include"../xml_utils.h"

namespace jh = jheaders;

TEST_CASE ("XML::node_str")
{
    std::string file_path{ R"(D:\jheaders\jheaders\test\test_files\a739.xml)" };
    
    if (!jh::exists (file_path))
    {
        std::string file_in_test{ "./test_files/a739.xml" };
        
        if (jh::exists (file_in_test))
        {
            file_path = file_in_test;
        }
        
        else
        {
            EZLOG_ (fatal) << R"(please add a test file for TEST_CASE "XML::node_str")";
        }
    }
    

}