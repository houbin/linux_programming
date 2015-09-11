#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1234);

    printf("addr is %d\n", addr.sin_addr.s_addr);

    char *temp = inet_ntoa(addr.sin_addr);

    printf("temp is %s\n", temp);

    return 0;
}
