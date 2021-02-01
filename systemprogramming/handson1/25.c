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


void main(int argc, char **argv, char **argp){
    int pid1, pid2, pid3;
    //pid3 child will be waited for by the parent. It will be made to sleep for 5 secs
    printf("Parent will wait for child 3...\n");

    pid1 = fork();
    if(pid1 > 0){
        pid2 = fork();
        if(pid2 > 0){
            pid3 = fork();
            if(pid3 > 0){
                printf("parent waiting for: %d\n", pid3);
                waitpid(pid3, NULL, 0);
                printf("Parent exiting...\n");
            }
            else{
                sleep(5);
                printf("Child 3 exiting...\n");
            }
        }
        else{
            sleep(7);
            printf("Child 2 exiting...\n");
        }
    }
    else{
        printf("Child 1 exiting...\n");
    }
}
