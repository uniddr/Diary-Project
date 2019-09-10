#include <stdio.h>
#include <time.h>
#include<string.h>

int main()
{
    time_t timer;
    char rtime[26],time1[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(rtime,sizeof(rtime), "%d/%m/%Y-%H:%M", tm_info);
    strcpy(time1,rtime);


    return 0;
}
