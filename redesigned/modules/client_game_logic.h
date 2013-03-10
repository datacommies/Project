#ifndef CLIENT_GAME_LOGIC_H
#define CLIENT_GAME_LOGIC_H

#include "../resource.h"
#include <vector>
#include <map>
#include "client_network.h"
#include "control.h"
#include "graphics.h"

struct CLIENT_UNIT // This struct applies only to the client side
{
   int id;
   int position;
   int health;
   int team;
   int type;
};

class ClientGameLogic
{
public:
   // Constructor
   ClientGameLogic() : clientNetwork_(), control_(this), graphics_(this) { }

   // Fields
   std::vector<CLIENT_UNIT> units;
   CLIENT_UNIT* map[MAPWIDTH][MAPHEIGHT];
   int playerId;
   int currency;

   // Functions
   bool createUnit(UnitType type, Point location);
   bool movePlayer(Direction direction);
   bool attack(Direction direction);
   void exit();
private:   
   // Modules
   ClientNetwork clientNetwork_;   
   Control control_;
   Graphics graphics_;
};

#endif