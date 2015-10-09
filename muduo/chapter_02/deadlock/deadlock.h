#ifndef DEADLOCK_H_
#define DEADLOCK_H_

#include <unistd.h>
#include <set>
#include "mutex.h"
#include "thread.h"
#include "inventory.h"
#include "request.h"

using namespace std;
using namespace util;

extern Inventory g_inventory;

class MyThread : public Thread
{
public:
    void* Entry()
    {
        Request *req = new Request;
        req->Process();
        delete req;

        return 0;
    }
};

#endif
