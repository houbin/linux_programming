#include <map>
#include <iostream>
#include <time.h>

using namespace std;

#define TEST_COUNT 200000

int main()
{
    int del_count = 0;
    map<int, int> test;

    for (int i = 0; i < TEST_COUNT; i++)
    {
        test.insert(make_pair(i, i));
    }

    struct timeval before;
    gettimeofday(&before, NULL);

    map<int, int>::iterator iter = test.begin();
    while(iter != test.end())
    {
        if (iter->first % 2 == 0)
        {
            map<int, int>::iterator del_iter = iter;
            iter++;
            test.erase(del_iter);
            del_count ++;
        }
        else
        {
            iter++;
        }
    }

    struct timeval after;
    gettimeofday(&after, NULL);

    int cost_sec = (after.tv_usec < before.tv_usec) ? (after.tv_sec - before.tv_sec -1) : (after.tv_sec - before.tv_sec);
    int cost_usec = (after.tv_usec < before.tv_usec) ? (after.tv_usec + 1000000 - before.tv_usec) : (after.tv_usec - before.tv_usec);

    cout << "map del " << del_count << " in " << TEST_COUNT << " elements cost " << cost_sec << "." << cost_usec << " seconds" << endl;

    int count = 0;
    iter = test.begin();
    for ( ; iter != test.end(); iter++)
    {
        cout << "seq " << count << ", iter->first is " << iter->first << ", iter->second is " << iter->second << endl;
        count ++;
    }

    return 0;
}
