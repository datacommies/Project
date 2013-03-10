#ifndef AI_H
#define AI_H

#include "../resource.h"

class ServerGameLogic;

class Ai
{
public:
   // Constructors
   Ai(ServerGameLogic& clientGameLogicModule) : clientGameLogicModule_(clientGameLogicModule) { }
private:
   // Module references
   ServerGameLogic& clientGameLogicModule_;

   // Functions
   void createUnit(UnitType type, Point location);
   void movePlayer(Direction direction);
   void attack(Direction direction);
};

#endif