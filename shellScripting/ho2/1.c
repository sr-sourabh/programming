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

/*
Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
*/

void main(int argc, char **argv, char **argp){

    struct timeval t = {10,10};
    struct timeval t1 = {0,0};

    struct itimerval v;
    v.it_value = t;
    v.it_interval = t1;

    int choice = -1;
    printf( "1. ITIMER_REAL\n"
            "2. ITIMER_VIRTUAL\n"
            "3. ITIMER_PROF\n"
            "4. Exit\n"
            "Enter your choice:\n");
    scanf("%d", &choice);
    printf("start timer\n");
    switch(choice){

        case 1:
            setitimer(ITIMER_REAL, &v,0);
            break;

        case 2:
            setitimer(ITIMER_VIRTUAL, &v,0);
            break;

        case 3:
            setitimer(ITIMER_PROF, &v,0);
            break;

        case 4: break;
        default: printf("Wrong choice...\n");
    }
    sleep(5);
    while(1){};

}
