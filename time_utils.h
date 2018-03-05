#ifndef JH_TIME_H_
#define JH_TIME_H_

#include<chrono>
#include<iostream>
#include<thread>
#include"universal_utils.h"
#include"ezlog.h"

//there is a good lib for datetime at:https://howardhinnant.github.io/date/date.html
//I will add it later

namespace jheaders
{

#define TIME_CONSUME_MICRO_SECS(unsigned_int_microseconds, expr){\
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();\
expr;\
std::chrono::system_clock::time_point end = std::chrono::system_clock::now();\
unsigned_int_microseconds =std::chrono::duration_cast<std::chrono::microseconds>( end-start).count();\
}

#define TIME_CONSUME_MILLI_SECS(unsigned_int_millisecond, expr){\
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();\
expr;\
std::chrono::system_clock::time_point end = std::chrono::system_clock::now();\
unsigned_int_millisecond =std::chrono::duration_cast<std::chrono::milliseconds>( end-start).count();\
}

    //创建之时即开始计时
    class Timer: public NonCopyMoveable
    {
        public:
            Timer () :
                start_point_{ std::chrono::system_clock::now() }, thread_id_{std::this_thread::get_id() }
            {}
            void reset()
            {
                check();
                start_point_ = std::chrono::system_clock::now();
            }
            unsigned int elapsed_milliseconds (const std::string& msg) //如果msg为空则不打印信息，否则打印形式为msg123\n，下同
            {
                check();
                unsigned int millis = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - start_point_).count();
                
                if (!msg.empty())
                {
                    std::cout << msg << millis << std::endl;
                }
                
                return millis;
            }
            unsigned int elapsed_microseconds (const std::string& msg)
            {
                check();
                unsigned int micros = std::chrono::duration_cast<std::chrono::microseconds> (std::chrono::system_clock::now() - start_point_).count();
                
                if (!msg.empty())
                {
                    std::cout << msg << micros << std::endl;
                }
                
                return micros;
            }
            unsigned int elapsed_seconds (const std::string& msg)
            {
                check();
                unsigned int secs = std::chrono::duration_cast<std::chrono::seconds> (std::chrono::system_clock::now() - start_point_).count();
                
                if (!msg.empty())
                {
                    std::cout << msg << secs << std::endl;
                }
                
                return secs;
            }
        private:
            bool check()
            {
                if (std::this_thread::get_id() != thread_id_)
                {
                    EZLOG_ (warn) << "Timer used in different thread";
                }
                
                return true;
            }
        private:
            std::thread::id thread_id_;//创建当前对象的线程ID
            std::chrono::system_clock::time_point start_point_;
    };
}

#endif // !JH_TIME_H_
