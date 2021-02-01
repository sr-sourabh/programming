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
    char ch[1];
    write(1, "Enter something: ", 17);
    int count = 0;
    while(read(0, ch, sizeof(ch)) > 0){
        count++;
        if(ch[0] == '\n') break;
        if(count == 1)  write(1, "You Entered: ", 14);
        write(1, ch, sizeof(ch));
    }
    write(1, "\n", 1);
}