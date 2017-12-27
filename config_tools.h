#ifndef JH_CONFIG_TOOLS_H_
#define JH_CONFIG_TOOLS_H_

#include <map>
#include <string>
#include "filesystem.h"
#undef min
#undef max
#include "3rdparty/cpptoml/cpptoml_0.4.h"




namespace jheaders
{
    namespace toml04 = cpptoml;
    //the usage of cpptoml can be find at 3rdparty/cpptoml
    
    //just parse simple toml file(just key value)£¬all value would be converted to string
    //std::map<std::string, std::string> parse_simple_toml_file (const std::string &path)
    //{
    //    if (!exists (path))
    //    {
    //        EZLOG_ (fatal) << "can not open config file: " << path;
    //    }
    //
    //    else
    //    {
    //        auto configs = cpptoml::parse_file (path);
    //    }
    //}
    
}

#endif // !JH_CONFIG_TOOLS_H_
