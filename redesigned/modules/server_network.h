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
    friend bool operator == (const player_matchmaking_t&, const player_matchmaking_t&);
    
    bool update_all_clients(int message);
    static void* handle_single_client_lobby(void* thing);
    void * handle_client_lobby(void *);

    void gameOver(int client_, const int winner);

private:
    int sock_;
    std::vector<int> clients_;       // client_ sockets
    pthread_t uiThread_, crThread_;
    std::vector<pthread_t> threads_; // client_ handler threads_.
    std::vector<player_matchmaking_t> players_;

    // Module references
    ServerGameLogic& serverGameLogic_;

    // Functions
    bool sync(int); // TODO: clientId is a placeholder. May be a socket or something else
    void error(const char *);
    
    static void* handleClient(void*);
    static void* handleClientRequest(void* args);
    void handleRequests();
};

int recv_complete(int,void*,size_t,int);

#endif
