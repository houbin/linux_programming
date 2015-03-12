#include <stdio.h>
#include <stdlib.h>

int test(int &a)
{
    a = 10000;
    return 0;
}

int main()
{
    int my = 0;

    test(my);

    printf("my is %d\n", my);

    return 0;
}
