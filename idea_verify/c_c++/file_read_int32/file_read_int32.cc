#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    int ret;
    char temp[32] = {0};
    FILE *file;
    int count = 0;

    file = fopen("./count", "r");

    ret = fread(temp, 1, 32, file);
    cout << "ret is " << ret << endl;

    for (int i = 0; i < ret; i++)
    {
        int a = 0;
        a = temp[i];
        cout << a << endl;
    }

    count = atoi(temp);
    cout << "count is " << count << endl;
    
    return 0;
}
