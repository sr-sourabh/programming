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
#include<time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include<sched.h>
#include <stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<pthread.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>

/*
31. Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
*/

void main(int argc, char **argv, char **argp){

    int semidb, semidc;
    int key;

    union semun{
        int val;
        struct semid_ds *buf;
        ushort *array;
    };
    union semun arg;

    key = ftok("./24.c", 123);
    semidb = semget(key, 1, IPC_CREAT | 0644);
    arg.val = 1;
    int status = semctl(semidb, 0, SETVAL, arg);
    if(status == -1){
        printf("%s\n",strerror(errno));
    }
    else{
        printf("Binary semaphore created with id: %d\n", semidb);
    }

    key = ftok("./24.c", 1234);
    semidc = semget(key, 1, IPC_CREAT | 0644);
    arg.val = 5;
    status = semctl(semidc, 0, SETVAL, arg);
    if(status == -1){
        printf("%s\n",strerror(errno));
    }
    else{
        printf("Counting semaphore created with id: %d\n", semidc);
    }

}
//ipcs -s