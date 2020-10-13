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
Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
*/

void main(int argc, char **argv, char **argp){

    printf( "Size of the pipe: %ld\nMaximum number of files can be opened within a process: %ld\n",
            pathconf(".", _PC_PIPE_BUF), sysconf(_SC_OPEN_MAX));

}