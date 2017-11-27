#include<iostream>
#include"format.h"
#include"ezlog.h"
#include"filesystem.h"
using namespace std;
namespace jh = jheaders;
INIT_EZLOG

int main()
{
    EZLOG (jh::Log_level::DBUG) << jh::format ("hello{0}", " word").c_str();
    auto re = jh::list_dir ("G:/jhtools_vs2013", jh::FileType::ALL);
    
    for (auto x : re)
    {
        cout << x << endl;
    }
    
    system ("pause");
}