#include <string>
#include <iostream>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define server_port 5555

using namespace std;

int fd = -1;
bool connected = false;

void *send_func(void *arg)
{
    char buffer[32] = "hello from select client";

    while (true)
    {
        if (connected)
        {
            int ret = send(fd, buffer, strlen(buffer), MSG_NOSIGNAL);
            if (ret != strlen(buffer))
            {
                perror("send error");
                printf("fd %d\n", fd);
            }
        }

        sleep(2);
    }

    return 0;
}

int main()
{
    // create a thread
    //
    pthread_t t;
    pthread_create(&t, NULL, send_func, NULL);

    int ret = 0;
    struct sockaddr_in server_addr;
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(server_port);

    socklen_t len = sizeof(server_addr);

    struct timeval tv = {0, 0};

    while (true)
    {
        while (!connected)
        {
            fd = socket(AF_INET, SOCK_STREAM, 0);
            if (fd < 0)
            {
                perror("create socket error");
                return -1;
            }

            ret = connect(fd, (struct sockaddr*)&server_addr, len);
            if (ret < 0)
            {
                cout << "connect error, sleep 5s" << endl;
                connected = false;
                sleep(5);
                continue;
            }

            connected = true;
        }
        
        fd_set read_set, error_set;
        FD_ZERO(&read_set);
        FD_ZERO(&error_set);
        FD_SET(fd, &read_set);
        FD_SET(fd, &error_set);

        ret = select(fd + 1, &read_set, NULL, &error_set, NULL);
        if (ret == -1)
        {
            perror("select error");
        }
        else if (ret)
        {
            if (FD_ISSET(fd, &read_set))
            {
                char buffer[32] = {0};
                int ret = recv(fd, buffer, 32, 0);
                if (ret > 0)
                {
                    string msg(buffer);
                    cout << "aaaaaa select recv msg " << msg << endl;
                }
                else if (ret == 0)
                {
                    cout << "peer has performed an orderly showdown, fd is " << fd << endl;
                    close(fd);
                    fd = -1;
                    connected = false;
                }
                else
                {
                    cout << "fd " << fd << " recv error, error msg " << strerror(errno) << endl;
                    close(fd);
                    fd = -1;
                    connected = false;
                }
            }
            else if (FD_ISSET(fd, &error_set))
            {
                cout << "fd " << fd << " is error in error_set" << endl;
                close(fd);
                fd = -1;
                connected = false;
            }
        }
        else
        {
            cout << "select ret is 0" << endl;
        }
    }
}

