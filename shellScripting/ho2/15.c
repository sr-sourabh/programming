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
Write a simple program to send some data from parent to the child process.
*/

void main(int argc, char **argv, char **argp){
    int fd[2];
    pipe(fd);
    if(!fork()){
        //close write end of the pipe as we only want to read in child process
        close(fd[1]);
        sleep(0.1);
        char buff[6];
        read(fd[0], buff, 6);
        printf("Data from parent: %s", buff);
        close(fd[0]);
    }
    else{
        //close read end as we only want to write in parent process
        close(fd[0]);
        write(fd[1], "Hello\n", 6);
        close(fd[1]);
        sleep(0.2);
    }
}