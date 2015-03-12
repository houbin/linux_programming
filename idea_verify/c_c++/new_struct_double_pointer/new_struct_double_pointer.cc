#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Test
{
    int a;
    int b;
};

int main()
{
    Test **test = new Test*[10];

    for (int i = 0; i < 10; i++)
    {
        test[i] = new Test;
        test[i]->a = i;
        test[i]->b = i;
    }

    for (int i = 0; i < 10; i++)
    {
        cout << "seq " << i << ", a is " << test[i]->a << ", b is " << test[i]->b << endl;
    }

    return 0;
}
