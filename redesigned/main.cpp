#include <iostream>
#include "resource.h"
#include "team.h"
#include "units/castle.h"
#include "units/mobile_unit.h"
#include "units/creep.h"
#include "units/player.h"
#include "units/tower.h"
#include "units/unit.h"
#include "modules/ai.h"
#include "modules/client_game_logic.h"
#include "modules/client_network.h"
#include "modules/control.h"
#include "modules/graphics.h"
#include "modules/server_game_logic.h"
#include "modules/server_network.h"
#include "modules/client.h"
#include "modules/server.h"

enum Role
{
   CLIENT,
   SERVER
};

int main()
{   
   Role role = CLIENT; // TODO: actually get role
 
   if (role == CLIENT)
      Client();
   else
      Server();
   return 0;
}