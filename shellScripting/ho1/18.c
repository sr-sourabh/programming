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
    int t = 0, len = 3;
    char *record[] = { "This is first record\n",
                      "This is second record\n",
                      "This is third record\n"};
    int sizes[len+1];
    sizes[0] = 0;
    for(int i = 1 ; i < len+1; ++i){
        sizes[i] = sizes[i-1] + strlen(record[i-1]);
    }

    int fd = open("trash/18db", O_CREAT | O_RDWR | O_EXCL , 0644);
    if(fd != -1){
        //printf("%s\n",strerror(errno));
        printf("Setting up database...\n");
        while(t < len){
            write(fd, record[t] ,strlen(record[t]));
            t++;
        }
        printf("Database setup done...\n");
    }
    else {
        fd = open("trash/18db", O_CREAT | O_RDWR  , 0644);
        if(fd == -1){
            printf("%s\n",strerror(errno));
        }
    }

    printf("Which record do you want to modify 1, 2 or 3\nEnter you choice: ");
    int choice;
    scanf("%d",&choice);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = sizes[choice-1];
    lock.l_len = sizes[choice];
    lock.l_pid = getpid();

    printf("Starting...\n");
    int retval = fcntl(fd, F_SETLKW, &lock);
    if(retval == -1){
        printf("%s\n",strerror(errno));
    }

    printf("Inside critical section...\n");
    printf("Press enter to finish...\n");
    getchar();
    getchar();
    lock.l_type = F_UNLCK;
    printf("Fcntl retval while unlocking: %d\n", fcntl(fd, F_SETLK, &lock));
    printf("Done...\n");

    close(fd);

}
