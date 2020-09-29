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


void main(int argc, char **argv, char **argp){
    int p = getpriority(PRIO_PROCESS, 0);
    printf("Current priority is: %d\n", p);
    printf("Setting new priority as 2 using nice...\n");
    p = nice(2);
    printf("New priority is: %d\n", p);
}
