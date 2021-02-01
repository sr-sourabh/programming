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

/*
30. Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
*/

void main(int argc, char **argv, char **argp){

    int shmid;
    int key;
    key = ftok("./24.c", 123);
    printf("Creating shared memory...\n");
    shmid = shmget(key, 64, IPC_CREAT|0644);
    printf("Done...\n");
    printf("Attaching shared memory...\n");
    char *data = shmat(shmid, 0, 0);
    printf("Done...\n");

    printf("Enter some data: ");
    scanf("%s", data);

    char * newdata = shmat(shmid, 0, SHM_RDONLY);
    printf("Data from shared memory: %s\n", newdata);

    printf("Deattaching shared memory...\n");
    shmdt((void *)newdata);
    printf("Done...\n");

    printf("Destroying shared memory...\n");
    shmctl(shmid, IPC_RMID, NULL);
    printf("Done...\n");

}
//ipcs -m