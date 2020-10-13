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

/*
27. Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
*/

void main(int argc, char **argv, char **argp){
    struct msg{
        long int type;
        char message[20];
    } m;

    int msgid;
    key_t key;
    key = ftok("./24.c", 123);
    msgid = msgget(key, IPC_CREAT | 0644);

    int status = msgrcv(msgid, &m, sizeof m, 1, 0);
    if(status == -1){
        printf("%s\n",strerror(errno));
    }
    printf("Part a\n");
    printf("Type: %ld\nMessage: %s\n", m.type, m.message);

    status = msgrcv(msgid, &m, sizeof m, 22, IPC_NOWAIT);
    printf("Part b\n");
    if(status == -1){
        printf("%s\n",strerror(errno));
    }

}