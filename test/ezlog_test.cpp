#include<jheaders/ezlog.h>
#include<gtest/gtest.h>
#include<string>

using namespace jheaders;
using namespace std;

const string print_str_{"This is a test string for ezlog.(no errors appear)"};

TEST (zelog, run_able)
{
    EZLOG (Log_level::INFO) << print_str_;
    EZLOG (Log_level::DBUG) << print_str_;
    EZLOG (Log_level::WARN) << print_str_;
    EZLOG (Log_level::ERR) << print_str_;
    //EZLOG (Log_level::FATAL) << print_str_;
    EZLOG_ (info) << print_str_;
    EZLOG_ (debug) << print_str_;
    EZLOG_ (warn) << print_str_;
    EZLOG_ (error) << print_str_;
}