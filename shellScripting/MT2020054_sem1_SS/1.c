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

    const char *target = "./trash/dummy.txt";
    const char *softlink = "./trash/1softlink.txt";
    const char *hardlink = "./trash/1hardlink.txt";
    const char *mkfifotest = "./trash/1mkfifotest";
    const char *mknodtest = "./trash/1mknodtest";

    printf("**************Link creation menu***************\n"
            "1. Soft link\n"
            "2. Hard link\n"
            "3. FIFO using mkfifo\n"
            "4. FIFO using mknod (Block special file, requires root)\n"
            "5. Exit\n");
    int choice = -1;
    int retval;
    while(choice != 5){
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1 :    if(symlink(target, softlink) == 0){
                            printf("soft link created successfully...\n");
                        }
                        else {
                            printf("%s\n",strerror(errno));
                        }
                        break;

            case 2 :    if(link(target, hardlink) == 0){
                            printf("hard link created successfully...\n");
                        }
                        else {
                            printf("%s\n",strerror(errno));

                        }
                        break;

            case 3 :    if(mkfifo(mkfifotest, 0666) == 0){
                            printf("Named pipe created successfully...\n");
                        }
                        else {
                            printf("%s\n",strerror(errno));

                        }
                        break;

            case 4 :    if(mknod(mknodtest, S_IFBLK | 0644, makedev(12,3)) == 0){
                            printf("Named pipe created successfully...\n");
                        }
                        else {
                            printf("%s\n",strerror(errno));
                        }
                        break;

            case 5 :
                        break;

            default :   printf("Wrong choice try again...\n");
        }
    }

}
