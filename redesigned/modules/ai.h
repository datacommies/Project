#ifndef AI_H
#define AI_H

#include "../resource.h"
#include "server_game_logic.h"
#include "../team.h"

class Ai
{
public:
   // Constructors
   Ai(ServerGameLogic& serverGameLogicModule);
private:
   // Module references
   ServerGameLogic& serverGameLogicModule_;

   // Functions
   void createUnit(int unitId, UnitType type, Point location, Point destination);
   void moveUnit(int unitId, Direction direction);
   void attack(int unitId, Direction direction);
   void UpdateAI(Team &team[]);
};

#endif
