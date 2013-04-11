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
    int  recv_complete (int sockfd, void *buf, size_t len, int flags);
    bool update_all_clients(int message);
    static void* handle_single_client_lobby(void* thing);
    void * handle_client_lobby(void *);

    void gameOver(int client_, const int winner);
    void syncFirstTeam(int);
    void syncSecondTeam(int);
    void syncTeamCurrency(int, int);


private:
    int sock_;
    std::vector<int> clients_;       // client_ sockets
    pthread_t uiThread_, crThread_;
    std::vector<pthread_t> threads_; // client_ handler threads_.
    std::vector<player_matchmaking_t> players_;

    // Module references
    ServerGameLogic& serverGameLogic_;

    // Functions
    bool sync(int, int); // TODO: clientId is a placeholder. May be a socket or something else
    void error(const char *);
    
    static void* handleClient(void*);
    static void* handleClientRequest(void* args);
};



#endif
