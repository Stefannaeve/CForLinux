#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <server.h>

#define BUFFERSIZE 1024

int server(int argc, char *argv[]) {

    if (argc < 5) {
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
    int textWithNameLength;
    char buffer[BUFFERSIZE];
    char *name;
    char *textWithName;
    char *text = "250 Hello ";

    if (strcmp(argv[1], "-port") != 0) {
        printf("first argument should be \"-port\"\n");
        return 1;
    }

    iPort = atoi(argv[2]);

    if (strcmp(argv[3], "-name") != 0) {
        printf("second argument should be \"-name\"\n");
        return 1;
    }

    if (strlen(argv[4]) > 1024) {
        printf("-name variable size is to long, max char size is 1024");
        return 1;
    }

    name = (char *) malloc(strlen(argv[4]) + 1);
    memset(name, 0, (strlen(argv[4]) + 1));
    if (!name) {
        printf("Error allocating memory\n");
        return 1;
    }
    strncpy(name, argv[4], (strlen(argv[4]) + 1));

    textWithNameLength = (strlen(text) + strlen(name) + 1);

    textWithName = (char *) malloc(textWithNameLength);
    memset(name, 0, textWithNameLength);

    if (!textWithName) {
        free(name);
        printf("Error allocating memory\n");
        return 1;
    }

    strncpy(textWithName, text, (textWithNameLength));
    strncat(textWithName, name, (textWithNameLength));
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
    if (sockFd < 0) {
        printf("Failed to create endpoint and retrieve file descriptor - Error message %s\n", strerror(errno));
        return 1;
    }

    printf("Successfully created endpoint with socket\n");

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0) {
        printf("Failed to bind address and port to socket - Error message: %s\n", strerror(errno));
        return 1;
    }

    printf("Socket successfully bound to IP address and port\n");

    int irc = listen(sockFd, 5);

    if (irc < 0) {
        printf("Failed to find incoming connection through listen - Error message %i", strerror(errno));
        return 1;
    }

    sockNewFd = accept(sockFd, (struct sockaddr *) &saConClient, (socklen_t *) &addrLen);
    if (sockNewFd < 0) {
        printf("Failed to extract first connection request and create new socket - Error message: %s\n",
               strerror(errno));
        return 1;
    }

    printf("Successfully created new socket from connection request\n");

    // Set buffer to 0 and use it to read the value from client
    memset(buffer, 0, BUFFERSIZE);
    while (1) {
        value = send(sockNewFd, stringArray[i], strlen(stringArray[i]), 0);

        if (value < 0) {
            printf("Failed to transmit message - Error massage: %s", strerror(errno));
        }

        readValue = read(sockNewFd, buffer, BUFFERSIZE - 1);
        sleep(1);
        if (readValue < 0) {
            printf("Reading failed - Error message: %s\n", strerror(errno));
        } else {
            printf("%s\n", buffer);
        }
        i++;
        if (i > 5) {
            break;
        }
        memset(buffer, 0, BUFFERSIZE);
    }
    send(sockNewFd, stringArray[i], strlen(stringArray[i]), 0);

    printf("Closing socket\n");

    free(textWithName);
    free(name);

    close(sockFd);
    close(sockNewFd);
    // -1 is often seen as invalid
    sockFd = -1;
    sockNewFd = -1;

    return 0;
}