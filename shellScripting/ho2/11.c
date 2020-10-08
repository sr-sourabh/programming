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


void main(int argc, char **argv, char **argp){
    struct sigaction newAction;
    newAction.sa_handler = SIG_IGN;
    newAction.sa_flags = 0;

    sigaction(SIGINT, &newAction, NULL);
    printf("Ignore signal\n");
    sleep(5);
    printf("\n");

    newAction.sa_handler = SIG_DFL;
    sigaction(SIGINT, &newAction, NULL);
    printf("Reset signal action to default\n");
    sleep(5);
    printf("\n");
}