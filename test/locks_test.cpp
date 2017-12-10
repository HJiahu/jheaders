#include<mutex>
#include<future>
#include<cassert>
#include<functional>
#include<atomic>
#include<thread>
#include"catch.h"
#include"../locks.h"

namespace jh = jheaders;
using namespace std;

volatile unsigned long value_g = 0;
jh::spinlock splock;
mutex mtx;
int loop (bool inc, unsigned long limit)
{
    for (int i = 0; i < limit; ++i)
    {
        //lock_guard<mutex> lg (mtx);
        lock_guard<jh::spinlock> splg (splock);
        
        if (inc)
        {
            ++value_g;
        }
        
        else
        {
            --value_g;
        }
    }
    
    return 0;
}

TEST_CASE ("locks spinlock")
{
	unsigned long increase_times = 100000000;
	unsigned long decrease_times = 100000000;
    auto result = async (launch::async, loop, true, increase_times);
    loop (false, decrease_times);
    result.get();
    REQUIRE (value_g == increase_times - decrease_times);
}