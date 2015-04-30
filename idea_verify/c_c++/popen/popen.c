#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = NULL;
    char buffer[1024] = {0};
    char result_buffer[2048] = {0};

    snprintf(buffer, 1024, "./test.sh &");

    fp = popen(buffer, "r");
    if (fp == NULL)
    {
        perror("popen error");
        return -1;
    }

    printf("fgets start\n");
    while(fgets(result_buffer, sizeof(result_buffer), fp) != NULL)
    {
        printf("result is %s\n", result_buffer);
    }
    printf("fgets end\n");
    
    int rc = pclose(fp);
    if (rc == -1)
    {
        perror("pclose fp error");
        return -1;
    }
    else
    {
        printf("进程结束状态【%d】命令返回值【%d】\r\n", rc, WEXITSTATUS(rc));
    }

    return 0;
}
