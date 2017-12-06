//#include<jheaders/ezlog.h>
//#include<gtest/gtest.h>
//#include<string>
//
//using namespace jheaders;
//using namespace std;
//
//const string print_str_{"This is a test string for ezlog.(no errors appear)"};
//
//TEST (EZlog, runable)
//{
//    //for (int i = 0; i < 99; i++)
//    {
//        EZLOG (Log_level::INFO) << print_str_;
//        EZLOG (Log_level::DBUG) << print_str_;
//        EZLOG (Log_level::WARN) << print_str_;
//        EZLOG (Log_level::ERR) << print_str_;
//        //EZLOG (Log_level::FATAL) << print_str_;
//        EZLOG_ (info) << print_str_;
//        EZLOG_ (debug) << print_str_;
//        EZLOG_ (warn) << print_str_;
//        EZLOG_ (error) << print_str_;
//        //exit (1);
//    }
//}

#include<jheaders/ezlog.h>
#include<string>
#include"catch.h"
using namespace jheaders;
using namespace std;
const string print_str_{ "This is a test string for ezlog.(no errors appear)" };
TEST_CASE ("test ezlog runable")
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