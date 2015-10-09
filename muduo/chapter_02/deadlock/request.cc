#include <stdio.h>
#include "request.h"
#include "deadlock.h"

void Request::Process()
{
    printf("Process: request lock\n");
    Mutex::Locker lock(mutex_);
    g_inventory.Add(this);
    printf("Process: request unlock\n");
}

Request::~Request()
{
    printf("~Request: request lock\n");
    Mutex::Locker lock(mutex_);
    sleep(1);
    g_inventory.Remove(this);
    printf("~Request: request unlock\n");
}

void Request::Print()
{
    printf("Print: request lock\n");
    Mutex::Locker lock(mutex_);
    printf("Print: request unlock\n");
}
