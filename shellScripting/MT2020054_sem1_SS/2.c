void main(){
    while(1);
}

/*
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ ls /proc/12522
attr        comm             fd        map_files   net            pagemap      schedstat     stat     timerslack_ns
autogroup   coredump_filter  fdinfo    maps        ns             patch_state  sessionid     statm    uid_map
auxv        cpuset           gid_map   mem         numa_maps      personality  setgroups     status   wchan
cgroup      cwd              io        mountinfo   oom_adj        projid_map   smaps         syscall
clear_refs  environ          limits    mounts      oom_score      root         smaps_rollup  task
cmdline     exe              loginuid  mountstats  oom_score_adj  sched        stack         timers
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ ls /proc/12522/fd
0  1  2
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ cat /proc/12522/stat
12522 (a.out) R 10778 12522 10778 34816 12545 4194304 91 0 0 0 11285 0 0 0 20 0 1 0 2891975 4481024 180 18446744073709551615 94039780233216 94039780235208 140733578096224 0 0 0 0 0 0 0 0 0 17 0 0 0 0 0 0 94039782333936 94039782334480 94039785644032 140733578100852 140733578100860 140733578100860 140733578104816 0
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ cat /proc/12522/syscall
cat: /proc/12522/syscall: Operation not permitted
sourabh@sourabh-predator:~/programming/shellScripting/MT2020054_sem1_SS$ cat /proc/12522/status
Name:	a.out
Umask:	0022
State:	R (running)
Tgid:	12522
Ngid:	0
Pid:	12522
PPid:	10778
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	4 24 27 30 46 113 128 1000
NStgid:	12522
NSpid:	12522
NSpgid:	12522
NSsid:	10778
VmPeak:	    4492 kB
VmSize:	    4376 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	     720 kB
VmRSS:	     720 kB
RssAnon:	      64 kB
RssFile:	     656 kB
RssShmem:	       0 kB
VmData:	      44 kB
VmStk:	     132 kB
VmExe:	       4 kB
VmLib:	    2112 kB
VmPTE:	      48 kB
VmSwap:	       0 kB
HugetlbPages:	       0 kB
CoreDumping:	0
Threads:	1
SigQ:	0/31117
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000000
SigCgt:	0000000000000000
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	0000003fffffffff
CapAmb:	0000000000000000
NoNewPrivs:	0
Seccomp:	0
Speculation_Store_Bypass:	thread vulnerable
Cpus_allowed:	f
Cpus_allowed_list:	0-3
Mems_allowed:	00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	0
nonvoluntary_ctxt_switches:	580

*/