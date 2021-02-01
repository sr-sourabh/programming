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
Write two programs so that both can communicate by FIFO -Use one way communication.
*/

void main(int argc, char **argv, char **argp){
    printf("1. Read\n2. Write\nEnter your choice:\n");
    int c;
    scanf("%d", &c);

    char * filename = "trash/20fifo";
    int fd;
    char buff[20];

    if(c==1){
        fd = open(filename, O_RDONLY);
        if(fd == -1){
            printf("%s\n",strerror(errno));
        }
        read(fd, buff, sizeof buff);
        printf("Read: %s\n", buff);
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