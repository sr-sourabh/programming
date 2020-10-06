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
    const char *file = "./trash/4dummy.txt";
    int fd = open(file, O_RDWR | O_EXCL);
    if(fd == -1){
        printf("%s\n",strerror(errno));
    }
    else{
        printf("File opened in read write mode \n");
    }

}