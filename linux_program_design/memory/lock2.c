#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int loop = 10;
    int file;

    while (loop-- > 0)
    {
        file = open("/tmp/LCK.test2", O_CREAT | O_EXCL | O_RDWR, 0644);
        if (file == -1)
        {
            printf("have already locked\n");
            sleep(3);
        }
        else
        {
            printf("%d - I have exclusive access\n", getpid());
            sleep(1);
            close(file);
            unlink("/tmp/LCK.test2");
            sleep(2);
        }
    }

    return 0;
}
