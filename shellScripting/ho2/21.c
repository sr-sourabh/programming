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
Write two programs so that both can communicate by FIFO -Use two way communications.
*/

void main(int argc, char **argv, char **argp){
    printf("1. Read first then write\n2. Write first then read\nEnter your choice:\n");
    int c;
    scanf("%d", &c);

    char * filename1 = "trash/21fifo1";
    char * filename2 = "trash/21fifo2";
    int fd1, fd2;
    char buff[20];

    if(c==1){
        fd1 = open(filename1, O_RDONLY);
        fd2 = open(filename2, O_WRONLY);
        if(fd1 == -1 || fd2 == -1){
            printf("%s\n",strerror(errno));
        }
        read(fd1, buff, sizeof buff);
        printf("Read: %s\n", buff);

        printf("Enter a message to send: ");
        scanf("%s", buff);
        write(fd2, buff, sizeof(buff));
    }
    else if(c==2){
        fd1 = open(filename1, O_WRONLY);
        fd2 = open(filename2, O_RDONLY);
        if(fd1 == -1 || fd2 == -1){
            printf("%s\n",strerror(errno));
        }
        printf("Enter a message to send: ");
        scanf("%s", buff);
        write(fd1, buff, sizeof(buff));

        read(fd2, buff, sizeof buff);
        printf("Read: %s\n", buff);
    }
    close(fd1);
    close(fd2);
}