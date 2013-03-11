#ifndef CLIENT_GAME_LOGIC_H
#define CLIENT_GAME_LOGIC_H

#include "../resource.h"
#include <vector>
#include <map>
#include "client_network.h"

class ClientGameLogic
{
public:
   // Constructor
   ClientGameLogic(ClientNetwork& clientNetwork);

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
   // Module References
   ClientNetwork& clientNetwork_;

   // Fields
   GameState gameState_;
};

#endif