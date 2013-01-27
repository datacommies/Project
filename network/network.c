#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "types.h"

int recv_complete (int sockfd, void *buf, size_t len, int flags) {
    int bytesRead = 0;
    int result;

    while (bytesRead < len) {
        result = recv (sockfd, buf + bytesRead, len - bytesRead, flags);
        if (result < 1)
            return -1;
        bytesRead += result;
    }

    return bytesRead;
}

