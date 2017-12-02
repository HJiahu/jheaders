#ifndef JH_FORMAT_H_
#define JH_FORMAT_H_
//Optional header-only configuration enabled with the FMT_HEADER_ONLY macro.
//this line #define FMT_HEADER_ONLY had been added to original format.h

#include"3rdparty/format.h"

namespace jheaders
{
    //print("Hello, {}!", "world");  // uses Python-like format string syntax
    //printf("Hello, %s!", "world"); // uses printf format string syntax
    //print(stderr, "System error code = {}\n", errno);
    //print("Hello, {name}! The answer is {number}. Goodbye, {name}.", fmt::arg("name", "World"), fmt::arg("number", 42));
    //print("Hello, {name}! The answer is {number}. Goodbye, {name}.", "name"_a = "World", "number"_a = 42);
    using fmt::print;
    
    //std::string s = format("{0}{1}{0}", "abra", "cad");
    
    using fmt::format;
    
    //MemoryWriter w;
    //w.write("Look, a {} string", 'C');
    //w.c_str(); // returns a C string (const char*)
    using fmt::MemoryWriter; //use fmt::MemoryWriter to avoid constructing std::string
    
    /****
      Allows integer, floating-point, character, and string literals to produce objects of user-defined type by defining a user-defined suffix.
      http://en.cppreference.com/w/cpp/language/user_literal
    ****/
    //using namespace fmt::literals;
    //std::string message = "{0}{1}{0}"_format("abra", "cad");
}

#endif