#include<vector>
#include<gtest/gtest.h>
#include<jheaders/string_utils.h>

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



TEST (string_utils, start_end)
{
    //start with
    EXPECT_TRUE (jh::starts_with (test_strs[0], ""));
    EXPECT_FALSE (jh::starts_with (test_strs[0], "tih"));
    EXPECT_FALSE (jh::starts_with (test_strs[0], 'r'));
    EXPECT_TRUE (jh::starts_with (test_strs[0], "t"));
    EXPECT_TRUE (jh::starts_with (test_strs[0], 't'));
    EXPECT_TRUE (jh::starts_with (test_strs[0], "thi"));
    EXPECT_TRUE (jh::starts_with (test_strs[0], "this "));
    EXPECT_TRUE (jh::starts_with (test_strs[0], "this "));
    EXPECT_TRUE (jh::starts_with (test_strs[0], test_strs[0]));
    //end with
    EXPECT_TRUE (jh::ends_with (test_strs[0], ""));
    EXPECT_FALSE (jh::ends_with (test_strs[0], "gn"));
    EXPECT_TRUE (jh::ends_with (test_strs[0], "ng"));
    EXPECT_TRUE (jh::ends_with (test_strs[0], test_strs[0]));
}



TEST (string_utils, split)
{
    auto vs = jh::split (test_strs[1], ' ');
    EXPECT_TRUE (vs == (vector<string> {"this", "is", "a", "test", "string"})) << jh::join_str ('_', vs);
    EXPECT_TRUE (jh::split (test_strs[0], ' ') == (vector<string> {"this", "is", "a", "test", "string"}));
    EXPECT_TRUE (jh::split ("    ", ' ') == vector<string>());
    EXPECT_TRUE (jh::split (test_strs[4], 'c') == vector<string> {test_strs[4]});
    EXPECT_TRUE (jh::split ("", ' ') == vector<string>());
    EXPECT_TRUE (jh::split ("", 'c') == vector<string>());
}

TEST (string_utils, trim)
{
    auto test_1 = test_strs[0];
    jh::ltrim (test_1);
    EXPECT_TRUE (test_1 == test_strs[0]);
}

