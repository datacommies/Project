#ifndef AI_H
#define AI_H

#include "../resource.h"

class ServerGameLogic;

class Ai
{
public:
   // Constructors
   Ai(ServerGameLogic& serverGameLogicModule) : serverGameLogicModule_(serverGameLogicModule) { }
private:
   // Module references
   ServerGameLogic& serverGameLogicModule_;

   // Functions
   void createUnit(int playerId, UnitType type, Point location);
   void movePlayer(int playerId, Direction direction);
   void attack(int playerId, Direction direction);
};

#endif
