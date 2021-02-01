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
Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
*/

void main(int argc, char **argv, char **argp){
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    if(!fork()){
        dup2(fd1[1], 1);
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        execl("/bin/ls", "ls", "-l", NULL);
    }
    else{
        if(!fork()){
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0], 0);
            dup2(fd2[1], 1);
            execl("/bin/grep", "grep", "^d", NULL);
        }
        else{
            close(fd1[1]);
            close(fd1[0]);
            close(fd2[1]);
            dup2(fd2[0], 0);
            execl("/usr/bin/wc", "wc", NULL);
        }
    }
}