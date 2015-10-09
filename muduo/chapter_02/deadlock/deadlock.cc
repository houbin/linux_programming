#include "deadlock.h"

Inventory g_inventory;

int main()
{
    MyThread my_thread;
    my_thread.Create();

    usleep(500 * 1000);
    g_inventory.PrintAll();

    my_thread.Join();

    return 0;
}
