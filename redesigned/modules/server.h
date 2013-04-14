#ifndef SERVER_H
#define SERVER_H

#include "../resource.h"
#include "server_game_logic.h"
#include "server_network.h"

class Server
{
public:
   // Constructors
   Server();
   
   // Functions
   void run();
private:

   // Modules
   ServerGameLogic serverGameLogic_;
   ServerNetwork serverNetwork_;
};

#endif