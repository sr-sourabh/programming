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
    int choice = -1;

    while(choice != 7){

        printf("\n1. execl\n"
                "2. execlp\n"
                "3. execle\n"
                "4. execv\n"
                "5. execvp\n"
                "6. execvpe (This requires an executable file with name srtestenv to be present in $PATH )\n"
                "7. exit\n"
                "Enter your choice:\n");
        scanf("%d", &choice);

        char *const myargv1[] = {"hello", NULL};
        char *const myargv2[] = {"ls", "-Rl", NULL};
        char *const myargp[] = {"myenviron", NULL};
        int pid;
        int status;
        switch(choice){
            case 1:
                pid = fork();
                if(!pid){
                    execl("/bin/ls", "ls", "-Rl", NULL); //File path
                }
                waitpid(pid, NULL, 0);
                break;

            case 2:
                pid = fork();
                if(!pid){
                    execlp("ls", "ls", "-Rl", NULL); // uses the PATH environment variable to find the file
                }
                waitpid(pid, NULL, 0);
                break;

            case 3:
                pid = fork();
                if(!pid){
                    execle("/bin/ls", "ls", "-Rl", NULL, NULL);
                }
                waitpid(pid, NULL, 0);
                break;

            case 4:
                pid = fork();
                if(!pid){
                    execv("/bin/ls", myargv2);
                }
                waitpid(pid, NULL, 0);
                break;

            case 5:
                pid = fork();
                if(!pid){
                    execvp("ls", myargv2);
                }
                waitpid(pid, NULL, 0);
                break;

            case 6:
                pid = fork();
                if(!pid){
                    status = execvpe("srtestenv", myargv1, myargp);
                    if(status == -1){
                        printf("%s\n",strerror(errno));
                    }
                }
                waitpid(pid, NULL, 0);
                break;

            case 7 : break;

            default : printf("Wrong choice try again...\n");
        }
    }
}

/*
    v mean argv variable length array
    l means variable len argument list
    e mean it takes an extra argument to provide the environment to the new program.
        Otherwise, the program inherits the current process's environment.
        It is given using an array
    p means path : search the PATH environment variable to find the program if it doesn't have a directory in it
        (i.e. it doesn't contain a / character).
        Otherwise, the program name is always treated as a path to the executable.
        echo $PATH | grep ':/bin'

    free BSD added execvP which has an additional arg for custom search path instead of PATH

    Actually, the only system call is execve(2) and all other exec* functions are wrapping it
*/