#include<mutex>
#include<future>
#include<cassert>
#include<functional>
#include<atomic>
#include<thread>
#include"../ezlog.h"
#include"catch.h"
#include"../locks.h"

namespace jh = jheaders;
using namespace std;

volatile unsigned long value_g = 0;
jh::SpinLock splock;
mutex mtx;

template<typename lock_type>
int loop (bool inc, unsigned long limit, lock_type& lock)
{
    for (int i = 0; i < limit; ++i)
    {
        //lock_guard<mutex> lg (mtx);
        lock_guard<lock_type> splg (lock);
        
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
    unsigned long increase_times = 10000000;
    unsigned long decrease_times = 10000000;
    //test for mutex
    value_g = 0;
    chrono::system_clock::time_point start = chrono::system_clock::now();
    auto result = async (launch::async, [&] {return loop (true, increase_times, mtx); });
    loop (false, decrease_times, mtx);
    result.get();
    REQUIRE (value_g == increase_times - decrease_times);
    chrono::system_clock::time_point mtx_end = chrono::system_clock::now();
    //test for spinlock
    value_g = 0;
    auto result_sp = async (launch::async, [&] {return loop (true, increase_times, splock); });
    loop (false, decrease_times, splock);
    result_sp.get();
    REQUIRE (value_g == increase_times - decrease_times);
    chrono::system_clock::time_point sp_end = chrono::system_clock::now();
    EZLOG_ (info) << "\nmutex ms: " << chrono::duration_cast<chrono::milliseconds> (mtx_end - start).count() \
                  << "\nspinlock ms: " << chrono::duration_cast<chrono::milliseconds> (sp_end - mtx_end).count();
}