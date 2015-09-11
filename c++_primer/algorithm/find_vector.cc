#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    vector<int> my_vec;
    for (int i = 0; i < 100; i++)
    {
        my_vec.push_back(i);
    }

    int search_value = 142;
    vector<int>::const_iterator iter = find(my_vec.begin(), my_vec.end(), search_value);
    if (iter == my_vec.end())
    {
        cout << "can't find value " << search_value << endl;
        return -1;
    }

    cout << "find search value " << search_value << endl;

    return 0;
}
