#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    int fd = 0;
    int ret = 0;
    char cmdline_path[64] = {0};
    char cmdline[256] = {0};
    char exe_path[128] = {0};

    if (argc != 2)
    {
        printf("wrong parameter\n");
        return -1;
    }

    snprintf(cmdline_path, 63, "/proc/%s/cmdline", argv[1]);

    fd = open(cmdline_path, O_RDONLY);
    if (fd < 0)
    {
        perror("open fd error");
        return -1;
    }

    ret = read(fd, cmdline, 253);
    if (ret < 0)
    {
        perror("read error");
        return -1;
    }
    
    char process_path[64] = {0};
    snprintf()

    int offset = 0;
    string sum;
    while (offset < ret)
    {
        char *start = &(cmdline[offset]);

        string temp(start);
        sum += temp;
        sum += " ";

        offset += temp.size() + 1;
    }
    close(fd);
    
    printf("ret %d, cmdline %s\n", ret, cmdline);
    printf("sum is %s\n", sum.c_str());

    return 0;
}
