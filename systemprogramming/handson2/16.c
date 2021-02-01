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
Write a program to send and receive data from parent to child vice versa. Use two way
communication.
*/

void main(int argc, char **argv, char **argp){
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if(!fork()){
        //close write end of the pipe as we only want to read in child process
        close(fd1[1]);
        close(fd2[0]);

        sleep(0.1);
        char buff[19];
        read(fd1[0], buff, 19);
        printf("Data from parent: %s", buff);
        close(fd1[0]);

        write(fd2[1], "Hello from child\n", 18);
        close(fd2[1]);

    }
    else{
        //close read end as we only want to write in parent process
        close(fd1[0]);
        close(fd2[1]);

        write(fd1[1], "Hello from parent\n", 19);
        close(fd1[1]);

        char buff[18];
        read(fd2[0], buff, 18);
        printf("Data from child: %s", buff);
        close(fd2[0]);
    }
}