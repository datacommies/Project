#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "types.h"

void error (const char *msg) {
    perror(msg);
    exit(1);
}


/* Receive len amount of byte completely (no partial recv) */
int recv_complete (int sockfd, void *buf, size_t len, int flags) {
    size_t bytesRead = 0;
    int result;

    while (bytesRead < len) {
        result = recv (sockfd, (char*)buf + bytesRead, len - bytesRead, flags);
        if (result < 1) {
            return -1;
        }
        bytesRead += result;
    }

    return bytesRead;
}


/* Start server. By default port = 4545 */
int server (int port) {
    struct sockaddr_in serv_addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);;
    if (sock < 0)
        error("ERROR opening socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sock, 5);

    return sock;
}

