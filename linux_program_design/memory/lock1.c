#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int main()
{
    int file;
    
    file = open("/tmp/LCK.test", O_CREAT | O_EXCL | O_RDWR, 0444);
    if (file == -1)
    {
        perror("open LCK.test error");
        return -1;
    }

    printf("open LCK.test success\n");

    return 0;
}
