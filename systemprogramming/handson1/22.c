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
    int fd = open("trash/22.txt", O_RDWR | O_CREAT, 0644);
    //child
    if(!fork()){
        write(fd, "Child\n", 6);
    }
    //parent
    else{
        write(fd, "Parent\n", 7);
    }
}
