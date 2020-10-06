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
    const char *target = "trash/8dummy.txt";

    int targetFd = open(target, O_RDONLY);
    if(targetFd == -1){
        printf("%s\n",strerror(errno));
    }

    char buff[1];
    while(read(targetFd, buff, sizeof buff) > 0){
        write(1, buff, sizeof buff);
    }
    close(targetFd);
}