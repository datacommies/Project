#include <vector>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <netdb.h>

#include "types.h"

using namespace std;

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port clientname\n", argv[0]);
       exit(0);
    }
    //// connect
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    // connect.

    player_matchmaking_t p = {0};
    strcpy(p.name, argv[3]);
    p.team = 1;
    p.role = 2;
    p.ready = false;

    n = write(sockfd, &p, sizeof(p));
    if (n < 0) 
        error("ERROR writing to socket");

    while (1) {
        header_t head;
        n = recv_complete(sockfd, &head, sizeof(head), 0);
        if (n < 0)
            error("Disconnect");
        if (head.type == MSG_PLAYER_UPDATE_INFO) {
            player_matchmaking_t p;
            p.head = head;
            n = recv_complete(sockfd, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);
            if (n < 0) 
                error("ERROR reading from socket");
            printf("Player: %s\t"
                "team: %d\t"
                "role: %d\t"
                "ready: %s\n",
                p.name, p.team,
                p.role, (p.ready ? "yes" : "no"));
            //if (!p.more_players)
            //    break;
        } else if (head.type == MSG_MAPNAME) {
            //n = recv_complete(sockfd, ((char*)&m + sizeof(head)), sizeof(map_t) - sizeof(head), 0);
            char m[MAP_NAME_SIZE] = {0};
            n = recv_complete(sockfd, m, MAP_NAME_SIZE, 0);
            if (n > 0)
                printf("Got map name: %s\n", m);
        } else if (head.type == MSG_CHAT) {
            printf("got msgchat size: %d\n", head.size);
            char m[head.size];
            n = recv_complete(sockfd, m, head.size, 0);
            m[n] = 0;
            if (n > 0)
                printf("message: %s\n", m);
        }
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
    return 0;
}