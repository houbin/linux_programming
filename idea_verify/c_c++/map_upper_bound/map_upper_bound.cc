#include <stdio.h>
#include <map>

using namespace std;

int main()
{
    map<int, int> test;

    for (int i = 0; i < 100; i++)
    {
        test.insert(make_pair(i, i));
    }

    {
        map<int, int>::iterator iter = test.upper_bound(101);
        if (iter == test.end())
        {
            printf("get 101 upper bound reach to end\n");
        }
        else
        {
            printf("get 101 upper bound ok, first is %d, second is %d\n", iter->first, iter->second);
        }
    }

    {
        map<int, int>::iterator iter = test.upper_bound(5);
        if (iter == test.end())
        {
            printf("get 5 upper bound error\n");
            return -1;
        }

        printf("get 5 upper bound ok, first is %d, second is %d\n", iter->first, iter->second);
    }

    {
        map<int, int>::iterator iter = test.lower_bound(5);
        if (iter == test.end())
        {
            printf("get 5 lower bound error\n");
            return -1;
        }

        printf("get 5 lower bound ok, first is %d, second is %d\n", iter->first, iter->second);
    }

    return 0;
}
