#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <iostream>
#include "../resource.h"
#include "../types.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

class ClientGameLogic;

class ClientNetwork
{
public:
   

   // Constructors
   ClientNetwork();
   ~ClientNetwork();

   // Functions
   bool createUnit(int playerId, UnitType type, Point location, int path);
   bool movePlayer(int playerId, Direction direction);
   bool attack(int playerId, Direction direction);

   int sendRequest(int msg);
   bool connectToServer(std::string hostname, int port);
   ClientGameLogic* gl;
   void recvReply();

   //void behnamspartyfunction();
   
   //Lobby variables
   player_matchmaking_t team_l[5];
   player_matchmaking_t team_r[5];
   std::vector<player_matchmaking_t> waiting;

   //Lobby functions
   void player_update (player_matchmaking_t * p);
   void player_leave (player_matchmaking_t * p);
   void msg_mapname (char * map);
   void msg_chat (char * text);

private:
   int connectsock;

   
   
};

#endif
