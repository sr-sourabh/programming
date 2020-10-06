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
    int fd1 = open("trash/11dummy.txt", O_RDWR);
    int fd2 = dup(fd1);
    int fd3 = dup2(fd2, 22);
    int fd4 = fcntl(fd3, F_DUPFD);

    printf("Seek fd1: %ld\n", lseek(fd1, 0, SEEK_END));
    printf("Seek fd2: %ld and fd value: %d\n", lseek(fd2, 0, SEEK_END), fd3);
    printf("Seek fd3: %ld\n", lseek(fd3, 0, SEEK_END));
    printf("Seek fd4: %ld\n", lseek(fd4, 0, SEEK_END));


    write(fd1, "filedescriptor1", 15);
    write(fd2, "fd2", 3);
    write(fd3, "fd3", 3);
    write(fd4, "fd4", 3);

    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
}