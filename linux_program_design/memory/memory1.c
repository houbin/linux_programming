#include <stdio.h>
#include <stdlib.h>

#define A_MEGABYTE (1024 * 1024)

int main()
{
    char *some_memory = NULL;

    some_memory = malloc(A_MEGABYTE);
    if (some_memory == NULL)
    {
        printf("malloc memory error");
        exit(-1);
    }

    sprintf(some_memory, "%s\n", "hello world");
    printf("%s", some_memory);

    exit(0);
}
