#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>

void main(){
    const char * filename = "./trash/3dummyfile.txt";
    int fd = creat(filename, 0666);
    if(fd == -1){
        printf("%s\n",strerror(errno));
    }
    else{
        printf("File descriptor: %d \n", fd);
    }
}