#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main()
{
    char buffer[1024] = {0};

    char *temp = realpath("./", buffer);
    cout << "realpath return " << buffer << endl;

    memset(buffer, 0, 1024);
    getcwd(buffer, 1023);
    cout << "getcwd return " << buffer << endl;

    memset(buffer, 0, 1024);
    int cnt = readlink("/proc/self/exe", buffer, 1023);
    if (cnt < 0 || cnt >= 1023)
    {
        cout << "readlink error" << endl;
        return -1;
    }

    int i = 0;
    for (i = cnt; i > 0; i--)
    {
        if (buffer[i] == '/')
        {
            buffer[i] = 0;
            break;
        }
    }

    cout << "readlink ret " << buffer << endl;

    return 0;
}
