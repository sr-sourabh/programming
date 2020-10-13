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
Write a program to send messages to the message queue. Check $ipcs -q
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

    m.type = 1;
    strncpy(m.message, "hello", 20);
    int status = msgsnd(msgid, &m, sizeof m, 0);
    if(status == -1){
        printf("%s\n",strerror(errno));
    }

}