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

void main(int argc, char **argv, char **argp){
    printf("Minimum priority for Round robin: %d\n", sched_get_priority_min(SCHED_RR));
    printf("Maximum priority for Round robin: %d\n", sched_get_priority_max(SCHED_RR));
    printf("Minimum priority for FIFO: %d\n", sched_get_priority_min(SCHED_FIFO));
    printf("Maximum priority for FIFO: %d\n", sched_get_priority_max(SCHED_FIFO));
}