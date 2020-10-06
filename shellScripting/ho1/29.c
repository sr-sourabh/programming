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

void printSchedulerName(){
    int currentScheduler = sched_getscheduler(getpid());
    char *currentSchedulerName = "Other";
    if(currentScheduler == SCHED_FIFO){
        currentSchedulerName = "FIFO";
    }
    else if(currentScheduler == SCHED_RR){
        currentSchedulerName = "Round Robin";
    }
    printf("Current scheduling policy is: %s\n", currentSchedulerName);
}

void main(int argc, char **argv, char **argp){
    printSchedulerName();

    struct sched_param sh;
    sh.sched_priority = 11;
    printf("Changing scheduler to FIFO\nChanging scheduler priority to: %d\n",sh.sched_priority);
    int status = sched_setscheduler(getpid(), SCHED_FIFO, &sh);
    if(status == -1){
        printf("%s\n",strerror(errno));
    }

    printSchedulerName();

    printf("Current priority obtained using nice: %d\n", nice(0));

    printf("Get schd attribute status: %d\n", sched_getparam(getpid(), &sh));
    printf("Priority obtained using sched_getparam: %d\n", sh.sched_priority);
}
//why is priority coming as 0?