#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#include "../resource.h"
#include <queue>
#include "../team.h"

class ServerGameLogic
{
public:
   // Constructors
   ServerGameLogic() : serverNetwork_(this), ai_(this) { }

   // Fields
   Team teams[2];
   std::queue<void*> requestedCommands; // TODO: This shouldn't be a void* - using as a placeholder

   // Functions
   void startGame();
   void receiveCreateUnitCommand(int playerId, UnitType type, Point location);
   void receiveMovePlayerCommand(int playerId, Direction direction);
   void receiveAttackCommand(int playerId, Direction direction);   
private:
   // Modules
   ServerNetwork serverNetwork_;   
   AI ai_;   

   // Functions
   void update();
};

#endif