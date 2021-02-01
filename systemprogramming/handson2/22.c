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
#include<time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include<sched.h>
#include <stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<pthread.h>

/*
Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO
*/

void main(int argc, char **argv, char **argp){


    printf("1. Read\n2. Write\nEnter your choice:\n");
    int c;
    scanf("%d", &c);

    char * filename = "trash/22fifo";
    int fd;
    char buff[20];

    if(c==1){
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            printf("%s\n",strerror(errno));
        }

        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;

        int retval = select(fd+1, &rfds, NULL, NULL, &tv);

        if (retval == -1)
            printf("%s\n",strerror(errno));
        else if (retval){
            read(fd, buff, sizeof buff);
            printf("Read: %s\n", buff);
        }
        else
            printf("No data within ten seconds.\n");

    }
    else if(c==2){
        fd = open(filename, O_WRONLY);
        if(fd == -1){
            printf("%s\n",strerror(errno));
        }
        printf("Enter a message to send: ");
        scanf("%s", buff);
        write(fd, buff, sizeof(buff));
    }
    close(fd);
}