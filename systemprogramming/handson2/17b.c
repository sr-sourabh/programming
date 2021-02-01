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
Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
*/

void main(int argc, char **argv, char **argp){
    int fd[2];
    pipe(fd);

    if(!fork()){
        dup2(fd[1], 1);
        close(fd[0]);
        execl("/bin/ls", "ls", "-l", NULL);
    }
    else{
        sleep(0.1);
        close(fd[1]);
        dup2(fd[0], 0);
        execl("/usr/bin/wc", "wc", NULL);
    }
}