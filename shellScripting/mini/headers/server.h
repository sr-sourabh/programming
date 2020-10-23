#include "adminCredentials.h"
#include "errors.h"
#include "user.h"
char menuMsg[] = "Welcome\n1.Admin\n2.Joint Account\n3.Normal Account\n4.Exit\nEnter your choice: ";
char connectedMsg[] = "Connected to server...\n\n";
char adminLoginMsg[] = "\nAdmin Login\n";
char userIdMsg[] = "User Id: ";
char passwordMsg[] = "Password: ";
char adminMenuMsg[] = "\n1.Add User\n2.Delete User\n3.Modify User\n4.Search User\n5.Exit\nEnter your choice: ";

int sleepSync = 0.01;
#define SYNC sleep(sleepSync)

void adminAdd(int nsd){
    struct user u;
    read(nsd, &u, sizeof (struct user));

    char *filepath = malloc(strlen("db/") + strlen(u.userId) + 1);
    strcpy(filepath, "db/");
    strcat(filepath, u.userId);
    int fd = open(filepath, O_CREAT | O_EXCL | O_RDWR, 0644 );
    if(fd == -1){
        printf("%s\n",strerror(errno));
        write(nsd, usernameNotUnique, sizeof usernameNotUnique);
    }
    else{
        write(nsd, success, sizeof success);
        read(nsd, &u, sizeof(struct user));
        write(fd, &u, sizeof(struct user));
        printf("UserId: %s added...\n", u.userId);
    }
    free(filepath);
    close(fd);
}

void adminDelete(int nsd){
    struct user u;
    read(nsd, &u, sizeof u);
    char *filepath = malloc(strlen("db/") + strlen(u.userId) + 1);
    strcpy(filepath, "db/");
    strcat(filepath, u.userId);
    int fd = unlink(filepath);
    if(fd == -1){
        printf("%s\n",strerror(errno));
        memcpy(u.userId, notFound, sizeof notFound);
    }
    else{
        printf("UserId: %s deleted...\n", u.userId);
    }
    write(nsd, &u, sizeof u);
    close(fd);
    free(filepath);
}

void adminModify(int nsd){
    struct user u;

    read(nsd, &u, sizeof u);

    char *filepath = malloc(strlen("db/") + strlen(u.userId) + 1);
    strcpy(filepath, "db/");
    strcat(filepath, u.userId);

    int fd = open(filepath, O_RDWR);
    if(fd == -1){
        printf("%s\n",strerror(errno));
        memcpy(u.userId, notFound, sizeof notFound);
        write(nsd, &u, sizeof u);
    }
    else{
        write(nsd, &u, sizeof u);
        //Read the modified details coming in from client
        read(nsd, &u, sizeof(struct user));
        //Read existing details
        lseek(fd, 0, SEEK_SET);
        struct user existingU;
        read(fd, &existingU, sizeof existingU);
        u.type = existingU.type;
        u.balance = existingU.balance;

        //Write new values
        lseek(fd, 0, SEEK_SET);
        write(fd, &u, sizeof(struct user));
        printf("UserId: %s modified...\n", u.userId);
    }
    close(fd);
    free(filepath);
}

void adminSearch(int nsd){
    struct user u;
    read(nsd, &u, sizeof u);
    char *filepath = malloc(strlen("db/") + strlen(u.userId) + 1);
    strcpy(filepath, "db/");
    strcat(filepath, u.userId);
    int fd = open(filepath, O_RDONLY);
    if(fd == -1){
        printf("%s\n",strerror(errno));
        memcpy(u.userId, notFound, sizeof notFound);
    }
    else{
        lseek(fd, 0, SEEK_SET);
        read(fd, &u, sizeof u);
    }
    write(nsd, &u, sizeof u);
    close(fd);
    free(filepath);
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
        SYNC;
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

