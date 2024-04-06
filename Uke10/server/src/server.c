#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <server.h>

#define BUFFERSIZE 1024

int server(int argc, char *argv[]){

    if (argc < 5){
        printf("Wrong number of arguments, there should be 5\n");
        return 1;
    }

    struct sockaddr_in saAddr = {0};
    struct sockaddr_in saConClient = {0};

    int sockFd;
    int sockNewFd = 0;
    int iPort;
    int readValue;
    int addrLen = sizeof(saAddr);
    int i = 0;
    int value;
    char buffer[BUFFERSIZE];
    char *name;
    char *textWithName;
    char *text = "250 Hello ";

    if (strcmp(argv[1], "-port") != 0){
        printf("first argument should be \"-port\"");
        return 1;
    }

    iPort = atoi(argv[2]);

    if (strcmp(argv[3], "-name") != 0){
        printf("second argument should be \"-name\"");
        return 1;
    }

    name = (char *) malloc(strlen(argv[4]) + 1);
    if (!name) {
        printf("Error allocating memory\n");
        return 1;
    }
    strcpy(name, argv[4]);

    textWithName = (char *) malloc(strlen(text) + strlen(name) + 1);
    if (!textWithName) {
        free(name);
        printf("Error allocating memory\n");
        return 1;
    }

    strcpy(textWithName, text);
    strcat(textWithName, name);
    free(name);

    char *stringArray[] = {
            "220 127.0.0.1 ESMTP Postfix",
            textWithName,
            "250 Sender address Ok",
            "250 Recipent address Ok",
            "354 End data with <CR><LF>.<CR><LF>",
            "250 Message accepted, Ok",
            "221 127.0.0.1 closing connection"
    };

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd < 0){
        printf("socket failed with %i\n", errno);
        return 1;
    }

    printf("Socket sucsessfully created with the id %d\n", sockFd);

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0){
        printf("Failed to bind the socket. Error message: %s\n", strerror(errno));
        return 1;
    }

    printf("Socket successfully bound to IP address\n");

    int irc = listen(sockFd, 5);

    if(irc < 0){
        printf("Failed to listen find incoming connectino through listen: Error message %i", strerror(errno));
        return 1;
    }

    sockNewFd = accept(sockFd, (struct sockaddr *) &saConClient, (socklen_t*) &addrLen);
    if(sockNewFd < 0){
        printf("Accept failed: Error message: %s\n", strerror(errno));
        return 1;
    }

    printf("Accept successfully handled\n");

    // Set buffer to 0 and use it to read the value from client
    memset(buffer, 0, BUFFERSIZE);
    while(1){
        value = send(sockNewFd, stringArray[i], strlen(stringArray[i]), 0);

        readValue = read(sockNewFd, buffer, BUFFERSIZE-1);
        sleep(1);
        if(readValue < 0){
            printf("Reading failed: Error message: %s\n", strerror(errno));
        } else {
            printf("%s\n", buffer);
        }
        i++;
        if(i > 5){
            break;
        }
        memset(buffer, 0, BUFFERSIZE);
    }
    send(sockNewFd, stringArray[i], strlen(stringArray[i]), 0);

    printf("Closing socket\n");

    close(sockFd);
    close(sockNewFd);
    // -1 is often seen as invalid
    sockFd = -1;
    sockNewFd = -1;

    return 0;
}