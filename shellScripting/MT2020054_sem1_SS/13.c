#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>

void main(int argc, char *argv[]){
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    int retval = select(1, &rfds, NULL, NULL, &tv);

    if (retval == -1)
        printf("%s\n",strerror(errno));
    else if (retval)
        printf("Data is available now.\n");
    else
        printf("No data within ten seconds.\n");

}
