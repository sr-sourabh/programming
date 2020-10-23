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
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include "headers/client.h"

/*
Client
*/

void main(int argc, char **argv, char **argp){

    struct sockaddr_in server;
    int sd, msgLen;
    char buff[300];

    sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(4444);

    printf("Waiting to connect...\n");
    connect(sd, (struct sockaddr *) &server, sizeof(server));

    read(sd, buff, sizeof(buff));
    printf("%s", buff);
    read(sd, buff, sizeof(buff));
    printf("%s", buff);

    char choice[1];
    scanf("%s", choice);
    write(sd, choice, sizeof(choice));

    if(choice[0] == '1'){
        handleAdminUser(sd);
    }
    else if(choice[0] == '2'){
        handleJointUser(sd);
    }
    else if(choice[0] == '3'){
        handleNormalUser(sd);
    }
    else{
        printf("Client exiting...\n");
        exit(0);
    }

    close(sd);

}
