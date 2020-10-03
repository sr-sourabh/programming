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
#include<stdlib.h>


void main(int argc, char **argv, char **argp){
    int pid = fork();
    //child
    if(pid == 0){
        printf("Child running...");
        exit(0);
    }
    //parent
    else{
        printf("Parent going to sleep...\n");
        sleep(5);
        printf("Parent is awake...\n");
    }
}

//ps aux | grep 'Z' or simply do ps
