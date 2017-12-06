#include<vector>
#include"catch.h"
#include"../string_utils.h"

using namespace std;
namespace jh = jheaders;
static const vector<string> test_strs
{
    "this is a test string",//0
    " this is a test      string ",//1
    "lena.jpg",//2
    "caffe_.log",//3
    "     ",//4
    "",//5
};



TEST_CASE ("string_utils, start_end")
{
    //start with
    REQUIRE (jh::starts_with (test_strs[0], ""));
    REQUIRE_FALSE (jh::starts_with (test_strs[0], "tih"));
    REQUIRE_FALSE (jh::starts_with (test_strs[0], 'r'));
    REQUIRE (jh::starts_with (test_strs[0], "t"));
    REQUIRE (jh::starts_with (test_strs[0], 't'));
    REQUIRE (jh::starts_with (test_strs[0], "thi"));
    REQUIRE (jh::starts_with (test_strs[0], "this "));
    REQUIRE (jh::starts_with (test_strs[0], "this "));
    REQUIRE (jh::starts_with (test_strs[0], test_strs[0]));
    //end with
    REQUIRE (jh::ends_with (test_strs[0], ""));
    REQUIRE_FALSE (jh::ends_with (test_strs[0], "gn"));
    REQUIRE (jh::ends_with (test_strs[0], "ng"));
    REQUIRE (jh::ends_with (test_strs[0], test_strs[0]));
}



TEST_CASE ("string_utils, split")
{
    auto vs = jh::split (test_strs[1], ' ');
    REQUIRE (vs == (vector<string> {"this", "is", "a", "test", "string"}));
    REQUIRE (jh::split (test_strs[0], ' ') == (vector<string> {"this", "is", "a", "test", "string"}));
    REQUIRE (jh::split ("    ", ' ') == vector<string>());
    REQUIRE (jh::split (test_strs[4], 'c') == vector<string> {test_strs[4]});
    REQUIRE (jh::split ("", ' ') == vector<string>());
    REQUIRE (jh::split ("", 'c') == vector<string>());
}

TEST_CASE ("string_utils, trim")
{
    auto test_1 = test_strs[0];
    jh::ltrim (test_1);
    REQUIRE (test_1 == test_strs[0]);
}

