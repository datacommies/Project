#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <strings.h>
#include <netdb.h>

#include "types.h"

using namespace std;

// Function Prototype(s)
void * init (void * nothing);

player_matchmaking_t team_l[5];
player_matchmaking_t team_r[5];
vector<player_matchmaking_t> waiting;
player_matchmaking_t empty = {{0, 0}, "Empty", 0, 0, 0, false};

void player_update (player_matchmaking_t * p) {
    printf("Player: %s\t" "Team: %d\t"
        "Role: %d\t" "Ready: %s\n",
        p->name, p->team,
        p->role, (p->ready ? "yes" : "no"));

    if (p->team == 1)
        team_l[p->role] = *p;
    else if (p->team == 2)
        team_r[p->role] = *p;
    else 
        waiting.push_back(*p);
}

void player_leave (player_matchmaking_t * p) {
    printf("Player Left: %s\n", p->name);

    // Remove player from the waiting list.
    if (p->team == 0) {
        waiting.erase(std::remove(waiting.begin(), waiting.end(), *p), waiting.end());
    } else {
        // Remove the player from the team arrays.
        if (p->team == 1){
            memcpy(team_l+p->role, &empty, sizeof(player_matchmaking_t));
        } else if (p->team == 2) {
            memcpy(team_r+p->role, &empty, sizeof(player_matchmaking_t));
        }
    }
}

void msg_mapname (char * map) {
    printf("Got map name: %s\n", map);
}

void msg_chat (char * text) {
    printf("message: %s\n", text);
}

int main(int argc, char *argv[])
{
    long sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 5) {
       fprintf(stderr,"usage %s hostname port clientname\n", argv[0]);
       exit(0);
    }

    for (int i = 0; i < 5; ++i)
    {
        memcpy(team_l+i, &empty, sizeof(player_matchmaking_t));
        memcpy(team_r+i, &empty, sizeof(player_matchmaking_t));
    }

    /*-- Connect ---------- */
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr,
            (char *)server->h_addr,
            server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    // Initialize a new player_matchmaking_t struct with default values,
    // then assign the appropriate values.
    player_matchmaking_t p = {{0, 0}, {0}, 0, 0, 0, false};
    strcpy(p.name, argv[3]);
    p.team = atoi(argv[4]);
    p.role = 0;
    p.ready = false;

    if ((n = write(sockfd, &p, sizeof(p))) < 0)
        error("ERROR writing to socket");

    send_chat(sockfd, "Hello server!");
    pthread_t t;
    pthread_create(&t, NULL, init, (void*)sockfd);

    while (1) {
        header_t head;
        if ((n = recv_complete(sockfd, &head, sizeof(head), 0)) < 0)
            error("Disconnect");

        // [Jesse]: I'm probably going to change this to a switch statement
        // at some point in time.  It displeases me in its current state.
        
        /*
            ^ Would this one do?
            
            while (1) {
            header_t head;
            if ((n = recv_complete(sockfd, &head, sizeof(head), 0)) < 0)
                error("Disconnect");
                
            switch(head.type){
            case MSG_PLAYER_UPDATE:
                player_matchmaking_t p;
                p.head = head;
                n = recv_complete(sockfd, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);
    
                player_update(&p);
    			
    			continue;
                
        	case MSG_PLAYER_LEAVE:
            	player_matchmaking_t p;
                p.head = head;
                n = recv_complete(sockfd, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);
    
                player_leave(&p);
                
                continue;
                
            case MSG_MAPNAME:
                //n = recv_complete(sockfd, ((char*)&m + sizeof(head)), sizeof(map_t) - sizeof(head), 0);
                char m[MAP_NAME_SIZE] = {0};
                if ((n = recv_complete(sockfd, m, MAP_NAME_SIZE, 0)) > 0)
                    msg_mapname(m);
                    
                continue;
                
            case MSG_CHAT:
                char * m = (char *) malloc (head.size);
                n = recv_complete(sockfd, m, head.size, 0);
                m[n] = 0;
                msg_chat(m);
                free(m);
        
            
            }
            
        }
        */
        if (head.type == MSG_PLAYER_UPDATE) {
            player_matchmaking_t p;
            p.head = head;
            n = recv_complete(sockfd, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);

            player_update(&p);

        } else if (head.type == MSG_PLAYER_LEAVE) {
            player_matchmaking_t p;
            p.head = head;
            n = recv_complete(sockfd, ((char*)&p) + sizeof(head), sizeof(p) - sizeof(head), 0);

            player_leave(&p);

        } else if (head.type == MSG_MAPNAME) {
            //n = recv_complete(sockfd, ((char*)&m + sizeof(head)), sizeof(map_t) - sizeof(head), 0);
            char m[MAP_NAME_SIZE] = {0};
            if ((n = recv_complete(sockfd, m, MAP_NAME_SIZE, 0)) > 0)
                msg_mapname(m);
        } else if (head.type == MSG_CHAT) {
            char * m = (char *) malloc (head.size);
            n = recv_complete(sockfd, m, head.size, 0);
            m[n] = 0;
            msg_chat(m);
            free(m);
        }
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);

    return 0;
}


