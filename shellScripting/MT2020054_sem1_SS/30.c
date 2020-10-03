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


void main(int argc, char **argv, char **argp){

    if(!fork()){
        printf("Converting to daemon with pid: %d\n", getpid());
        setsid(); //make session leader
        umask(0); //permission with 0744

        struct tm time_to_execute;
        time_to_execute.tm_hour = 16;

        struct tm *time_now;
        time_t t;
        time(&t);
        time_now = localtime(&t);

        int sleep_time = 1800; //give 86400 to sleep for 24 hours

        while(1){
            if(time_now->tm_hour == time_to_execute.tm_hour ){
                int pid = fork();
                if(!pid){
                    printf("Script execution starting...\n");
                    execl("trash/30.sh", "30.sh", NULL);
                }
                else{
                    waitpid(pid, NULL, 0);
                    sleep(sleep_time);
                }
            }
            else{
                sleep(sleep_time);
            }
        }
    }
    else{
        exit(0);
    }
}
