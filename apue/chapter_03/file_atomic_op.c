#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define WRITE_LENGTH 10
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("count of argument less than 2\n");
        return -1;
    }

    int fd = 0;

    fd = open("./file_atomic.txt", O_CREAT | O_RDWR , S_IRWXU);
    if (fd < 0)
    {
        perror("open file error");
        return -1;
    }

    lseek(fd, 0, SEEK_END);

    sleep(2);

    char buffer[WRITE_LENGTH];
    int i = 0;
    for(; i < WRITE_LENGTH; i++)
        buffer[i] = *argv[1];
    
    int ret = write(fd, buffer, WRITE_LENGTH);
    if (ret != WRITE_LENGTH)
    {
        perror("write error");
        return -1;
    }

    ret = write(fd, buffer, WRITE_LENGTH);
    if (ret != WRITE_LENGTH)
    {
        perror("write again error");
        return -1;
    }

    close(fd);

    return 0;
}
