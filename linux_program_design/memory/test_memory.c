#include <stdio.h>
#include <stdlib.h>

#define A_MEGABYTE (1024 * 1024)

int main()
{
    int i = 0;
    char *some_memory = NULL;

    for (i = 0; i < 10; i++)
    {
        some_memory = (char *)malloc(A_MEGABYTE);
        if (some_memory != NULL)
        {
            printf("alloc memory, ptr is %p\n", some_memory);
        }
    }

    return 0;
}
