#include "errors.h"

int sleepSync = 0.01;
#define SYNC sleep(sleepSync)

char incorrectCredentialsMsg[] = "Credentials entered are incorrect...\n";


void handleNormalUser(int sd){

}

void handleJointUser(int sd){

}

void handleAdminUser(int sd){
    char buff[200];
    char userId[20];
    char password[20];

    read(sd, buff, sizeof(buff));
    printf("%s", buff);
    read(sd, buff, sizeof(buff));
    printf("%s", buff);

    scanf("%s", userId);
    write(sd, userId, sizeof userId);
    read(sd, buff, sizeof(buff));
    printf("%s", buff);
    scanf("%s", password);
    write(sd, password, sizeof password);

    //Waiting for authorization
    read(sd, buff, sizeof buff);
    if(strcmp(invalidCredentials, buff) == 0){
        printf("%s\n", invalidCredentials);
        return;
    }
    else{
        printf("Login successfull...\n");
    }

    char choice[1] = "9";
    while(choice[0] != '5'){
        //Read and display admin menu recieved from server
        read(sd, buff, sizeof buff);
        printf("%s", buff);
        scanf("%s", choice);
        write(sd, choice, sizeof choice);
        if(choice[0] == '1'){

        }
        else if(choice[0] == '2'){

        }
        else if(choice[0] == '3'){

        }
        else if(choice[0] == '4'){

        }
    }



}