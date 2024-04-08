#include "../include/client.h"

int main() {
    int statusCode = client();
    if (statusCode != 0) {
        return 1;
    }
    return 0;
}