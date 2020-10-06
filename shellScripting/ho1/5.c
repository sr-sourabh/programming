#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <string.h>

void main(){
    const char* file = "./trash/5dummy";
    int count = 0 ;
    while(count<5){
        int fd = open(file, O_CREAT, 0644);
        if(fd == -1){
            printf("%s\n",strerror(errno));
        }
        count++;
    }
    while(1);
}

/*
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ ./a.out &
[1] 14185
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ ls /proc/14185
attr        comm             fd        map_files   net            pagemap      schedstat     stat     timerslack_ns
autogroup   coredump_filter  fdinfo    maps        ns             patch_state  sessionid     statm    uid_map
auxv        cpuset           gid_map   mem         numa_maps      personality  setgroups     status   wchan
cgroup      cwd              io        mountinfo   oom_adj        projid_map   smaps         syscall
clear_refs  environ          limits    mounts      oom_score      root         smaps_rollup  task
cmdline     exe              loginuid  mountstats  oom_score_adj  sched        stack         timers
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ ls /proc/14185/fd
0  1  2  3  4  5  6  7
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$
*/