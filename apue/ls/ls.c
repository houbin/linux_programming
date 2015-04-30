#include <apue.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "args too less\n");
        return -1;
    }

    DIR *dir = NULL;

    dir = opendir(argv[1]);
    if (dir == NULL)
    {
        printf("can't open dir, error msg %s\n", strerror(errno));
        return -1;
    }

    struct dirent *ent = NULL;
    while((ent = readdir(dir)) != NULL)
    {
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}
