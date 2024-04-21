#include "../include/client.h"

int main(int argc, char *argv[]) {
    int statusCode = client(argc, argv);
    if (statusCode != 0) {
        return 1;
    }
    return 0;
}