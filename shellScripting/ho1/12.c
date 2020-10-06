#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>

void main(int argc, char *argv[]){
    int fd1 = open("11.c", O_RDONLY);
    int fd2 = open("11.c", O_WRONLY);

    if((fcntl(fd1, F_GETFL) & O_ACCMODE)  == O_RDONLY){
        printf("Fd1 is Read only\n");
    }
    if((fcntl(fd2, F_GETFL) & O_ACCMODE) == O_WRONLY){
        printf("Fd2 is Write Only\n");
    }

    close(fd1);
    close(fd2);
}