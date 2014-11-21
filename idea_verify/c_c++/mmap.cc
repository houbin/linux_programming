#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int file;
    int *addr = NULL;
    int len = 1024;
    FILE *f;
/*
    f = fopen("./mmap.txt","w+"); 
    int i = 0;
    for (i = 0; i < len; i++)
    {
        fwrite(&i, sizeof(int), 1, f);
    }
    fclose(f);
    return 0;
    */
    
    file = open("./mmap.txt", O_RDWR);
    if (file == -1)
    {
        printf("open failed\n");
        return -1;
    }
    int i = 0;
    int j = 0;
    for (i = 0; i < len; i++)
    {
        write(file, &j, sizeof(int));
    }

    lseek(file, 0, SEEK_SET);

    addr = (int *)mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);
    if (addr == NULL)
    {
        printf("mmap failed\n");
        return -1;
    }

    addr[3] = 123;
    addr[7] = 123;
    addr[10] = 234;

//    munmap(addr, len);
    exit(0);
}
