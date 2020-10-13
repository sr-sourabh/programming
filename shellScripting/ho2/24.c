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
Write a program to create a message queue and print the key and message queue id.
*/

void main(int argc, char **argv, char **argp){

    int msgid;
    key_t key;
    key = ftok("./24.c", 123);
    msgid = msgget(key, IPC_CREAT | IPC_EXCL|0644);
    printf("key: %d\nMessage queue id: %d\n", key, msgid);

}

//ipcs -q