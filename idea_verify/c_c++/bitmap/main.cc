#include <iostream>
#include "bitmapper.h"

using namespace std;
using namespace util;

int main()
{
    bitmapper bitmap(128);

    int i = 0;
    for (i = 0; i < 10; i++)
    {
        bitmap.set(i);
    }

    bitmap.clear(3);
    bitmap.clear(7);

    for(i = 0; i < 10; i++)
    {
        int temp = bitmap.get_free_bit();
        cout << "get free bit is " << temp << endl;
        bitmap.set(temp);
    }

    bitmapper bitmap_2(64);
    for (i = 0; i < 1000; i++)
    {
        int temp = bitmap_2.get_free_bit();
        cout << "bitmap get free bit " << temp << endl;
        if (temp >= 0)
        {
            bitmap_2.set(temp);
            cout << "this is valid" << endl;
        }
        else
        {
            cout << "this is invalid" << endl;
            break;
        }
    }

    return 0;
}
