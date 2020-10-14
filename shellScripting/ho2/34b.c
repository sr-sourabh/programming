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

/*
34. Write a program to create a concurrent server.
a. use fork
b. use pthread_create
*/

void *serverSlave(void *arg ){
    int nsd = *(int *) arg;
    char buff[50];

    printf("Connecting to client...\nA new is client connected\n");
    write(nsd, "Connected to server...\n", sizeof("Connected to server...\n"));
    read(nsd, buff, sizeof(buff));
    printf("\nMessage from client: %s", buff);
    close(nsd);
    return 0;
}

void main(int argc, char **argv, char **argp){
    int choice ;
    printf("1. Run as server\n2. Run as client\nEnter your choice:\n");
    scanf("%d", &choice);

    if(choice == 1){
        struct sockaddr_in server, client;
        int sd, nsd, clientLen;

        sd = socket(AF_INET, SOCK_STREAM, 0);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(5555);

        bind(sd, (struct sockaddr *) &server, sizeof server);
        listen(sd, 2);

        while(1){
            printf("\nWaiting for client...\n");
            clientLen = sizeof(client);
            nsd = accept(sd, (struct sockaddr*) &client, &clientLen);

            pthread_t p;
            int status = pthread_create(&p, NULL, serverSlave, (void*)&nsd);
            if(status == -1){
                printf("%s\n",strerror(errno));
            }
        }
        pthread_exit(NULL);
        close(sd);
    }
    else if (choice == 2){
        struct sockaddr_in server;
        int sd, msgLen;
        char buff[50];

        sd = socket(AF_INET, SOCK_STREAM, 0);
        server.sin_family = AF_INET;
        //server.sin_addr.s_addr = "IP";
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        server.sin_port = htons(5555);

        printf("Waiting to connect...\n");
        connect(sd, (struct sockaddr *) &server, sizeof(server));

        read(sd, buff, sizeof(buff));
        printf("Message from server: %s", buff);
        printf("Enter a message: \n");
        scanf("%s", buff);
        write(sd, buff, sizeof(buff));
    }

}
