#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <iostream>
#include "../resource.h"
#include "../types.h"
#include "audio.h"


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
   int  recv_complete (int sockfd, void *buf, size_t len, int flags);
   bool updatePlayerLobby (int team, int role, const char* name, bool ready);
   void send_chatmsg(std::string msg);

   void sendReady () {
      strcpy(p.name, (_name+" - Ready").c_str());
      p.head.type = MSG_PLAYER_UPDATE;
      p.ready = true;
      send(connectsock, &p, sizeof(player_matchmaking_t), 0);
   }
   
   void setConnectionInfo (std::string name, std::string server, int port) {
     _name = name; _server = server; _port = port;
   }
   
   player_matchmaking_t p;

   // Connection parameters
   std::string _name, _server; 
   int _port;

   //chat parameters
   std::vector<std::string> chatbuffer_;
private:

   int connectsock;
    Audio audio_;
};

#endif
