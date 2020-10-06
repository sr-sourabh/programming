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
    const char *target = "trash/7target.txt";
    const char *destination = "trash/7destination.txt";

    int targetFd = open(target, O_RDONLY);
    if(targetFd == -1){
        printf("Target: %s\n",strerror(errno));
    }

    int destinationFd = open(destination, O_WRONLY | O_CREAT| O_EXCL, 0644);
    if(destinationFd == -1){
        printf("Destination: %s\n",strerror(errno));
    }
    else{
        char buff[1];
        while(read(targetFd, buff, sizeof buff) > 0){
            write(destinationFd, buff, sizeof buff);
        }
        write(1, "File copied successfully...\n", 29);
    }

    close(destinationFd);
    close(targetFd);
}