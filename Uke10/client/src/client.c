#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <../include/client.h>

#define BUFFERSIZE 1024

int client(int argc, char *argv[]) {

    if (argc < 5) {
        printf("Wrong number of arguments, there should be 5\n");
        return 1;
    }

    struct sockaddr_in saAddr = {0};

    int sockFd;
    int iPort;
    int readValue;
    int i = 0;
    int textWithNameLength;
    int value;
    char buffer[BUFFERSIZE];
    char *beforeName = "HELO ";
    char *afterName= ", 127.0.0.1";
    char *name;
    char *textWithName;

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

    textWithNameLength = (strlen(beforeName) + strlen(name) + strlen(afterName) + 1);

    textWithName = (char *) malloc(textWithNameLength);
    memset(textWithName, 0, textWithNameLength);

    if (!textWithName) {
        free(name);
        printf("Error allocating memory\n");
        return 1;
    }
    snprintf(textWithName, textWithNameLength, "%s%s%s", beforeName, name, afterName);
    free(name);

    char *msg[] = {
            "HELO Stefan, 127.0.0.1",
            "MAIL FROM: <stefan.naeve@hotmail.com>",
            "RCPT TO: <amund.myrnokka@gay.no",
            "Hei, du din fjøsnisse",
            "Test",
            "QUIT"
    };

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        free(textWithName);
        printf("Failed to create endpoint and retrieve file descriptor - Error message %s\n", strerror(errno));
        return 1;
    }
    printf("Successfully created endpoint with socket\n");

    saAddr.sin_family = AF_INET;
    saAddr.sin_port = htons(iPort);
    saAddr.sin_addr.s_addr = htonl(0x7F000001); //Home

    if (connect(sockFd, (struct sockaddr *) &saAddr, sizeof(saAddr)) < 0) {
        free(textWithName);
        close(sockFd);
        sockFd = -1;
        printf("Connection failed: Error message: %s\n", strerror(errno));
    }
    printf("Connect successfully handled\n");


    memset(buffer, 0, BUFFERSIZE);
    while (1) {
        readValue = read(sockFd, buffer, BUFFERSIZE - 1);
        sleep(1);
        if (readValue < 0) {
            printf("Reading failed: Error message: %s\n", strerror(errno));
        } else {
            printf("%s\n", buffer);
        }
        value = send(sockFd, msg[i], strlen(msg[i]), 0);

        if (value < 0) {
            printf("Failed to transmit message - Error massage: %s", strerror(errno));
        }

        if (i > 4) {
            break;
        }
        memset(buffer, 0, BUFFERSIZE);
        i++;
    }
    read(sockFd, buffer, BUFFERSIZE - 1);
    printf("%s\n", buffer);

    printf("Closing socket\n");

    free(textWithName);

    close(sockFd);
    sockFd = -1;

    return 0;
}
