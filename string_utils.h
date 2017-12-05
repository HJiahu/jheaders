#ifndef JH_STRING_UTILS_H_
#define JH_STRING_UTILS_H_

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace jheaders
{
    //utils for this header
    template<int (&F) (int) >
    int safe_ctype (unsigned char c)
    {
        return F (c);
    }
    
    inline bool ends_with (const std::string &s, char ch)
    {
        return !s.empty() && s.back() == ch;
    }
    
    inline bool ends_with (const std::string &s, const std::string &suffix)
    {
        //mismatch 是C++STL的非变易算法，用于查找两个序列中第一个不匹配的元素的位置
        //mismatch 返回值是一个pair，保存两个分别指向两个序列对应元素的迭代器
        return (suffix.size() <= s.size()) && std::mismatch (suffix.rbegin(), suffix.rend(), s.rbegin()).first == suffix.rend();
    }
    
    inline bool starts_with (const std::string &s, char ch)
    {
        return !s.empty() && s.front() == ch;
    }
    
    inline bool starts_with (const std::string &s, const std::string &prefix)
    {
        return (prefix.size() <= s.size()) && std::mismatch (prefix.begin(), prefix.end(), s.begin()).first == prefix.end();
    }
    
    template <class Op>
    void split (const std::string &s, char delim, Op op)
    {
        std::stringstream ss (s);
        
        for (std::string item; std::getline (ss, item, delim);)
        {
            if (item.size() != 0)
            { *op++ = item; }
        }
    }
    
    
    inline std::vector<std::string> split (const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split (s, delim, std::back_inserter (elems));
        return elems;
    }
    
    //删除字符串最右侧的 space
    inline void rtrim (std::string &s)
    {
        s.erase (std::find_if (s.rbegin(), s.rend(), [] (int c) {return !std::isspace (c); }).base(), s.end());
    }
    
    inline void ltrim (std::string &s)
    {
        s.erase (s.begin(), find_if (s.begin(), s.end(), [] (int c) {return !std::isspace (c); }));
    }
    //删除两侧的 space
    inline void trim (std::string &s)
    {
        ltrim (s);
        rtrim (s);
    }
    
    inline void toupper (std::string &s)
    {
        std::transform (s.begin(), s.end(), s.begin(), [] (unsigned char c) {return std::toupper (c); });
    }
    
    inline void tolower (std::string &s)
    {
        std::transform (s.begin(), s.end(), s.begin(), [] (unsigned char c) {return std::tolower (c); });
    }
    
    
    inline std::string join_str (char glue, const std::vector<std::string> &pieces)
    {
        std::string s;
        
        if (!pieces.empty())
        {
            s.append (pieces[0]);
            
            for (size_t i = 1; i < pieces.size(); ++i)
            {
                s.push_back (glue);
                s.append (pieces[i]);
            }
        }
        
        return s;
    }
    
    
    inline std::string join_str (const std::string &glue, const std::vector<std::string> &pieces)
    {
        std::string s;
        
        if (!pieces.empty())
        {
            s.append (pieces[0]);
            
            for (size_t i = 1; i < pieces.size(); ++i)
            {
                s.append (glue);
                s.append (pieces[i]);
            }
        }
        
        return s;
    }
}

#endif // !JH_STRING_UTILS_H_
