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
    struct ticketReservation t;
    t.number = 1;
    printf("Setting up database...\n");
    FILE *file = fopen("trash/17db.dat", "w+");
    if(file == NULL){
        printf("%s\n",strerror(errno));
        return;
    }
    printf("Done..\nInitial ticket number is 1\n");

    fwrite(&t, sizeof (t), 1, file);

    fclose(file);

}
