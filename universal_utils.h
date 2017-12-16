#ifndef JH_UTILS_H_
#define JH_UTILS_H_

#include<iostream>
#include<functional>
#include<exception>
//this header only use std libs

/*
	this header has:
		class noncopyable;
		class noncopy_moveable;
		class ScopeGuard
*/

namespace jheaders
{
    class NonCopyable
    {
        protected:
            NonCopyable() = default;
            ~NonCopyable() = default;
            NonCopyable (const NonCopyable&) = delete;
            NonCopyable& operator= (const NonCopyable&) = delete;
    };
    
    class NonCopyMoveable
    {
        protected:
            NonCopyMoveable() = default;
            ~NonCopyMoveable() = default;
            NonCopyMoveable (const NonCopyMoveable&) = delete;
            NonCopyMoveable& operator= (const NonCopyMoveable&) = delete;
            NonCopyMoveable (NonCopyMoveable&&) = delete;
            NonCopyMoveable& operator= (NonCopyMoveable&&) = delete;
    };
    
    class ScopeGuard: NonCopyMoveable
    {
        public:
            ScopeGuard (std::function<void (void) > f) : fun_ (f) {}
            ~ScopeGuard()
            {
                try
                {
                    fun_();
                }
                
                catch (std::exception &e)
                {
                    std::cerr << "some thing wrong in fun called by ScopeGuard: " << std::endl;
                    std::cerr << e.what() << std::endl;
                    getchar();
                    exit (1);
                }
            }
        private:
            std::function<void (void) > fun_;
    };
}



#endif // !JH_UTILS_H_