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
Write a program to remove the message queue.
*/

void main(int argc, char **argv, char **argp){

    int msgid;
    key_t key;
    key = ftok("./24.c", 123);
    msgid = msgget(key, IPC_CREAT|0644);

    struct msqid_ds msg;
    msg.msg_perm.mode = 0744;
    int status = msgctl(msgid, IPC_RMID, 0);
    if(status == -1){
        printf("%s\n",strerror(errno));
    }
}
//ipcs -q