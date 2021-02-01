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

void main(int argc, char **argv, char **argp){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int fd = open("trash/16dummy.txt", O_RDWR);
    if(fd == -1){
        printf("%s\n",strerror(errno));
    }
    printf("Program starting write lock...\n");
    int retval = fcntl(fd, F_SETLKW, &lock);
    if(retval == -1){
        printf("%s\n",strerror(errno));
    }
    printf("Inside critical section executing...\n");
    printf("Press a Enter to finish...\n");
    getchar();
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Leaving critical section...\n");

    close(fd);

}
