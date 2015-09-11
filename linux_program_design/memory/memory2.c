#include <stdio.h>
#include <stdlib.h>

#define A_MEGABYTE (1024 * 1024)
#define PHY_MEM_MEGS 1024

int main()
{
    int i = 1;
    char *some_memory = NULL;

    for (i = 1; i < PHY_MEM_MEGS; i++)
    {
        some_memory = (char *)malloc(i * A_MEGABYTE);
        if (some_memory == NULL)
        {
            printf("malloc memory error, size %dM\n", i);
            exit(-1);
        }

        printf("malloc memory ok, size %dM, ptr is %p\n", i, some_memory);
    }

    return 0;
}
