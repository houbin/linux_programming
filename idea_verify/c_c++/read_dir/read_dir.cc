#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

int main()
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    dir = opendir("/tmp");

    chdir("/tmp");
    while((entry = readdir(dir)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            if ((strcmp(".", entry->d_name)) == 0
                || (strcmp("..", entry->d_name)) == 0)
            {
                continue;
            }

            string base_name("/temp/");
            base_name = base_name + entry->d_name + "/";
            cout << "dir: entry->d_name is " << base_name << endl;
        }
        else
        {
            string base_name("/temp/");
            base_name = base_name + entry->d_name;
            cout << "file: entry->d_name is " << base_name << endl;
        }
    }

    return 0;
}
