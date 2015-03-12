#include <stdio.h>
#include <stdlib.h>

struct Test
{
    int a;
};

int main()
{
    Test test;
    int len = sizeof(Test);
    printf("sizeof struct Test is %d\n", sizeof(Test));
    //char array[len] = {0};

    return 0;
}
