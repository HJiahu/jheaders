#include<cfloat>
#include<cstdio>
#include<fstream>
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
	REQUIRE(fabs(stod(parse_result["double"])- stod("3.1415926")) <= DBL_MAX_EXP);
	REQUIRE(parse_result["string"] == "hello,this is a test json");
	REQUIRE(parse_result["empty_str"] == "");
}


TEST_CASE("parse_simple_json from file")
{
	char test_file_name[L_tmpnam];
	tmpnam(test_file_name);
	cout << "tmp file name: " << test_file_name << endl;
	ofstream out(test_file_name);
	out.write(a_json_str_for_test.c_str(), a_json_str_for_test.size());
	out.close();
	REQUIRE(parse_simple_json_str(a_json_str_for_test) == parse_simple_json_from_file(test_file_name));	
}