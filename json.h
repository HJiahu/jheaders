#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include"3rdparty/json.hpp"
#include"ezlog.h"

namespace jheaders
{
    using nlohmann::json;
    
    //json without nest，just key and value（int,float,double,string）
    inline std::map<std::string, std::string> parse_simple_json_str (const std::string&json_str)
    {
        json jn;
        
        try
        {
            jn = json::parse (json_str.c_str());
        }
        
        catch (std::exception &e)
        {
            EZLOG (Log_level::FATAL) << "parse json string failed: " << e.what();
        }
        
        std::map<std::string, std::string> results;
        
        for (json::iterator it = jn.begin(); it != jn.end(); ++it)
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
    
    //json without nest，just key and value（int,float,double,string）
    inline std::map<std::string, std::string> parse_simple_json (const std::string &json_file_path)
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