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
#include <map>

#define server_port 16000

#define BACKLOG 10
using namespace std;

int fds[BACKLOG];

int conn_amount = 0;

struct Connection
{
    string client_ip;
    int client_port;
};

map<int, Connection> all_connections_by_fd;


int main()
{
    int ret = 0;
    int yes = 1;
    int listen_fd = 0;
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    socklen_t len = sizeof(server_addr);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        perror("create socket error");
        return -1;
    }

    // set reuse option
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("set reuse error");
        return -1;
    }
    
    ret = bind(listen_fd, (struct sockaddr*)&server_addr, len);
    if (ret < 0)
    {
        perror("bind socket error");
        return -1;
    }

    ret = listen(listen_fd, BACKLOG);
    if (ret < 0)
    {
        perror("listen fd error");
        return -1;
    }

    int max_socket = listen_fd;

    while (true)
    {
        fd_set read_set, error_set;
        FD_ZERO(&read_set);
        FD_ZERO(&error_set);

        struct timeval tv = {30, 0};

        FD_SET(listen_fd, &read_set);

        map<int, Connection>::iterator iter = all_connections_by_fd.begin();
        for(; iter != all_connections_by_fd.end(); iter++)
        {
            FD_SET(iter->first, &read_set);
        }

        ret = select(max_socket + 1, &read_set, NULL, NULL, &tv);
        if (ret < 0)
        {
            perror("select error");
            break;
        }
        else if (ret == 0)
        {
            cout << "select timeout" << endl;
            continue;
        }

        map<int, Connection>::iterator iter_2 = all_connections_by_fd.begin();
        while (iter_2 != all_connections_by_fd.end())
        {
            if (FD_ISSET(iter_2->first, &read_set))
            {
                Connection temp= iter_2->second;

                cout << "read_set: client ip " << temp.client_ip << ", client port " << temp.client_port << endl;

                char buffer[32] = {0};
                ret = recv(iter_2->first, buffer, 32, 0);
                if (ret <= 0)
                {
                    cout  << "client has performed an orderly shutdown" << endl;
                    iter_2++;
                    close(iter_2->first);
                    all_connections_by_fd.erase(iter_2->first);
                    continue;
                }
                else
                {
                    string msg(buffer);
                    cout << "client recv " << msg << endl;

                    // send back
                    char back_msg[32] = "hello from select server";
                    ret = send(iter_2->first, back_msg, strlen(back_msg), 0);
                    if (ret != strlen(back_msg))
                    {
                        cout << "client send back error" << endl;
                        iter_2++;
                        all_connections_by_fd.erase(iter_2->first);
                    }
                    else
                    {
                        iter_2++;
                    }
                }
            }
        }

        if (FD_ISSET(listen_fd, &read_set))
        {
            struct sockaddr_in client_addr;
            memset(&client_addr, 0, sizeof(client_addr));
            socklen_t client_len = sizeof(client_addr);

            int sock = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
            if (sock != -1)
            {
                Connection temp;
                temp.client_ip.assign(inet_ntoa(client_addr.sin_addr));
                temp.client_port = ntohs(client_addr.sin_port);
                all_connections_by_fd.insert(make_pair(sock, temp));
                cout << "accept client, client ip " << temp.client_ip << ", client port " << temp.client_port << endl;

                if (sock > max_socket)
                    max_socket = sock;
            }
            else
            {
                perror("accept");
                continue;
            }
        }
    }


    return 0;
}
