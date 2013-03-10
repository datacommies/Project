#ifndef AI_H
#define AI_H

#include "../resource.h"
#include "client_game_logic.h"

class Ai
{
public:
   // Constructors
   Ai(ClientGameLogic& clientGameLogicModule) : clientGameLogicModule_(clientGameLogicModule) { }
private:
   // Module references
   ClientGameLogic& clientGameLogicModule_;

   // Functions
   void createUnit(UnitType type, Point location);
   void movePlayer(Direction direction);
   void attack(Direction direction);
};

#endif