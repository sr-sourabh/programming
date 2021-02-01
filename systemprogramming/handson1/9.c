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
    const char * file = "9.c";

    int fd = open(file, O_RDONLY);
    if(fd == -1){
        printf("%s\n",strerror(errno));
    }

    struct stat fileInfo;
    int retVal = fstat(fd, &fileInfo);
    if(retVal == -1){
        printf("%s\n",strerror(errno));
    }

    printf("Inode number: %ld \n", fileInfo.st_ino);
    printf("Number of hardlinks: %ld \n", fileInfo.st_nlink);
    printf("Uid: %d \n", fileInfo.st_uid);
    printf("Gid: %d \n", fileInfo.st_gid);
    printf("Size: %ld \n", fileInfo.st_size);
    printf("Block size: %ld \n", fileInfo.st_blksize);
    printf("Number of blocks: %ld \n", fileInfo.st_blocks);
    printf("Time of last access: %ld \n", fileInfo.st_atim);
    printf("Time of last modification: %ld \n", fileInfo.st_mtim);
    printf("Time of last change: %ld \n", fileInfo.st_ctim);

    close(fd);

}