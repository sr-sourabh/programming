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
    printf("Executing with below arguments...\n");
    for(int i = 0 ; i < argc ; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
}