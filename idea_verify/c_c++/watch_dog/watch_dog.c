#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define CHECK_DOG_INTERVAL 2
#define FEED_DOG_INTERVAL 1

int main()
{
    pid_t son_pid;

    while(true)
    {
        son_pid = fork();
        if (son_pid > 0)
        {
            bool dog_status = true;
            while(dog_status)
            {
                sleep(CHECK_DOG_INTERVAL);
                int fd = open("/tmp/temp_dog.txt", O_RDONLY);
                if (fd <= 0)
                {
                    perror("fd open error");
                    return -1;
                }

                char buffer[32] = {0};
                read(fd, buffer, 31);
                int food = atoi(buffer);
                printf("parent: check dog, food is %d\n", food);
                if (food > 0)
                {
                    char z = 0;
                    write(fd, &z, 1);
                    close(fd);
                    printf("parent: check dog ok\n", food);
                }
                else
                {
                    printf("parent: check dog error\n", food);
                    //kill(son_pid, 9);
                }
            }
        }
        else
        {
            while(true)
            {
                assert(1 == 0);
                /* son process */
                sleep(FEED_DOG_INTERVAL);

                int fd = open("/tmp/temp_dog.txt", O_WRONLY);
                if (fd < 0)
                {
                    perror("open error");
                    return -1;
                }

                char food = '0';
                printf("son: feed dog\n");
                write(fd, &food, 1);
                close(fd);
            }
        }
    }

    return 0;
}
