#include"catch.h"
#include"../json.h"

using namespace std;
using namespace jheaders;

static string a_json_str_for_test = R"(
{
"int":123,
"double":3.1415926,
"string":"hello,this is a test json",
"empty_str":""
}
)";

TEST_CASE("parse_simple_json_str") {
	auto parse_result = parse_simple_json_str(a_json_str_for_test);
	REQUIRE(parse_result["int"] == "123");
	REQUIRE(parse_result["double"] == "3.1415926");
	REQUIRE(parse_result["string"] == "hello,this is a test json");
	REQUIRE(parse_result["empty_str"] == "");

}