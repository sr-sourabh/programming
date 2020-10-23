#include "adminCredentials.h"
#include "errors.h"

char menuMsg[] = "Welcome\n1.Admin\n2.Joint Account\n3.Normal Account\n4.Exit\nEnter your choice: ";
char connectedMsg[] = "Connected to server...\n\n";
char adminLoginMsg[] = "\nAdmin Login\n";
char userIdMsg[] = "User Id: ";
char passwordMsg[] = "Password:";
char adminMenuMsg[] = "\n1.Add User\n2.Delete User\n3.Modify User\n4.Search User\n5.Exit\nEnter your choice: ";

int sleepSync = 0.01;
#define SYNC sleep(sleepSync)

void adminAdd(int nsd){

}

void adminDelete(int nsd){

}

void adminModify(int nsd){

}

void adminSearch(int nsd){

}

void handleAdminUser(int nsd){
    char userId[20];
    char password[20];

    write(nsd, adminLoginMsg, sizeof adminLoginMsg);
    SYNC;
    write(nsd, userIdMsg, sizeof userIdMsg);
    read(nsd, userId, sizeof(userId));
    write(nsd, passwordMsg, sizeof passwordMsg);
    read(nsd, password, sizeof(password));

    int adminCredFd = open(adminCredFile, O_RDONLY);
    if(adminCredFd == -1){
        printf("%s\n",strerror(errno));
    }

    struct AdminCredentials admin;
    lseek(adminCredFd, 0, SEEK_SET);
    int b = read(adminCredFd, &admin, sizeof(struct AdminCredentials));

    if(b == -1){
        printf("%s\n",strerror(errno));
    }

    //incorrect credentails
    if(strcmp(admin.userId, userId) != 0 || strcmp(admin.password, password) != 0){
        write(nsd, invalidCredentials, sizeof invalidCredentials);
        close(adminCredFd);
        return;
    }
    else{
        write(nsd, "Success\n", sizeof "Success\n");
    }

    char choice[1] = "9";
    while(choice[0] != '5'){
        SYNC;
        write(nsd, adminMenuMsg, sizeof adminMenuMsg);
        //Read the choice from client
        read(nsd, choice, sizeof choice);
        if(choice[0] == '1'){
            adminAdd(nsd);
        }
        else if(choice[0] == '2'){
            adminDelete(nsd);
        }
        else if(choice[0] == '3'){
            adminModify(nsd);
        }
        else if(choice[0] == '4'){
            adminSearch(nsd);
        }
    }

    close(adminCredFd);

}

void handleJointUser(int nsd){

}

void handleNormalUser(int nsd){

}

void handleLogin(int nsd){
    write(nsd, connectedMsg, sizeof(connectedMsg));
    SYNC;
    write(nsd, menuMsg, sizeof menuMsg);

    char choice[1];
    read(nsd, choice, sizeof choice);

    if(choice[0] == '1')
        handleAdminUser(nsd);
    else if(choice[0] == '2')
        handleJointUser(nsd);
    else if(choice[0] == '3')
        handleNormalUser(nsd);
    else{
        printf("Exiting...\n"); return;
    }
}

