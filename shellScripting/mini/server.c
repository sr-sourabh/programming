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
#include "headers/server.h"
/*
Server
*/

void main(int argc, char **argv, char **argp){

    printf("Server is starting up...\n");

    struct sockaddr_in server, client;
    int sd, nsd, clientLen;
    char buff[50];

    sd = socket(AF_INET, SOCK_STREAM, 0); //domain, type, protocol
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4444);

    bind(sd, (struct sockaddr *) &server, sizeof server);
    listen(sd, 2);

    while(1){
        printf("\nWaiting for client...\n");
        clientLen = sizeof(client);
        nsd = accept(sd, (struct sockaddr*) &client, &clientLen);

        if(!fork()){
            printf("Connecting to client...\nA new client is connected\n");
            handleLogin(nsd);
            close(nsd);
            close(sd);
            exit(0);
        }
        else{
            close(nsd);
        }
    }
    close(sd);

}
