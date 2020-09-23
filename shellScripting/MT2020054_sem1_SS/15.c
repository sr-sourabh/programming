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

extern char **environ;
void main(int argc, char **argv, char **argp){
    printf("Using normal method:\n\n");
    for(char **env = argp ; *env != NULL ; env++){
        printf("%s \n", *env);
    }

    printf("\n\nUsing environ: \n\n");
    char *s = *environ;
    for(int i = 1; s; i++){
        printf("%s\n", s);
        s = *(environ+i);
    }
}
