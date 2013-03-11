#ifndef CONTROL_H
#define CONTROL_H

#include "../resource.h"
#include "client_game_logic.h"

class ClientGameLogic;

class Control
{
public:
   // Constructors
   Control(ClientGameLogic& clientGameLogicModule);
private:
   // Module references
   ClientGameLogic& clientGameLogicModule_;
      
   // Functions
   void createUnit(UnitType type, Point location);
   void movePlayer(Direction direction);
   void attack(Direction direction);
};

#endif