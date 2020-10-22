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

void handler(int sigid){
    switch(sigid){
        case SIGINT : printf("\nInside SIGINT\nHandling...\n"); sleep(30); break;
        case SIGFPE : printf("\nInside SIGFPE\nHandling...\n");  break;
        default : break;
    }
}

void main(int argc, char **argv, char **argp){

    signal(SIGINT, handler);  // ctrl + c
    signal(SIGFPE, handler);
    printf("Starting...\n");
    sleep(5);
    printf("Back to main...\n");

}
