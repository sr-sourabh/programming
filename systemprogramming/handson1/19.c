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


void main(int argc, char **argv, char **argp){
    clock_t t = clock();
    getpid();
    t = clock() - t;
    double seconds = ((double)t)/CLOCKS_PER_SEC;
    printf("Time taken for getpid(): %f", seconds);
}
