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

#define MAX_CONNECTIONS 10
#define PORT_DEFAULT 4545

class ServerNetwork
{
public:
   // Constructors
   ServerNetwork(ServerGameLogic& serverGameLogic);
    
    // Functions

private:
   // Module references
   ServerGameLogic& serverGameLogic_;

   // Functions
   bool sync(int); // TODO: clientId is a placeholder. May be a socket or something else
    void error(const char *);
    int initSock(int port = PORT_DEFAULT);
    void handleClient();
    void handleRequests();
    int recv_complete(int,void*,size_t,int);
};

#endif