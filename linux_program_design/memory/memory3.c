#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define A_K (1024)

int main()
{
    int i = 0;
    int count = 0;
    char *some_memory = NULL;

    while (true)
    {
        for (i = 0; i < 1024; i++)
        {
            some_memory = (char *)malloc(A_K);
            if (some_memory != NULL)
            {
                sprintf(some_memory, "hello world");
            }
            else
            {
                exit(-1);
            }
        }

        count++;
        printf("malloc %d megabyte, ptr is %p\n", count, some_memory);
    }

    return 0;
}
