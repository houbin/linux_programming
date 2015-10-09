#ifndef REQUEST_H_
#define REQUEST_H_

#include "mutex.h"

using namespace util;

class Request
{
private:
    Mutex mutex_;

public:
    Request() : mutex_("Request") {}
    ~Request();

    void Process();
    void Print();
};

#endif
