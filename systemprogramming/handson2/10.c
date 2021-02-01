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
Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
*/

void handler(int sigid){
    switch(sigid){
        case SIGSEGV : printf("SIGSEGV handled\n"); exit(0); break;
        case SIGINT : printf("\nSIGINT handled\n"); break;
        case SIGFPE: printf("\nSIGFPE handled\n"); exit(0); break;
        default : break;
    }
}

void main(int argc, char **argv, char **argp){
    int choice = -1;
    while(choice != 4){
        printf( "1. SIGSEGV\n"
                "2. SIGINT\n"
                "3. SIGFPE \n"
                "4. Exit\n"
                "Enter your choice\n");
        scanf("%d", &choice);

        int input;
        struct sigaction newAction;
        newAction.sa_handler = handler;
        newAction.sa_flags = 0;

        switch(choice){
            case 1:
                sigaction(SIGSEGV, &newAction, NULL); //segmentation fault
                printf("Enter a number: ");
                scanf("%d", input);
                printf("\n");
                break;

            case 2:
                sigaction(SIGINT, &newAction, NULL);  // ctrl + c
                sleep(5);
                printf("No SIGINT in last 5 seconds\n");
                break;

            case 3:
                sigaction(SIGFPE, &newAction, NULL); ; //floating point error;
                int a = 1/0;
                break;

            case 4: break;

            default: printf("Wrong choice...\n");

        }
    }
}
//kill -l