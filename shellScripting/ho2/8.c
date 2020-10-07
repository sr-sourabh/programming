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

void handler(int sigid){
    switch(sigid){
        case SIGSEGV : printf("SIGSEGV handled\n"); exit(0); break;
        case SIGINT : printf("\nSIGINT handled\n"); break;
        case SIGFPE: printf("\nSIGFPE handled\n"); exit(0); break;
        case SIGALRM: printf("SIGALRM handled\n"); exit(0);  break;
        case SIGVTALRM: printf("\nSIGVTALRM handled\n"); exit(0); break;
        case SIGPROF: printf("\nSIGPROF handled\n"); exit(0); break;
        default : break;
    }
}

void main(int argc, char **argv, char **argp){
    int choice = -1;
    while(choice != 8){
        printf( "1. SIGSEGV\n"
                "2. SIGINT\n"
                "3. SIGFPE \n"
                "4. SIGALRM(using alarm sys call)\n"
                "5. SIGALRM(using setitimer)\n"
                "6. SIGVTALRM\n"
                "7. SIGPROF\n"
                "8. Exit\n"
                "Enter your choice\n");
        scanf("%d", &choice);

        int input;
        struct timeval t = {0,1};
        struct timeval t1 = {0,0};

        struct itimerval v;

        switch(choice){
            case 1:
                signal(SIGSEGV, handler); //segmentation fault
                printf("Enter a number: ");
                scanf("%d", input);
                printf("\n");
                break;

            case 2:
                signal(SIGINT, handler); // ctrl + c
                sleep(5);
                printf("No SIGINT in last 5 seconds\n");
                break;

            case 3:
                signal(SIGFPE, handler); //floating point error;
                int a = 1/0;
                break;

            case 4:
                signal(SIGALRM, handler);
                alarm(1);
                pause(); //don't proceed till signal is handled
                break;

            case 5:
                signal(SIGALRM, handler);
                v.it_value = t;
                v.it_interval = t1;
                setitimer(ITIMER_REAL, &v,0);
                pause();
                break;

            case 6:
                signal(SIGVTALRM, handler);
                v.it_value = t;
                v.it_interval = t1;
                setitimer(ITIMER_VIRTUAL, &v, 0);
                while(1){}
                break;

            case 7:
                signal(SIGPROF, handler);
                v.it_value = t;
                v.it_interval = t1;
                setitimer(ITIMER_PROF, &v, 0);
                while(1){}
                break;

            case 8: break;

            default: printf("Wrong choice...\n");

        }
    }
}
//kill -l