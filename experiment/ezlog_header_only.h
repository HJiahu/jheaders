#ifndef EZLOG_TRANDITION_H_
#define EZLOG_TRANDITION_H_

#include<cstdio>

#include<ctime>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<mutex>
#include<memory>
#include<atomic>
#include<iomanip>
#include"3rdparty/termcolor.h"

namespace jheaders
{
    //usage: EZLOG(level)<<"hello"<<"word"<<"!";
    //Macro EZLOG depends on EZlog::log() and will append file and line number where EZLOG was called
#define EZLOG(level) jheaders::EZlog::create_logstream(level,std::string(" [")+__FILE__+": "+std::to_string(__LINE__)+"]")
    ////usage: EZLOG(info)<<...  or EZLOG(fatal)<<... and so on ,level_str can be: info, debug, warn, error, fatal
#define EZLOG_(level_str) EZLOG([]{for(int i=0;;i++){if(i == static_cast<int>(Log_level_fullname::level_str))return static_cast<Log_level>(i);}}())
    
#ifdef _DEBUG
    #define EZLOG_D(msg) jheaders::EZlog::Instance().log_debug(msg+std::string(" [")+__FILE__+": "+std::to_string(__LINE__)+"]")
#else
    #define EZLOG_D(msg)  ;
#endif //EZLOG_DEBUG_DO_NOTHING
    
#define EZAssert(expr) bool(expr) || EZLOG(jheaders::Log_level::FATAL)<<"assert failed: "#expr<<". msg: "
    //small help functions
    //return a string like: 2017-11-27 17:33:52
    inline std::string current_time_YMDT();
    inline std::string trim_time_str (const std::string &str, int type = 0);
    /****** configures ******/
    //logs will be storaged in file LOG_FILE_NAME_PREFIX
    static const std::string LOG_FILE_NAME_PREFIX{ "ezlog_" };
    
    //if defined this macro below ,all logs would not show on terminal.
    //#define NO_TERMINAL_DISP  //just storage msg in log file , do not show msg on terminal
    
    //level less than LOG_LEVEL_THRES_ will not write into log file
    enum class Log_level { INFO, DBUG, WARN, ERR, FATAL};
    enum class Log_level_fullname {info, debug, warn, error, fatal};
    const Log_level LOG_LEVEL_THRES_ = Log_level::INFO; //all log msg will write into log file as default
    using LOG_LEVEL = Log_level;
    
    //if no define _DEBUG  macro, EZLOG_D (debug) will do nothing
    
    /****** end of configures ******/
    //use EZlog::log(LEVEL) to choose different log level
    class Logstream final : public std::ostringstream
    {
        public:
            Logstream (Log_level level = Log_level::INFO, const std::string suffix = "") :
                level_ (level), suffix_ (suffix)
            {  }
            
            inline void print_and_save_msg() const;
            ~Logstream() { print_and_save_msg(); }
        private:
            Log_level level_;
            std::string suffix_;//this string will be appended to log msg
    };
    
    
    class EZlog
    {
        public:
            friend class Logstream;
            struct LogInfos
            {
                std::string log_file_{ LOG_FILE_NAME_PREFIX + trim_time_str (current_time_YMDT(), 1) + ".log" };
                std::ofstream log_file_stream_{ log_file_};
                std::mutex log_file_mutex_;
                std::mutex console_mutex_;
                std::atomic_int cnt_;
            };
            EZlog()
            {
                //static EZlog* log_instance_;
                static LogInfos globale_loginfos_;
                globale_loginfos_.cnt_++;
                
                if (globale_loginfos_.cnt_ > 999)
                {
                    std::cerr << termcolor::on_magenta \
                              << "There are too many EZlog instance objs in your project,please use another log lib instead of ezlog." << std::endl;
                    getchar();
                    exit (1);
                }
                
                //log_file_ and EZlog::log_file_stream_ is initialed in jheaders.cpp
                if (globale_loginfos_.log_file_stream_.rdstate() != std::ios_base::goodbit)
                {
                    std::cerr << termcolor::on_magenta << "can not create file :" << globale_loginfos_.log_file_ << \
                              "\nPlease make sure you have appropriate permission!" << std::endl;
                    getchar();
                    exit (1);
                }
                
                info_ptr_ = &globale_loginfos_;
            }
        public:
            ~EZlog() {}
            EZlog (const EZlog&) = delete;
            EZlog (EZlog&&) = delete;
            EZlog& operator= (const EZlog&) = delete;
            EZlog& operator= (EZlog&&) = delete;
            
            //use this function to access methods of EZlog
            //to avoid race conditions in multithreads this function will be called
            //in ezlog.cpp after the defination of all funs in EZlog
            //no use barrier here , maybe add it later
            EZlog& Instance()
            {
                return *this;
            }
            
            void log_info (const std::string& msg) //white
            {
                std::string str (current_time_YMDT() + "[INFO]   " + msg);
                
                if (Log_level::INFO >= LOG_LEVEL_THRES_)
                {
                    writeline2logfile (str);
                }
                
                writeline2console (str, TERM_COLOR::GREEN);
            }
            void log_debug (const std::string&msg) //cyan
            {
                std::string str (current_time_YMDT() + "[DEBUG]  " + msg);
                
                if (Log_level::DBUG >= LOG_LEVEL_THRES_)
                {
                    writeline2logfile (str);
                }
                
                writeline2console (str, TERM_COLOR::CYAN);
            }
            void log_warn (const std::string& msg) //yellow
            {
                std::string str (current_time_YMDT() + "[WARN]   " + msg);
                
                if (Log_level::WARN >= LOG_LEVEL_THRES_)
                {
                    writeline2logfile (str);
                }
                
                writeline2console (str, TERM_COLOR::YELLOW);
            }
            void log_error (const std::string&msg) //red
            {
                std::string str (current_time_YMDT() + "[ERROR]  " + msg);
                
                if (Log_level::ERR >= LOG_LEVEL_THRES_)
                {
                    writeline2logfile (str);
                }
                
                writeline2console (str, TERM_COLOR::RED);
            }
            void log_fatal (const std::string&msg) //on_read
            {
                std::string str (current_time_YMDT() + "[FATAL]  " + msg);
                
                if (Log_level::FATAL >= LOG_LEVEL_THRES_)
                {
                    writeline2logfile (str);
                }
                
                writeline2console (str, TERM_COLOR::ON_RED);
                getchar();
                exit (1);
            }
            
            static std::shared_ptr<Logstream> create_logstream (Log_level level = Log_level::INFO, const std::string suffix = "")
            {
                return std::shared_ptr<Logstream> (new Logstream (level, suffix));
            }
            
        private://hlep function
            void writeline2logfile (const std::string&msg, const std::string &endwith = "\n")
            {
                std::lock_guard<std::mutex> lk_gd (info_ptr_->log_file_mutex_);
                
                if (info_ptr_->log_file_stream_.rdstate() == std::ios_base::goodbit)
                {
                    info_ptr_->log_file_stream_ << msg << endwith << std::flush;
                }
                
                else
                {
                    writeline2console ("can not write to log file: " + info_ptr_->log_file_, TERM_COLOR::ON_MAGENTA);
                    //std::cout << termcolor::on_magenta << "can not write to log file:" << log_file_ << std::endl;
                    std::cout << termcolor::reset;
                };
            }
            enum class TERM_COLOR
            {
                GREY, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, ON_GREY, \
                ON_RED, ON_GREEN, ON_YELLOW, ON_BLUE, ON_MAGENTA, ON_CYAN, ON_WHITE
            };
            void writeline2console (const std::string&msg, TERM_COLOR color, const std::string &endwith = "\n")
            {
#ifndef NO_TERMINAL_DISP
                std::lock_guard<std::mutex> lk_gd (info_ptr_->console_mutex_);
                std::string msg_ = std::string ("[Ezlog] ") + msg;
                
                switch (color)
                {
                    case TERM_COLOR::GREY:
                        std::cout << termcolor::grey << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::RED:
                        std::cout << termcolor::red << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::GREEN:
                        std::cout << termcolor::green << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::YELLOW:
                        std::cout << termcolor::yellow << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::BLUE:
                        std::cout << termcolor::blue << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::MAGENTA:
                        std::cout << termcolor::magenta << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::CYAN:
                        std::cout << termcolor::cyan << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::WHITE:
                        std::cout << termcolor::white << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_GREY:
                        std::cout << termcolor::on_grey << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_RED:
                        std::cout << termcolor::on_red << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_GREEN:
                        std::cout << termcolor::on_green << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_YELLOW:
                        std::cout << termcolor::on_yellow << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_BLUE:
                        std::cout << termcolor::on_blue << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_MAGENTA:
                        std::cout << termcolor::on_magenta << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_CYAN:
                        std::cout << termcolor::on_cyan << msg_ << endwith;
                        break;
                        
                    case TERM_COLOR::ON_WHITE:
                        std::cout << termcolor::on_white << msg_ << endwith;
                        break;
                        
                    default:
                        std::cout << termcolor::underline << msg_ << endwith;
                        break;
                }
                
                std::cout << termcolor::reset;
                //console_mutex_.unlock();
#endif //NO_TERMINAL_DISP  
            }
        private:
            LogInfos* info_ptr_ = nullptr;
        public://a sub class
        
    };//class EZlog
    
    //utils for Logstream
    template<typename T>
    std::shared_ptr<Logstream> operator<< (std::shared_ptr<Logstream> ptr, const T &data)
    {
        *ptr << data;
        return ptr; // ptr's life just in one scope
    }
    
    
    inline std::string current_time_YMDT()
    {
        char datetime[99];
        time_t current_t = time (nullptr);
        struct tm current_time;
#if defined(_WIN32) || defined(_WIN64)
        localtime_s (&current_time, &current_t);
        sprintf_s (datetime, \
                   "%d-%02d-%02d %02d:%02d:%02d", \
                   1900 + current_time.tm_year, \
                   1 + current_time.tm_mon, \
                   current_time.tm_mday, \
                   current_time.tm_hour, \
                   current_time.tm_min, \
                   current_time.tm_sec);
#elif defined(__unix__) || defined(__unix) || defined(__APPLE__)
        localtime_r (&current_t, &current_time);
        sprintf (datetime, \
                 "%d-%02d-%02d %02d:%02d:%02d", \
                 1900 + current_time.tm_year, \
                 1 + current_time.tm_mon, \
                 current_time.tm_mday, \
                 current_time.tm_hour, \
                 current_time.tm_min, \
                 current_time.tm_sec);
#endif
        return std::string (datetime);
    }
    
    static EZlog ezlog_instance_g_;
    
    inline void Logstream::print_and_save_msg() const
    {
        switch (level_)
        {
            //str() will return the string which stores in ostringstream
            case Log_level::INFO:
                ezlog_instance_g_.log_info (str() + suffix_);
                break;
                
            case Log_level::DBUG:
                ezlog_instance_g_.log_debug (str() + suffix_);
                break;
                
            case Log_level::WARN:
                ezlog_instance_g_.log_warn (str() + suffix_);
                break;
                
            case Log_level::ERR:
                ezlog_instance_g_.log_error (str() + suffix_);
                break;
                
            case Log_level::FATAL:
                ezlog_instance_g_.log_fatal (str() + suffix_);
                break;
        }
    }
    
    inline std::string trim_time_str (const std::string &str, int type)
    {
        std::string s_;
        
        switch (type)
        {
            case 0:
                {
                    for (auto ch : str)
                    {
                        if (isdigit (ch)) { s_ += ch; }
                    }
                    
                    break;
                }
                
            case 1:
                {
                    for (auto ch : str)
                    {
                        if (isdigit (ch)) { s_ += ch; }
                        
                        else { s_ += '_'; }
                    }
                    
                    break;
                }
                
            default:
                break;
        }
        
        return s_;
    }
    
}//namespace




#endif //EZLOG_h_
