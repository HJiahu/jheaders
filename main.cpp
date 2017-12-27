#include<iostream>
#include"format.h"
#include"ezlog.h"
#include"filesystem.h"
#include"json.h"
#include"string_utils.h"
#include"xml_utils.h"
#include"filesystem.h"
#include"time_utils.h"
using namespace std;
namespace jh = jheaders;
using namespace rapidxml;

extern string xml_sample;


int main()
{
    jh::Timer timer;
    this_thread::sleep_for (chrono::seconds (2));
    timer.elapsed_milliseconds ("milli: ");
    system ("pause");
}