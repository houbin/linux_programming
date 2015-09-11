#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *some_memory = NULL;
    
    some_memory = (char *)malloc(64);
    if (some_memory == NULL)
    {
        printf("malloc memory error");
        return -1;
    }

    int i = 0;
    while (1)
    {
        *(some_memory + i) = '\0';
        printf("assign %d = 0\n", i);
        i++;
    }

    return 0;
}
