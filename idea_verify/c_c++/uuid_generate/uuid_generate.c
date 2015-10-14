#include <stdio.h>
#include <uuid/uuid.h>

int main()
{
    uuid_t uuid;

    uuid_generate(uuid);

    int i = 0;
    for(; i < 16; i++)
    {
        printf("%02d ", uuid[i]);
    }

    printf("\n");

    return 0;
}
