#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    char str_add[32] = "192.168.6.2";
    char str_port[32] = "1234";
    struct in_addr s;

    int ret = inet_pton(AF_INET, str_add, &s);
    if (ret != 1)
    {
        cout << "inet_pton error" << endl;
        return -1;
    }

    int port = atoi(str_port);

    struct in_addr temp;
    temp = s;

    printf("in_addr s is 0x%08x, port is %d\n", ntohl(s.s_addr), port);

    return 0;
}
