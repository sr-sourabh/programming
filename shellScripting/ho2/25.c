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
25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
*/

void main(int argc, char **argv, char **argp){

    int msgid;
    key_t key;
    key = ftok("./24.c", 123);
    msgid = msgget(key, IPC_CREAT | 0644);

    struct msqid_ds msg;
    msgctl(msgid, IPC_STAT, &msg);

    printf("access permission: %d\n", msg.msg_perm.cuid);
    printf("uid: %d\n", msg.msg_perm.uid);
    printf("gid: %d\n", msg.msg_perm.gid);
    printf("time of last message sent: %ld\n", msg.msg_stime);
    printf("time of last message received: %ld\n", msg.msg_rtime);
    printf("time of last change in the message queue: %ld\n", msg.msg_ctime);
    printf("size of the queue: %ld\n", msg.__msg_cbytes);
    printf("number of messages in the queue: %ld\n", msg.msg_qnum);
    printf("maximum number of bytes allowed: %ld\n", msg.msg_qbytes);
    printf("pid of the msgsnd: %d\n", msg.msg_lspid);
    printf("pid of the msgrcv: %d\n", msg.msg_lrpid);

}