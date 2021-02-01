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

/*
Answer of a b and c is in comments.

Create a FIFO file by
a. mknod command:               $mknod myfifo p

b. mkfifo command:              $mkfifo myfifo1

c. use strace command to find out, which command (mknod or mkfifo) is better.
            sourabh@sourabh-predator:~/programming/shellScripting/ho2$ strace -c mknod myfifo p
            % time     seconds  usecs/call     calls    errors syscall
            ------ ----------- ----------- --------- --------- ----------------
              0.00    0.000000           0         7           read
              0.00    0.000000           0        10           close
              0.00    0.000000           0         8           fstat
              0.00    0.000000           0        17           mmap
              0.00    0.000000           0        12           mprotect
              0.00    0.000000           0         1           munmap
              0.00    0.000000           0         3           brk
              0.00    0.000000           0         2           rt_sigaction
              0.00    0.000000           0         1           rt_sigprocmask
              0.00    0.000000           0         8         8 access
              0.00    0.000000           0         1           execve
              0.00    0.000000           0         1           mknod
              0.00    0.000000           0         2         2 statfs
              0.00    0.000000           0         1           arch_prctl
              0.00    0.000000           0         1           set_tid_address
              0.00    0.000000           0         8           openat
              0.00    0.000000           0         1           set_robust_list
              0.00    0.000000           0         1           prlimit64
            ------ ----------- ----------- --------- --------- ----------------
            100.00    0.000000                    85        10 total
            sourabh@sourabh-predator:~/programming/shellScripting/ho2$ strace -c mkfifo myfifo1
            % time     seconds  usecs/call     calls    errors syscall
            ------ ----------- ----------- --------- --------- ----------------
             25.66    0.000274          16        17           mmap
             16.20    0.000173          14        12           mprotect
             11.05    0.000118          15         8           openat
              8.80    0.000094          12         8         8 access
              8.24    0.000088           9        10           close
              7.40    0.000079          11         7           read
              6.18    0.000066           8         8           fstat
              4.21    0.000045          45         1           mknod
              3.37    0.000036          36         1           munmap
              2.72    0.000029          15         2         2 statfs
              1.50    0.000016           5         3           brk
              1.40    0.000015           8         2           rt_sigaction
              0.66    0.000007           7         1           rt_sigprocmask
              0.66    0.000007           7         1           arch_prctl
              0.66    0.000007           7         1           set_tid_address
              0.66    0.000007           7         1           set_robust_list
              0.66    0.000007           7         1           prlimit64
              0.00    0.000000           0         1           execve
            ------ ----------- ----------- --------- --------- ----------------
            100.00    0.001068                    85        10 total
            sourabh@sourabh-predator:~/programming/shellScripting/ho2$

            mknod seems faster


c. mknod system call

d. mkfifo library function

*/

void main(int argc, char **argv, char **argp){
    int choice = -1;


    while(choice != 3){
        printf( "1. mknod system call\n"
                "2. mkfifo library function\n"
                "3. exit\nEnter your choice:\n");
        scanf("%d", &choice);

        if(choice == 1){
            int status = mknod("trash/19mknod", S_IFIFO | 0644, 0);
            if(status == -1){
                printf("%s\n",strerror(errno));
            }
            else{
                printf("created successfully...\n");
            }
        }
        else if(choice == 2){
            int status = mkfifo("trash/19mkfifo",  0644);
            if(status == -1){
                printf("%s\n",strerror(errno));
            }
            else{
                printf("created successfully...\n");
            }
        }
        else break;
    }
}