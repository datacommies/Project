#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "types.h"

using namespace std;

void error (const char *msg) {
    perror(msg);
    exit(1);
}

// Move me!
bool operator == (const player_matchmaking_t& a, const player_matchmaking_t& b) {
    return a.pid == b.pid;
}

/* Send a chat message. */
int send_chat ( int client, const string & body ) {
    header_t* msg = (header_t*) new char[sizeof(header_t) + body.size()];
    memset(msg, 0, sizeof(header_t) + body.size());
    msg->type = MSG_CHAT;
    msg->size = body.size();
    strcpy( ((char*)msg) + sizeof(header_t), body.c_str());

    int n = send(client, msg, sizeof(header_t) + body.size(), 0);
    delete msg;

    return n;
}

/* Receive len amount of byte completely (no partial recv) */
int recv_complete (int sockfd, void *buf, size_t len, int flags) {
    size_t bytesRead = 0;
    ssize_t result;

    while (bytesRead < len) {
        result = recv (sockfd, (char*)buf + bytesRead, len - bytesRead, flags);
        
        if (result < 1)
            error("recv");

        bytesRead += result;
    }

    return bytesRead;
}

/* Start server. By default port = 4545 */
int server (int port) {
    int ov = 1;
    struct sockaddr_in serv_addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);;
    if (sock < 0) 
        error("ERROR opening socket");

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ov, sizeof (ov));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sock, 5);
    return sock;
}

