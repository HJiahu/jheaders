#ifndef JH_TIME_H_
#define JH_TIME_H_

#include<chrono>
#include<iostream>

namespace jheaders
{

#define TIME_CONSUME(unsigned_int_milliseconds, expr){\
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();\
expr;\
std::chrono::system_clock::time_point end = std::chrono::system_clock::now();\
unsigned_int_milliseconds =std::chrono::duration_cast<std::chrono::milliseconds>( end-start).count();\
}
}

#endif // !JH_TIME_H_
