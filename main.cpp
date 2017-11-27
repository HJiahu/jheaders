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
    auto re = jh::list_dir ("./", jh::FileType::ALL);
    
    for (auto x : re)
    {
        cout << x << endl;
    }
#ifdef _MSC_VER    
    system ("pause");
#endif
}
