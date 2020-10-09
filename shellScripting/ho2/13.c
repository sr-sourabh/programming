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
Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
*/

void handler(int sigid){
    switch(sigid){
        case SIGSTOP : printf("SIGSTOP handled\n"); exit(0); break;
        default : break;
    }
}

void main(int argc, char **argv, char **argp){
    struct sigaction newAction;
    newAction.sa_handler = handler;
    newAction.sa_flags = 0;

    if(!fork()){
        printf("Inside child, stopping parent with ppid: %d", getppid());
        kill(getppid(), SIGSTOP);
    }
    else{
        sigaction(SIGSTOP, &newAction, NULL);
        sleep(5);
    }
}