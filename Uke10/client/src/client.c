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
    int iPort = atoi("8000");
    char *msg = "This is a message from client";

    printf("1\n");

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0){
        printf("socket failed with %s\n", strerror(errno));
    } else {
        printf("Socket successfully bound to IP address\n");
    }

    printf("2\n");


    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = htonl(0xF000001); //Home

    if(connect(sockFd, (struct sockaddr*) &saAddr, sizeof(saAddr)) < 0){
        printf("Connection failed: Error message: %s\n", strerror(errno));
    } else {
        printf("Connect successfully handled");
    }

    printf("3\n");

    send(sockFd, msg, strlen(msg), 0);

    printf("4\n");
    close(sockFd);
    sockFd = -1;

    return 0;
}
