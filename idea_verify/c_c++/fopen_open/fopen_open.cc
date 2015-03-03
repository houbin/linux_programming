#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    FILE *file_handle_1;
    FILE *file_handle_2;

    file_handle_1 = fopen("./test", "rw");
    assert(file_handle_1 != NULL);

    file_handle_2 = fopen("./test", "rw");
    assert(file_handle_2 != NULL);

    int fd;
    fd = open("./test", O_RDWR);
    assert(fd != -1);

    return 0;
}
