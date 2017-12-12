#ifndef JH_LOCK_H_
#define JH_LOCK_H_

#include<atomic>
#include<thread>
#include<chrono>
#include"universal_utils.h"
#include<iostream>

// BOOST_SMT_PAUSE

#if defined(_MSC_VER) && _MSC_VER >= 1310 && ( defined(_M_IX86) || defined(_M_X64) )
    //#include <windows.h>
    extern "C" void _mm_pause();
    
    #define BOOST_SMT_PAUSE _mm_pause();
    
#elif defined(__GNUC__) && ( defined(__i386__) || defined(__x86_64__) )
    
    #define BOOST_SMT_PAUSE __asm__ __volatile__( "rep; nop" : : : "memory" );
    
#endif

//

namespace jheaders
{


    //spinlock is extracted from boost\smart_ptr\detail\spinlock_std_atomic.hpp
    class SpinLock : public NonCopyable
    {
        public:
        
            bool try_lock()
            {
                return !v_.test_and_set (std::memory_order_acquire);
            }
            
            void lock()
            {
                for (unsigned k = 0; !try_lock(); ++k)
                {
                    if (k < 4)
                    {
                    }
                    
#if defined( BOOST_SMT_PAUSE )
                    
                    else
                        if (k < 16)
                        {
                            BOOST_SMT_PAUSE
                        }
                        
#endif
                        
                        else
                            if (k < 32)
                            {
                                std::this_thread::sleep_for (std::chrono::microseconds (1));
                            }
                            
                            else
                            {
                                std::this_thread::sleep_for (std::chrono::milliseconds (1));
                            }
                }
            }
            
            void unlock()
            {
                v_.clear (std::memory_order_release);
            }
        private:
            std::atomic_flag v_;
    };
}//namespace
#endif // !JH_LOCK_H_
