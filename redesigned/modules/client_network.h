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
   bool connectToServer();
   ClientGameLogic* gl;
   void recvReply();

   std::string connecting_status;

   //Lobby variables
   player_matchmaking_t team_l[5];
   player_matchmaking_t team_r[5];
   std::vector<player_matchmaking_t> waiting;

   //Lobby functions
   void player_update (player_matchmaking_t * p);
   void player_leave (player_matchmaking_t * p);
   void msg_mapname (char * map);
   void msg_chat (char * text);

   void sendReady () {
      player_matchmaking_t p = {{MSG_PLAYER_UPDATE, sizeof(player_matchmaking_t)}, {0}, 0, 0, 0, false};
      strcpy(p.name, "Test");
      p.role = 0;
      p.ready = true;
      send(connectsock, &p, sizeof(player_matchmaking_t), 0);
   }
   
   void setConnectionInfo (std::string name, std::string server, int port) {
     _name = name; _server = server; _port = port;
   }
private:
   // Connection parameters
   std::string _name, _server; 
   int _port;

   int connectsock;
};

#endif
