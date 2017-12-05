#include<iostream>
#include"format.h"
#include"ezlog.h"
#include"filesystem.h"
#include"json.h"
#include"string_utils.h"
#include"utils.h"
#include"time.h"
using namespace std;
namespace jh = jheaders;

#ifndef _MSC_VER
    #define INIT_EZLOG
#endif // !_MSC_VER

int main()
{
    unsigned millis;
    TIME_CONSUME (millis, [] {int i = 0; while (true) { if (i++ > 999999999) break; } }());
    std::cout << millis << endl;
#ifdef _MSC_VER
    system ("pause");
#endif
}
