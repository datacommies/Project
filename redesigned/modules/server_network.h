#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include "../resource.h"
#include "server_game_logic.h"

class ServerNetwork
{
public:
   // Constructors
   ServerNetwork(ServerGameLogic& serverGameLogic) : serverGameLogic_(serverGameLogic) { }
private:
   // Module references
   ServerGameLogic& serverGameLogic_;

   // Functions
   bool sync(int clientId); // TODO: clientId is a placeholder. May be a socket or something else
};

#endif