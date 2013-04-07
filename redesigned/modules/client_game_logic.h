#ifndef CLIENT_GAME_LOGIC_H
#define CLIENT_GAME_LOGIC_H

#include "../resource.h"
#include <map>
#include <set>
#include <vector>
#include "client_network.h"

class ClientGameLogic
{
public:
   pthread_mutex_t unit_mutex;
   // Constructor
   ClientGameLogic(ClientNetwork& clientNetwork);

   // Fields
   std::vector<CLIENT_UNIT> units;
   CLIENT_UNIT* map[MAPWIDTH][MAPHEIGHT];
   int playerId;
   int currency;
   std::set<Button> UIElements;

   // Functions
   void updateUnits(CLIENT_UNIT unit);
   GameState getCurrentState();
   
   void start ();
   void join ();
   void menu ();

   bool createTower(UnitType type, Point location);
   bool createCreep(UnitType type, int laneID);
   bool movePlayer(Direction direction);
   bool attack(Direction direction);
   void exit();
   
   // 
   // required because theres no reference to clientNetwork.
   void ready() {
      clientNetwork_.sendReady();
   }
   // Module References
   ClientNetwork& clientNetwork_;
private:

   // Fields
   GameState gameState_;
};

#endif
