#include "errors.h"
#include "user.h"

int sleepSync = 0.01;
#define SYNC sleep(sleepSync)

char incorrectCredentialsMsg[] = "Credentials entered are incorrect...\n";


void handleNormalUser(int sd){
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
    if(strcmp(invalidCredentials, buff) == 0 || strcmp(notFound, buff) == 0){
        printf("%s\n", invalidCredentials);
        return;
    }
    else{
        printf("Login successful...\n");
    }

    char choice[1] = "9";
    while(choice[0] != '6'){
        //Read and display admin menu received from server
        SYNC;
        read(sd, buff, sizeof buff);
        printf("%s", buff);
        scanf("%s", choice);
        //send choice to server
        write(sd, choice, sizeof choice);
        SYNC;
        if(choice[0] == '1'){
            printf("\n********** Deposit Menu **********\n");
            printf("Enter the amount to be deposited:\n");
            int amount;
            scanf("%d", &amount);
            write(sd, &amount, sizeof amount);
            printf("Amount deposited \n");
        }
        else if(choice[0] == '2'){
            printf("\n********** Withdraw Menu **********\n");
            printf("Enter the amount to be withdrawn:\n");
            int amount;
            scanf("%d", &amount);
            write(sd, &amount, sizeof amount);
            printf("Amount withdrawn \n");
        }
        else if(choice[0] == '3'){
            int balance;
            read(sd, &balance, sizeof balance);
            printf("\nAvailable balance is: %d\n", balance);
        }
        else if(choice[0] == '4'){
            printf("\n********** Password change Menu **********\n");
            printf("Enter the new password:\n");
            char passwd[20];
            scanf("%s", passwd);
            write(sd, &passwd, sizeof passwd);
            printf("Password changed \n");
        }
        else if(choice[0] == '5'){
            struct user u;
            read(sd, &u, sizeof u);
            printf("\nUserId: %s\n", u.userId);
            printf("Username: %s\n", u.userName);
            printf("Password: %s\n", u.password);
            printf("Balance: %d\n", u.balance);
            printf("Type: %d\n", u.type);
        }
    }
}

void handleJointUser(int sd){
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
    if(strcmp(invalidCredentials, buff) == 0 || strcmp(notFound, buff) == 0){
        printf("%s\n", invalidCredentials);
        return;
    }
    else{
        printf("Login successful...\n");
    }

    char choice[1] = "9";
    while(choice[0] != '6'){
        //Read and display admin menu received from server
        SYNC;
        read(sd, buff, sizeof buff);
        printf("%s", buff);
        scanf("%s", choice);
        //send choice to server
        write(sd, choice, sizeof choice);
        SYNC;
        if(choice[0] == '1'){
            printf("\n********** Deposit Menu **********\n");
            printf("Enter the amount to be deposited:\n");
            int amount;
            scanf("%d", &amount);
            write(sd, &amount, sizeof amount);
            printf("Amount deposited. Please wait...\n");
        }
        else if(choice[0] == '2'){
            printf("\n********** Withdraw Menu **********\n");
            printf("Enter the amount to be withdrawn:\n");
            int amount;
            scanf("%d", &amount);
            write(sd, &amount, sizeof amount);
            printf("Amount withdrawn. Please wait... \n");
        }
        else if(choice[0] == '3'){
            int balance;
            read(sd, &balance, sizeof balance);
            printf("\nAvailable balance is: %d\n", balance);
        }
        else if(choice[0] == '4'){
            printf("\n********** Password change Menu **********\n");
            printf("Enter the new password:\n");
            char passwd[20];
            scanf("%s", passwd);
            write(sd, &passwd, sizeof passwd);
            printf("Password changed. Please wait... \n");
        }
        else if(choice[0] == '5'){
            struct user u;
            read(sd, &u, sizeof u);
            printf("\nUserId: %s\n", u.userId);
            printf("Username: %s\n", u.userName);
            printf("Password: %s\n", u.password);
            printf("Balance: %d\n", u.balance);
            printf("Type: %d\n", u.type);
        }
    }
}

void adminAdd(int sd){
    printf("\n********** Add User Menu **********\n");
    struct user u;
    char buff[20];
    printf("Enter unique userId:\n");
    scanf("%s", u.userId);
    //send the userid to server for validation
    write(sd, &u, sizeof(struct user));
    //recieve status from server
    read(sd, buff, sizeof(buff));
    if(strcmp(buff, usernameNotUnique) == 0){
        printf("UserId already taken try again...\n");
    }
    else{
        printf("Enter user password: ");
        scanf("%s", u.password);
        printf("Enter user name: ");
        scanf("%s", u.userName);
        printf("Enter type of user: ");
        scanf("%d", &u.type);
        printf("\n");
        u.balance = 0;
        write(sd, &u, sizeof(struct user));
        printf("User addded...\n");
    }
}

void adminDelete(int sd){
    printf("\n********** Delete User Menu **********\n");
    struct user u;
    printf("Enter the userId to be deleted: \n");
    scanf("%s", u.userId);
    //send userId to server for validation
    write(sd, &u, sizeof u);
    //read server status
    read(sd, &u, sizeof u);
    if(strcmp(u.userId, notFound) == 0){
        printf("UserId does not exixts try again...\n");
    }
    else{
        printf("User removed...\n");
    }
}

void adminModify(int sd){
    printf("\n********** Modify User Menu **********\n");
    struct user u;
    printf("Enter the userId to be modified: \n");
    scanf("%s", u.userId);
    //send userId to server for validation
    write(sd, &u, sizeof u);
    //read server status
    read(sd, &u, sizeof u);
    if(strcmp(u.userId, notFound) == 0){
        printf("UserId does not exixts try again...\n");
    }
    else{
        printf("UserId and balance cannot be changed\n");
        printf("Enter new user password:\n");
        scanf("%s", u.password);
        printf("Enter new user name:\n");
        scanf("%s", u.userName);
        printf("\n");
        write(sd, &u, sizeof(struct user));
        printf("User modified...\n");
    }
}

void adminSearch(int sd){
    printf("\n********** Search User Menu **********\n");
    struct user u;
    printf("Enter the userId to be searched: \n");
    scanf("%s", u.userId);
    //send userid to server for search
    write(sd, &u, sizeof u);
    //read server status
    read(sd, &u, sizeof u);
    if(strcmp(u.userId, notFound) == 0){
        printf("No user found...\n");
    }
    else{
        printf("UserId: %s\n", u.userId);
        printf("Username: %s\n", u.userName);
        printf("Balance: %d\n", u.balance);
        printf("User type: %d\n", u.type);
    }
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
        printf("Login successful...\n");
    }

    char choice[1] = "9";
    while(choice[0] != '5'){
        //Read and display admin menu recieved from server
        SYNC;
        read(sd, buff, sizeof buff);
        printf("%s", buff);
        scanf("%s", choice);
        write(sd, choice, sizeof choice);
        SYNC;
        if(choice[0] == '1'){
            adminAdd(sd);
        }
        else if(choice[0] == '2'){
            adminDelete(sd);
        }
        else if(choice[0] == '3'){
            adminModify(sd);
        }
        else if(choice[0] == '4'){
            adminSearch(sd);
        }
    }

}