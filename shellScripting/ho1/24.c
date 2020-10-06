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
        printf("Initial parent id: %d\n", getppid());
        sleep(5);
        printf("Final parent id: %d\n", getppid());
    }
    //parent
    else{
        printf("\n");
    }
}
//pstree -p -s  6897
//man prctl