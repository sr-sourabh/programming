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

void main(int argc, char *argv[]){

    struct stat s;
    int retVal = stat(argv[1], &s);
    if(retVal == -1){
        printf("%s\n",strerror(errno));
    }
    printf("Mode value: %d\n", (s.st_mode & S_IFMT));

    if(S_ISREG(s.st_mode)){
        printf("Regular file\n");
    }
    else if(S_ISLNK(s.st_mode)){
        printf("Link file\n");
    }
    else if(S_ISDIR(s.st_mode)){
        printf("Directory file\n");
    }
    else if(S_ISCHR(s.st_mode)){
        printf("Char file\n");
    }
    else if(S_ISBLK(s.st_mode)){
        printf("Block file\n");
    }
    else if(S_ISFIFO(s.st_mode)){
        printf("Fifo file\n");
    }
    else if(S_ISSOCK(s.st_mode)){
        printf("Socket file\n");
    }

}
