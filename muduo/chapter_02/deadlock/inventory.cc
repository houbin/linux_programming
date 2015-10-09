#include <stdio.h>
#include <unistd.h>
#include "inventory.h"

void Inventory::Add(Request *req)
{
    printf("Add: inventory lock\n");
    Mutex::Locker lock(mutex_);
    requests_.insert(req);
    printf("Add: inventory unlock\n");
}

void Inventory::Remove(Request *req)
{
    Mutex::Locker lock(mutex_);
    requests_.erase(req);
}

void Inventory::PrintAll()
{
    printf("PrintAll: inventory lock\n");
    Mutex::Locker lock(mutex_);
    sleep(1);

    set<Request*>::iterator iter = requests_.begin();
    for(; iter != requests_.end(); iter++)
    {
        (*iter)->Print();
    }
    printf("PrintAll: inventory unlock\n");
}
