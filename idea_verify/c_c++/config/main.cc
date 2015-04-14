#include <stdio.h>
#include <string.h>
#include "config.h"
#include <iostream>

using namespace std;

int main()
{
    Config *config = NULL;

    config = new Config("./test.conf");

    string test_1 = "houbin";
    int test_2 = 0;
    double test_3 = 0;

    test_1 = config->Read("test_1", test_1);
    test_2 = config->Read("test_2", test_2);
    test_3 = config->Read("test_3", test_3);

    cout << "test_1 is " << test_1 << ", test_2 is " << test_2 << ", test_3 is " << test_3 << endl;

    return 0;
}
