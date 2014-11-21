#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        char temp[256] = {0};
        sprintf(temp, "./test.sh %d", i);
        system(temp);
    }

    return 0;
}
