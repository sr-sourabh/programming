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

/*
Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
*/

void main(int argc, char **argv, char **argp){
    if(!fork()){
        printf("Child executing with pid: %d...\nKilling parent with ppid: %d\n", getpid(), getppid());
        kill(getppid(), SIGKILL);
        sleep(1);
        printf("Parent id after killing: %d\n", getppid());
        sleep(10);
    }
    else{
        sleep(3);
    }
}
//pstree -p -s 20828