#ifndef JH_JSON_H_
#define JH_JSON_H_

#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include"ezlog.h"

//#define JSON_WITHOUT_CPP11

// exclude unsupported compilers
#if defined(__clang__)
    #if (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__) < 30400
        #define JSON_WITHOUT_CPP11
        #include"3rdparty/picojson.h"
    #else
        #include"3rdparty/Json.hpp"
    #endif
#elif defined(__GNUC__)
    #if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 40900
        #define JSON_WITHOUT_CPP11
        #include"3rdparty/picojson.h"
    #else
        #include"3rdparty/Json.hpp"
    #endif
#elif defined(_MSC_VER)// just support vs2015 or above
    #ifndef JSON_WITHOUT_CPP11
        #include"3rdparty/Json.hpp"
    #else
        #include"3rdparty/picojson.h"
    #endif // !JSON_WITHOUT_CPP11
#endif

namespace jheaders
{
#ifndef JSON_WITHOUT_CPP11
    using Json = nlohmann::json;
    //Json without nest，just key and value（int,float,double,string）
    inline std::map<std::string, std::string> parse_simple_json_str (const std::string&json_str)
    {
        Json jn;
        
        try
        {
            jn = Json::parse (json_str.c_str());
        }
        
        catch (std::exception &e)
        {
            EZLOG (Log_level::FATAL) << "parse Json string failed: " << e.what();
        }
        
        std::map<std::string, std::string> results;
        
        for (Json::iterator it = jn.begin(); it != jn.end(); ++it)
        {
            std::string key = it.key();
            std::string value = it.value().dump();
            
            if (it.value().is_string())
            {
                if (value.size() == 2) //just has ""
                {
                    value.clear();
                }
                
                else
                {
                    value = std::string (value.begin() + 1, value.end() - 1);
                }
            }
            
            results[key] = value;
        }
        
        return results;
    }
#else
    inline std::map<std::string, std::string> parse_simple_json_str (const std::string&json_str)
    {
        picojson::value v;
        std::string err = picojson::parse (v, json_str);
        std::map<std::string, std::string> results;
    
        if (!err.empty())
        {
            EZLOG_ (fatal) << err;
        }
    
        else
        {
            const picojson::value::object& obj = v.get<picojson::object>();
    
            for (picojson::value::object::const_iterator i = obj.begin();
                    i != obj.end();
                    ++i)
            {
                //std::cout << i->first << ": " << i->second.to_str() << std::endl;
                results[i->first] = i->second.to_str();
            }
        }
    
        return results;
    }
    
#endif // !JSON_WITHOUT_CPP11
    //Json without nest，just key and value（int,float,double,string）
    inline std::map<std::string, std::string> parse_simple_json (const std::string & json_file_path)
    {
        std::ifstream in (json_file_path);
        std::map<std::string, std::string> result;
        std::string contents;
        
        if (!in)
        {
            EZLOG (Log_level::FATAL) << "read file failed: " << json_file_path;
        }
        
        else
        {
            std::ostringstream out_str;
            out_str << in.rdbuf();
            contents = out_str.str();
        }
        
        return  parse_simple_json_str (contents);
    }
}

#endif