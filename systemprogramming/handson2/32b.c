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
32. Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
*/

void main(int argc, char **argv, char **argp){

    int shmid;
    int keym;
    keym = ftok("./24.c", 123);
    shmid = shmget(keym, 64, IPC_CREAT|0644);
    printf("shmid: %d\n", shmid);

    int semid;
    int keys;
    keys = ftok("./24.c", 123);
    semid = semget(keys, 1, 0);
    printf("Semid: %d\n", semid);

    printf("Entering critical section...\nWaiting for unlock...\n");
    struct sembuf buf = {0, -1, 0};
    buf.sem_op = -1;//-1
    printf("sem_op: %d\n", buf.sem_op);
    printf("%d\n", semop(semid, &buf, 1));

    char *data = shmat(shmid, 0, 0);
    printf("Current value: %s\n", data);
    printf("Press a enter to finish\n");
    getchar();
    (*data)++;
    printf("New value: %s\n", data);
    shmdt((void *)data);

    printf("Leaving critical section...\nUnlocking...\nDone\n");
    buf.sem_op = 1;
    printf("%d\n", semop(semid, &buf, 1));
}
