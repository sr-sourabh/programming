#include "adminCredentials.h"
#include "errors.h"
#include "user.h"
char menuMsg[] = "Welcome\n1.Admin\n2.Joint Account\n3.Normal Account\n4.Exit\nEnter your choice: ";
char connectedMsg[] = "Connected to server...\n\n";

char adminLoginMsg[] = "\nAdmin Login\n";
char userIdMsg[] = "User Id: ";
char passwordMsg[] = "Password: ";
char adminMenuMsg[] = "\n1.Add User\n2.Delete User\n3.Modify User\n4.Search User\n5.Exit\nEnter your choice: ";

char normalUserLoginMsg[] = "\nNormal User Login\n";
char normalMenuMsg[] = "\n1.Deposit\n2.Withdraw\n3.View Balance\n4.Change Password\n5.View Details\n6.Exit\nEnter your choice: ";

char jointUserLoginMsg[] = "\nJoint User Login\n";

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
    char userId[20];
    char password[20];

    write(nsd, jointUserLoginMsg, sizeof jointUserLoginMsg);
    SYNC;
    write(nsd, userIdMsg, sizeof userIdMsg);
    read(nsd, userId, sizeof(userId));
    write(nsd, passwordMsg, sizeof passwordMsg);
    read(nsd, password, sizeof(password));

    char *filepath = malloc(strlen("db/") + strlen(userId) + 1);
    strcpy(filepath, "db/");
    strcat(filepath, userId);
    int userFd = open(filepath, O_RDWR);
    if(userFd == -1){
        printf("%s\n",strerror(errno));
        write(nsd, notFound, sizeof notFound);
        close(userFd);
        free(filepath);
        return;
    }

    lseek(userFd, 0, SEEK_SET);
    struct user u;
    read(userFd, &u, sizeof(struct user));
    if(strcmp(password, u.password) != 0 || (u.type != 2)){
        write(nsd, invalidCredentials, sizeof invalidCredentials);
        close(userFd);
        free(filepath);
        return;
    }
    //else write success to client
    write(nsd, success, sizeof success);
    char choice[1] = "9";
    while(choice[0] != '6'){
        close(userFd);
        userFd = open(filepath, O_RDWR);
        lseek(userFd, 0, SEEK_SET);
        read(userFd, &u, sizeof(struct user));
        SYNC;
        write(nsd, normalMenuMsg, sizeof normalMenuMsg);
        //Read the choice from client
        read(nsd, choice, sizeof choice);
        SYNC;
        if(choice[0] == '1'){
            int amount;

            struct flock lock;
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = 0;
            lock.l_len = sizeof(struct user);
            lock.l_pid = getpid();

            int retval = fcntl(userFd, F_SETLKW, &lock);
            if(retval == -1){
                printf("%s\n",strerror(errno));
            }

            lseek(userFd, 0, SEEK_SET);
            read(userFd, &u, sizeof(struct user));

            read(nsd, &amount, sizeof amount);

            u.balance += amount;
            lseek(userFd, 0, SEEK_SET);
            write(userFd, &u, sizeof u);
            printf("Amount deposited for: %s\n", userId);

            lock.l_type = F_UNLCK;
            fcntl(userFd, F_SETLK, &lock);
        }
        else if(choice[0] == '2'){
            int amount;

            struct flock lock;
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = 0;
            lock.l_len = sizeof(struct user);
            lock.l_pid = getpid();

            int retval = fcntl(userFd, F_SETLKW, &lock);
            if(retval == -1){
                printf("%s\n",strerror(errno));
            }

            lseek(userFd, 0, SEEK_SET);
            read(userFd, &u, sizeof(struct user));

            read(nsd, &amount, sizeof amount);
            u.balance -= amount;
            lseek(userFd, 0, SEEK_SET);
            write(userFd, &u, sizeof u);
            printf("Amount withdrawn for: %s\n", userId);

            lock.l_type = F_UNLCK;
            fcntl(userFd, F_SETLK, &lock);
        }
        else if(choice[0] == '3'){
            struct flock lock;
            lock.l_type = F_RDLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = 0;
            lock.l_len = sizeof(struct user);
            lock.l_pid = getpid();

            int retval = fcntl(userFd, F_SETLKW, &lock);
            if(retval == -1){
                printf("%s\n",strerror(errno));
            }

            lseek(userFd, 0, SEEK_SET);
            read(userFd, &u, sizeof(struct user));

            write(nsd, &u.balance, sizeof u.balance);
            printf("\n");

            lock.l_type = F_UNLCK;
            fcntl(userFd, F_SETLK, &lock);
        }
        else if(choice[0] == '4'){
            char passwd[20];
            struct flock lock;
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = 0;
            lock.l_len = sizeof(struct user);
            lock.l_pid = getpid();

            int retval = fcntl(userFd, F_SETLKW, &lock);
            if(retval == -1){
                printf("%s\n",strerror(errno));
            }

            lseek(userFd, 0, SEEK_SET);
            read(userFd, &u, sizeof(struct user));

            read(nsd, &passwd, sizeof passwd);
            memcpy(u.password, passwd, sizeof u.password);
            lseek(userFd, 0, SEEK_SET);
            write(userFd, &u, sizeof u);
            printf("Password changed for: %s\n", userId);

            lock.l_type = F_UNLCK;
            fcntl(userFd, F_SETLK, &lock);
        }
        else if(choice[0] == '5'){
            struct flock lock;
            lock.l_type = F_RDLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = 0;
            lock.l_len = sizeof(struct user);
            lock.l_pid = getpid();

            int retval = fcntl(userFd, F_SETLKW, &lock);
            if(retval == -1){
                printf("%s\n",strerror(errno));
            }

            lseek(userFd, 0, SEEK_SET);
            read(userFd, &u, sizeof(struct user));

            write(nsd, &u, sizeof u);

            lock.l_type = F_UNLCK;
            fcntl(userFd, F_SETLK, &lock);
        }
    }

    close(userFd);
    free(filepath);
}

void handleNormalUser(int nsd){
    char userId[20];
    char password[20];

    write(nsd, normalUserLoginMsg, sizeof normalUserLoginMsg);
    SYNC;
    write(nsd, userIdMsg, sizeof userIdMsg);
    read(nsd, userId, sizeof(userId));
    write(nsd, passwordMsg, sizeof passwordMsg);
    read(nsd, password, sizeof(password));

    char *filepath = malloc(strlen("db/") + strlen(userId) + 1);
    strcpy(filepath, "db/");
    strcat(filepath, userId);
    int userFd = open(filepath, O_RDWR);
    if(userFd == -1){
        printf("%s\n",strerror(errno));
        write(nsd, notFound, sizeof notFound);
        close(userFd);
        free(filepath);
        return;
    }

    lseek(userFd, 0, SEEK_SET);
    struct user u;
    read(userFd, &u, sizeof(struct user));
    if(strcmp(password, u.password) != 0 || u.type != 1){
        write(nsd, invalidCredentials, sizeof invalidCredentials);
        close(userFd);
        free(filepath);
        return;
    }
    //else write success to client
    write(nsd, success, sizeof success);
    char choice[1] = "9";
    while(choice[0] != '6'){
        SYNC;
        write(nsd, normalMenuMsg, sizeof normalMenuMsg);
        //Read the choice from client
        read(nsd, choice, sizeof choice);
        SYNC;
        if(choice[0] == '1'){
            int amount;
            read(nsd, &amount, sizeof amount);
            u.balance += amount;
            lseek(userFd, 0, SEEK_SET);
            write(userFd, &u, sizeof u);
            printf("Amount deposited for: %s\n", userId);
        }
        else if(choice[0] == '2'){
            int amount;
            read(nsd, &amount, sizeof amount);
            u.balance -= amount;
            lseek(userFd, 0, SEEK_SET);
            write(userFd, &u, sizeof u);
            printf("Amount withdrawn for: %s\n", userId);
        }
        else if(choice[0] == '3'){
            write(nsd, &u.balance, sizeof u.balance);
            printf("\n");
        }
        else if(choice[0] == '4'){
            char passwd[20];
            read(nsd, &passwd, sizeof passwd);
            memcpy(u.password, passwd, sizeof u.password);
            lseek(userFd, 0, SEEK_SET);
            write(userFd, &u, sizeof u);
            printf("Password changed for: %s\n", userId);
        }
        else if(choice[0] == '5'){
            write(nsd, &u, sizeof u);
        }
    }

    close(userFd);
    free(filepath);
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

