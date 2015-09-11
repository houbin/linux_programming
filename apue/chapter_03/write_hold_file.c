#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char first_write[] = "abcdefghijklmn";
char second_write[] = "ABCDEFGHIJKLMN";

int main()
{
    int ret = 0;
    int fd = 0;

    fd = open("./test.txt", O_WRONLY | O_CREAT);
    if (fd == 0)
    {
        printf("open file error\n");
        return -1;
    }

    ret = lseek(fd, 0, SEEK_SET);
    if (ret != 0)
    {
        perror("lseek error");
        return -1;
    }


    ret = write(fd, first_write, sizeof(first_write));
    if (ret != sizeof(first_write))
    {
        perror("write first error");
        return -1;
    }

    ret = lseek(fd, 16284, SEEK_SET);
    if (ret != 16284)
    {
        perror("lseek 16284 error");
        return -1;
    }

    ret = write(fd, second_write, sizeof(second_write));
    if (ret != sizeof(second_write))
    {
        perror("write second error");
        return -1;
    }

    close(fd);
    return -1;
}
