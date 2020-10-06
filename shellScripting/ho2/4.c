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

unsigned long long help(){
    unsigned long long t;
    __asm__ __volatile__("rdtsc" : "=A"(t));
    return t;
}

void main(int argc, char **argv, char **argp){

    unsigned long long start = help();
    printf("Start %llu\n", start);
    for(int i = 0 ; i < 100; ++i){
        getppid();
    }
    unsigned long long stop = help();
    printf("Stop %llu\n", stop);
    printf("Total %llu\n", stop - start);
}
/*
    The __volatile__ modifier on an __asm__ block forces the compiler's optimizer to execute the code as-is.
     Without it, the optimizer may think it can be either removed outright, or lifted out of a loop and cached.
*/