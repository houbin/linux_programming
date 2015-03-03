#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    time_t t;

    t = time(NULL);

    printf("ctime is %s\n", ctime(&t));

    return 0;
}
