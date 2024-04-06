#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <../include/client.h>

int client(){
    struct sockaddr_in saAddr = {0};
    int sockFd;
    int iPort = atoi("80");
    char *msg = "This is a message from client";

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0){
        printf("socket failed with %s\n", strerror(errno));
    }

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = htonl(0xF000001); //Home

    if(connect(sockFd, (struct sockaddr*) &saAddr, sizeof(saAddr)) < 0){
        printf("Connection failed: Error message: %s\n", strerror(errno));
    }

    send(sockFd, msg, strlen(msg), 0);

    close(sockFd);
    sockFd = -1;

    return 0;
}
