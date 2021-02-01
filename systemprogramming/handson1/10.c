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

    const char *buff = "Hello world";
    int fd = open("trash/10dummy.txt", O_RDWR);
    write(fd, buff, strlen(buff));
    int retval = lseek(fd, 10, SEEK_END);
    printf("Lseek value: %d", retval);
    write(fd, buff, strlen(buff));
    close(fd);

}
/*
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ od -c trash/10dummy.txt
0000000   H   e   l   l   o       w   o   r   l   d  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0   H   e   l   l   o       w   o   r   l   d
0000040
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$
*/