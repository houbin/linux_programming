#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "you must input search value" << endl;
        return -1;
    }

    vector<int> test;

    test.push_back(1);
    test.push_back(100);
    test.push_back(200);
    test.push_back(100);
    test.push_back(1);
    test.push_back(200);
    test.push_back(5);

    int search_value = atoi(argv[1]);
    cout << "search value is " << search_value << endl;

    int my_count = count(test.begin(), test.end(), search_value);
    cout << "my_count is " << my_count << endl;

    return 0;
}
