#ifndef JH_LOCK_H_
#define JH_LOCK_H_

#include<atomic>
#include"universal_utils.h"
namespace jheaders
{
    //spinlock is extracted from boost\smart_ptr\detail\spinlock_std_atomic.hpp
    class spinlock : public noncopyable
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
                    //boost::detail::yield(k);
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
