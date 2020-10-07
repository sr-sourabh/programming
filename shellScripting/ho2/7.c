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

void *hello(void *arg ){
    printf("Thread %d 's id: %ld \n", *(int*)arg, pthread_self());
}
void main(int argc, char **argv, char **argp){
    pthread_t pthread;
    for(int i = 0 ; i < 3 ; ++i){
        int status = pthread_create(&pthread, NULL, hello, (void*)&i);
        if(status == -1){
            printf("%s\n",strerror(errno));
        }
    }
    pthread_exit(NULL);
}