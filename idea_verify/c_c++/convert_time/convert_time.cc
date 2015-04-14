#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void print_time_t(time_t *t, char *buffer)
{
    struct tm tm;
    gmtime_r(t, &tm);
    strftime(buffer, 32, "%Y%m%d-%H%M%S", &tm);

    return;
}

int main(int argc, char *argv[])
{
    struct tm arg_time = {0};
    struct tm *temp_time = NULL;
    time_t time_sec = 0;

    time_sec = time(NULL);
    char buffer[32] = {0};
    print_time_t(&time_sec, buffer);
    printf("time of now is %s\n", buffer);
    //cout << "time of now is " << buffer << endl;

    char *arg1_ch = argv[1];
    char *arg2_ch = argv[2];
    time_t arg1_int = (time_t)atoi(arg1_ch);
    time_t arg2_int = (time_t)atoi(arg2_ch);

    memset(buffer, 0, 32);
    print_time_t(&arg1_int, buffer);
    cout << "time of arg1 is " << buffer << endl;

    memset(buffer, 0, 32);
    print_time_t(&arg2_int, buffer);
    cout << "time of arg2 is " << buffer << endl;

    return 0;
}
