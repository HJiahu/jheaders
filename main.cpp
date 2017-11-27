#include<iostream>
#include"format.h"
#include"ezlog.h"
#include"filesystem.h"
#include"json.h"
using namespace std;
namespace jh = jheaders;

#ifndef _MSC_VER
    #define INIT_EZLOG
#endif // !_MSC_VER



int main()
{
    EZAssert (false)<<"this is a test";
    auto m = jh::parse_simple_json (R"(C:\Users\HJiahu\Desktop\json.txt)");
    
    for (auto x : m)
    {
        cout << x.first << " " << x.second << endl;
    }
    
#ifdef _MSC_VER
    system ("pause");
#endif
}
