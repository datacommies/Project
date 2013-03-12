#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include "../resource.h"
#include "server_game_logic.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <unistd.h>

#define MAX_CONNECTIONS 10
#define PORT_DEFAULT 4545

class ServerNetwork
{
public:
   // Constructors
   ServerNetwork(ServerGameLogic& serverGameLogic);
    
    // Functions
    void initNetwork();
    int initSock(int port = PORT_DEFAULT);
    static void* handleInput(void* args);
private:
    std::vector<player_matchmaking_t> players;
    std::vector<int> clients;       // client sockets
    pthread_t ui_thread;
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    long client;
    int sock;
    std::vector<pthread_t> threads; // client handler threads.
    
   // Module references
   ServerGameLogic& serverGameLogic_;

   // Functions
   bool sync(int); // TODO: clientId is a placeholder. May be a socket or something else
    void error(const char *);
    
    void handleClient();
    void handleRequests();
    int recv_complete(int,void*,size_t,int);
    
};

#endif