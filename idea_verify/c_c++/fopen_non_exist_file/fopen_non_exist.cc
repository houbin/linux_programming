#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    string file_name="/tmp/test123456789";

    FILE *fp = NULL;
    fp = fopen(file_name.c_str(), "r");
    if (fp == NULL)
    {
        cout << "using \"r+\" flag, fopen non exist file error" << endl;
        return -1;
    }

    cout << "using \"r+\" flag, fopen non exist file ok" << endl;

    return 0;
}
