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
#include "ticketReservation.h"


void main(int argc, char **argv, char **argp){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct ticketReservation);
    lock.l_pid = getpid();

    printf("Program starting...\n");

    int fd = open("trash/17db.dat", O_RDWR);
    if(fd == -1){
        printf("%s\n",strerror(errno));
    }

    FILE *file = fopen("trash/17db.dat", "r+");
    if(file == NULL){
        printf("%s\n",strerror(errno));
        return;
    }

    printf("Inside critical section executing...\n");
    int retval = fcntl(fd, F_SETLKW, &lock);
    if(retval == -1){
        printf("%s\n",strerror(errno));
    }

    struct ticketReservation t;
    printf("Read %ld bytes\n",fread(&t, sizeof (t), 1, file));
    printf("Current ticket value: %d\n", t.number);
    t.number = t.number + 1;
    printf("Press enter to finish\n");
    getchar();
    fseek(file, 0, 0);
    //printf("File write pointer is at %ld\n",ftell(file));
    printf("Written %ld bytes\n", fwrite(&t, sizeof(t), 1, file));
    printf("New ticket value: %d\n", t.number);
    lock.l_type = F_UNLCK;
    printf("Fcntl unlock value: %d\n", fcntl(fd, F_SETLK, &lock));
    printf("Leaving critical section...\n");

    fclose(file);
    close(fd);

}
