#ifndef EZLOG_H_
#define EZLOG_H_

//#define USE_TRADITION
#ifdef USE_TRADITION
    #include<jheaders/experiment/ezlog_tradition.h>
#else
    #include<jheaders/experiment/ezlog_header_only.h>
#endif // USE_TRADITION



#endif //EZLOG_h_
