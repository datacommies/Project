#ifndef CLIENT_GAME_LOGIC_H
#define CLIENT_GAME_LOGIC_H

#include "../resource.h"
#include <map>
#include <set>
#include <vector>
#include "client_network.h"
#include "audio.h"

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
   void connecting();
   void join ();
   void menu ();
   void win ();
   void lose ();

   bool createTower(UnitType type, Point location);
   bool createCreep(UnitType type, int laneID);
   bool movePlayer(Direction direction);
   bool attack(Direction direction);
   void exitGame();
   
   // 
   // required because theres no reference to clientNetwork.
   void ready() {
      waitingForStart = true;
      clientNetwork_.sendReady();
   }

   bool waitingForStart;
   // Module References
   ClientNetwork& clientNetwork_;
   
   // Fields
   GameState gameState_;
private:

   Audio audio_;

};

#endif
