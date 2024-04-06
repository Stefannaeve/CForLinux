#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <server.h>

int server(){
    struct sockaddr_in saAddr = {0};
    struct sockaddr_in saConClient = {0};

    int sockFd;
    int sockNewFd = 0;
    int iPort = 8000;
    int readValue;
    int addrLen = sizeof(saAddr);
    char buffer[256];

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0){
        printf("socket failed with %i\n", errno);
    } else {
        printf("Socket sucsessfully created with the id %d\n", sockFd);
    }

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0){
        printf("Failed to bind the socket. Error message: %s\n", strerror(errno));
    } else {
        printf("Socket successfully bound to IP address\n");
    }

    int irc = listen(sockFd, 5);

    printf("irc = %d\n", irc);

    sockNewFd = accept(sockFd, (struct sockaddr *) &saConClient, (socklen_t*) &addrLen);
    if(sockNewFd < 0){
        printf("Accept failed: Error message: %s\n", strerror(errno));
    } else {
        printf("Accept successfully handled\n");
    }

    // Set buffer to 0 and use it to read the value from client
    memset(buffer, 0, 256);
    readValue = read(sockNewFd, buffer, 256-1);
    if(readValue < 0){
        printf("Reading failed: Error message: %s\n", strerror(errno));
    } else {
        printf("%s\n", buffer);
    }

    close(sockFd);
    close(sockNewFd);
    // -1 is often seen as invalid
    sockFd = -1;
    sockNewFd = -1;

    return 0;
}