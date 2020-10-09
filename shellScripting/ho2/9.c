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
Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
*/


void main(int argc, char **argv, char **argp){
    signal(SIGINT, SIG_IGN);
    printf("Ignore signal\n");
    sleep(5);
    printf("\n");

     signal(SIGINT, SIG_DFL);
    printf("Reset signal action to default\n");
    sleep(5);
    printf("\n");
}