#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    int test[] = {1, 2, 3, 100, 50, 32, 142, 123};

    int search_value = 142;
    int *iter = find(test, test + 8, search_value);
    if (iter == test + 8)
    {
        cout << "can't find value " << search_value << endl;
        return -1;
    }

    cout << "find search value " << *iter << endl;

    return 0;
}
