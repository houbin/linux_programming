#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <set>
#include "mutex.h"
#include "request.h"

using namespace std;
using namespace util;

class Inventory
{
private:
    Mutex mutex_;
    set<Request*> requests_;

public:
    Inventory() : mutex_("Inventory") {}
    void Add(Request *req);
    void Remove(Request *req);
    void PrintAll();
};

#endif
