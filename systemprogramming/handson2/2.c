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

/*
Write a program to print the system resource limits. Use getrlimit system call.
*/

void main(int argc, char **argv, char **argp){

    struct rlimit limit;
    getrlimit(RLIMIT_NICE, &limit);
    printf("RLIMIT_NICE soft limit: %lu\nRLIMIT_NICE hard limit: %lu\n", limit.rlim_cur, limit.rlim_max);

}
