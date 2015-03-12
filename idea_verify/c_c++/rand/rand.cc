#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    
    for (; i < 100; i++)
    {
        int a = rand() % 7200;

        printf("rand number is %d\n", a);
    }

    return 0;
}
