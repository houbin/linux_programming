#include "../apue.h"

int main()
{
    printf("hello world from process id %d, uid %d, gid %d\n", getpid(), getuid(), getgid());

    return 0;
}
