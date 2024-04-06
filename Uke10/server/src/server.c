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

    /*for (int i = 0; i < 1000; ++i) {
        printf("%i ", i);
    }*/

    /*if (iPort <= 0 || iPort >= 65535) {
        printf("This port doesn't exist.\n");
        return 1;
    }*/

    printf("2\n");


    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0){
        printf("socket failed with %i\n", errno);
    } else {
        printf("Socket sucsessfully created with the id %d\n", sockFd);
    }

    printf("3\n");

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0){
        printf("Failed to bind the socket. Error message: %s\n", strerror(errno));
    } else {
        printf("Socket successfully bound to IP address\n");
    }

    printf("4\n");

    int irc = listen(sockFd, 5);

    printf("sockFd = %d\n", sockFd);

    printf("irc = %d\n", irc);

    printf("5\n");


    sockNewFd = accept(sockFd, (struct sockaddr *) &saAddr, (socklen_t*) &addrLen);
    if(sockNewFd < 0){
        printf("Accept failed: Error message: %s\n", strerror(errno));
    } else {
        printf("Accept successfully handled");
    }
    printf("6\n");

    // Set buffer to 0 and use it to read the value from client
    memset(buffer, 0, 256);
    readValue = read(sockNewFd, buffer, 256-1);
    if(readValue < 0){
        printf("Reading failed: Error message: %s\n", strerror(errno));
    } else {
        printf("%s\n", buffer);
    }

    printf("7\n");

    close(sockFd);
    close(sockNewFd);
    // -1 is often seen as invalid
    sockFd = -1;
    sockNewFd = -1;

    return 0;
}