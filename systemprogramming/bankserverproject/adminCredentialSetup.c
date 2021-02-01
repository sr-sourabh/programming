#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>
#include "headers/adminCredentials.h"
/*
Setup admin password and userId file
*/
void main(){

    struct AdminCredentials admin;
    memcpy(admin.userId, adminUserId, 20 );
    memcpy(admin.password, adminPassword, 20);

    int fd = open(adminCredFile, O_CREAT| O_RDWR | O_TRUNC, 0644);
    int b = write(fd, &admin, sizeof(struct AdminCredentials));
    if(b < 0){
        printf("%s\n",strerror(errno));
    }
    close(fd);
}
