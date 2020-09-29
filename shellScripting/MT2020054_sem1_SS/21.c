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


void main(int argc, char **argv, char **argp){
    //child
    if(!fork()){
        printf("Child processId: %d\n", getpid());
    }
    //parent
    else{
        printf("Parent processId: %d\n", getpid());
    }
}
