#ifndef JH_UTILS_H_
#define JH_UTILS_H_

namespace jheaders
{
    class noncopyable
    {
        protected:
            noncopyable() = default;
            ~noncopyable() = default;
            noncopyable (const noncopyable&) = delete;
            noncopyable& operator= (const noncopyable&) = delete;
    };
    
    class noncopy_moveable
    {
        protected:
            noncopy_moveable() = default;
            ~noncopy_moveable() = default;
            noncopy_moveable (const noncopy_moveable&) = delete;
            noncopy_moveable& operator= (const noncopy_moveable&) = delete;
            noncopy_moveable (noncopy_moveable&&) = delete;
            noncopy_moveable& operator= (noncopy_moveable&&) = delete;
    };
}



#endif // !JH_UTILS_H_