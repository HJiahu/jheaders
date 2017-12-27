#ifndef JH_PATH_H_
#define JH_PATH_H_

#include<memory>
#include<fstream>
#include<algorithm>
#include<functional>
#include<initializer_list>
#include"3rdparty/path.h"
#include"ezlog.h"

namespace jheaders
{
    using Path = TinyPath::path;
    
    inline Path current_path();
    inline bool create_directory (const Path& p);
    inline bool is_directory (const Path&p);
    inline bool is_regular_file (const Path&p);
    inline size_t file_size (const Path&p);
    inline bool exists (const Path&p);
    inline bool copy_file (std::string &from, std::string &dst);//successfully copy file or die
    inline bool copy_file2dir (std::string &from, std::string &dst_dir);//successfully copy file or die
    inline std::string get_a_valid_path_or_die (const std::initializer_list<std::string> &paths);
    enum class FileType { ALL, FILE, DIR };//type for list in list_d
    //for directory do not return . and ..
    //return file or dir name in folder p
    inline std::vector<std::string> list_dir (const Path& p, FileType type = FileType::FILE);
    //return regular file name with extend of suffix ,eg. *.jpg
    //use op to check file or dir name
    inline std::vector<std::string> list_dir (const Path&p, std::function<bool (const std::string) > op);
    //return file name with extension ,extension string eg .jpg .txt .log
    //auto convert file extension to lower eg .Jpg -> .jpg
    inline std::vector<std::string> list_dir (const Path&p, std::string extension);
    //return file name with extension in extensions, extension has point
    inline std::vector<std::string> list_dir (const Path&p, std::vector<std::string> extensions);
    inline bool readfile2str (const Path&p, std::string&dst_str); //read file (txt) to a string, string will be cleared before write
    inline std::pair<std::shared_ptr<char>, unsigned long long>  readfile2mem (const Path&p); //read file and write content to a memory block
    
    
    
    /****************    implementtion     ****************/
    inline Path current_path()
    {
        return Path::getcwd();
    }
    
    inline bool is_directory (const Path&p)
    {
        return p.is_directory();
    }
    inline bool is_regular_file (const Path&p)
    {
        return p.is_file();
    }
    inline size_t file_size (const Path&p)
    {
        return p.file_size();
    }
    inline bool exists (const Path&p)
    {
        return p.exists();
    }
    inline bool copy_file (std::string &from, std::string &dst)
    {
        if (!exists (from))
        {
            EZLOG_ (fatal) << "no such file: " << from;
        }
        
        if (exists (dst))
        {
            EZLOG_ (fatal) << "already exists file: " << dst << "copy file failed.";
        }
        
        std::ifstream  src_f (from, std::ios::binary);
        std::ofstream  dst_f (dst, std::ios::binary);
        dst_f << src_f.rdbuf();
    }
    
    inline bool copy_file2dir (std::string &from, std::string &dst_dir)
    {
        if (!exists (from))
        {
            EZLOG_ (fatal) << "no such file: " << from;
        }
        
        if (!exists (dst_dir) && !create_directory (dst_dir))
        {
            EZLOG_ (fatal) << "Can not create this dir: " << dst_dir;
        }
        
        auto dst_file = Path (dst_dir) / Path (from).filename();
        copy_file (from, dst_file.string());
    }
    
    inline bool create_directory (const Path& p)
    {
#if defined(_WIN32)
        return CreateDirectoryW (p.wstr().c_str(), NULL) != 0;
#else
        return mkdir (p.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR) == 0;
#endif
    }
    //list directory
#if defined(_WIN32)
    //for directory do not return . and ..
#include <windows.h>
    inline std::vector<std::string> list_dir (const Path& p, FileType type)
    {
        if (!exists (p))
        {
            EZLOG (Log_level::ERR) << "no file (dircetoy): " << p.string();
            return std::vector<std::string>();
        }
        
        WIN32_FIND_DATA ffd;
        LARGE_INTEGER filesize;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        TCHAR szDir[MAX_PATH];
        int i = 0;
        std::string path_str (p.string());
        
        for (; i < path_str.size(); i++)
        {
            szDir[i] = TCHAR (path_str[i]);
        }
        
        szDir[i++] = (TCHAR) '/';
        szDir[i++] = (TCHAR) '*';
        szDir[i++] = (TCHAR) 0;
        std::vector<std::string> result;
        hFind = FindFirstFile (szDir, &ffd);
        auto list_type = FILE_ATTRIBUTE_ARCHIVE;
        
        switch (type)
        {
            case FileType::ALL:
                list_type = FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_DIRECTORY;
                break;
                
            case FileType::FILE:
                list_type = FILE_ATTRIBUTE_ARCHIVE;
                break;
                
            case FileType::DIR:
                list_type = FILE_ATTRIBUTE_DIRECTORY;
                break;
                
            default:
                break;
        }
        
        do
        {
            //FILE_ATTRIBUTE_ARCHIVE
            //FILE_ATTRIBUTE_DIRECTORY
            if (list_type & ffd.dwFileAttributes)
            {
                std::string str;
                
                for (const auto &x : ffd.cFileName)
                {
                    if (x == 0) { break; }
                    
                    str += static_cast<char> (x);
                }
                
                result.push_back (str);
            }
            
            else
            {
                filesize.LowPart = ffd.nFileSizeLow;
                filesize.HighPart = ffd.nFileSizeHigh;
            }
        }
        while (FindNextFile (hFind, &ffd) != 0);
        
        FindClose (hFind);
        
        if (type != FileType::FILE && result.size() >= 2)
        {
            return std::vector<std::string> (result.begin() + 2, result.end());
        }
        
        else
        {
            return result;
        }
    }
#else
#include<dirent.h>
    //for directory do not return . and ..
    inline std::vector<std::string> list_dir (const Path &dir_path, FileType type)
    {
        std::vector<std::string> files;
    
        if (!exists (dir_path))
        {
            EZLOG (Log_level::ERR) << "no such file or Path: " << dir_path.string();
            return files;
        }
    
        DIR *dp = opendir (dir_path.string().c_str());
        struct dirent *dirp;
    
        while ( (dirp = readdir (dp)) != NULL)
        {
            if (std::string (".") == std::string (dirp->d_name) || std::string ("..") == std::string (dirp->d_name))
            {
                continue;
            }
    
            auto full_path = dir_path / Path (std::string (dirp->d_name));
    
            switch (type)
            {
                case FileType::ALL:
                    {
                        files.push_back (dirp->d_name);
                    }
                    break;
    
                case FileType::DIR:
                    {
                        if (is_directory (full_path))
                        {
                            files.push_back (dirp->d_name);
                        }
                    }
                    break;
    
                case FileType::FILE:
                    {
                        if (is_regular_file (full_path))
                        {
                            files.push_back (dirp->d_name);
                        }
                    }
                    break;
            }
        }
    
        closedir (dp);
        // if (type != FileType::FILE && files.size() >= 2) { return std::vector<std::string> (files.begin() + 2, files.end()); }
        return files;
    }
#endif
    
    inline std::vector<std::string> list_dir (const Path&p, std::function<bool (const std::string) > op)
    {
        std::vector<std::string> file_names;
        auto all_fles = list_dir (p, FileType::ALL);
        
        for (auto&f : all_fles)
        {
            if (op (f))
            {
                file_names.push_back (f);
            }
        }
        
        return file_names;
    }
    
    inline std::vector<std::string> list_dir (const Path&p, std::vector<std::string> extensions)
    {
        std::vector<std::string> file_names;
        auto all_fles = list_dir (p, FileType::FILE);
        auto to_lower = [] (std::string  s)->std::string
        {
            std::transform (s.begin(), s.end(), s.begin(), [] (unsigned char c) {return std::tolower (c); });
            return s;
        };
        
        for (auto&f : all_fles)
        {
            auto lower_extension = to_lower (Path (f).extension());
            
            for (auto &e : extensions)
            {
                if (e == lower_extension)
                {
                    file_names.push_back (f);
                }
            }
        }
        
        return file_names;
    }
    
    inline std::vector<std::string> list_dir (const Path&p, std::string extension)
    {
        return list_dir (p, std::vector<std::string> {extension});
    }
    
    inline bool readfile2str (const Path&p, std::string&dst_str)
    {
        std::ifstream in;
        
        if (!exists (p) || !is_regular_file (p) || ! (in.open (p.string()), in.good()))
        {
            EZLOG_ (fatal) << "can not open file: " << p.string();
        }
        
        std::stringstream buffer;
        buffer << in.rdbuf();
        dst_str = buffer.str();
        
        if (!in)
        {
            EZLOG_ (fatal) << "read file failed: " << p.string();
            //return{ ptr, unsigned long long (0) };
        }
        
        else
        {
            return true;
        }
    }
    
    inline std::pair<std::shared_ptr<char>, unsigned long long> readfile2mem (const Path&p)
    {
        std::ifstream in ;
        
        if (!exists (p) || !is_regular_file (p) || ! (in.open (p.string(), std::ifstream::binary), in.good()))
        {
            EZLOG_ (fatal) << "can not open file: " << p.string();
        }
        
        std::shared_ptr<char> ptr (nullptr, [] (char *data) {delete[] data; });
        in.seekg (0, std::ios::end);
        unsigned long long file_size = in.tellg();
        in.seekg (0, std::ios::beg);
        
        try
        {
            ptr.reset (new char[file_size]);
        }
        
        catch (std::exception &e)
        {
            EZLOG_ (fatal) << "can not malloc mem: " << file_size << " bytes. msg: " << e.what();
        }
        
        in.read (ptr.get(), file_size);
        
        if (!in)
        {
            EZLOG_ (fatal) << "read file failed: " << p.string();
            return{ ptr, (unsigned long long) (0) };
        }
        
        else
        {
            return{ ptr, file_size };
        }
    }
    
    inline std::ostream& operator<< (std::ostream&out, const std::initializer_list<std::string> &paths)
    {
        out << std::endl;
        
        for (auto&p : paths)
        {
            out << p << std::endl;
        }
        
        return out;
    }
    inline std::string get_a_valid_path_or_die (const std::initializer_list<std::string> &paths)
    {
        for (auto&path : paths)
        {
            if (exists (path))
            {
                return path;
            }
        }
        
        EZLOG_ (fatal) << "no one path in paths is valid: " << paths;
    }
}

#endif // !JH_PATH_H_




