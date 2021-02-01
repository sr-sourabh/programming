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
Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
*/

void main(int argc, char **argv, char **argp){
    int fd[2];
    pipe(fd);

    write(fd[1], "Hello\n", 6);
    char buff[6];
    read(fd[0], buff, 6);
    printf("Read: %s", buff);

    close(fd[0]);
    close(fd[1]);
}