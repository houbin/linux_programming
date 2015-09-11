#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
    vector<string> test;
    for(int i = 0; i < 100; i++)
    {
        char buffer[16] = {0};
        sprintf(buffer, "%d", i);
        string temp(buffer);
        test.push_back(temp);
    }

    string sum = accumulate(test.begin(), test.end(), string(""));

    cout << "sum is " << sum << endl; 

    return 0;
}
