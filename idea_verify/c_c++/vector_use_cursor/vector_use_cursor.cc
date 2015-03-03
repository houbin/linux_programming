#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> test;

    test.resize(30, 0);

    int i = 10;
    for (i; i >= 0; i--)
    {
        test[i] = i;
    }

    test[17] = 17;
    test[19] = 19;

    int j = 0;
    while (j < 30)
    {
        if (j %3 == 0)
        {
            j++;
            continue;
        }

        cout << "test " << j << " is " << test[j] << endl;
        j++;
    }

    cout << "scan" << endl;

    int seq = 0;
    vector<int>::iterator iter = test.begin();
    for (iter; iter != test.end(); iter++)
    {
        cout << "seq " << seq++ << ": value is " << *iter << endl;
    }

    return 0;
}

