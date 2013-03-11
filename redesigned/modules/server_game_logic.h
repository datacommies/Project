#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#include "../resource.h"
#include <string>
#include <queue>
#include "../team.h"

class ServerGameLogic
{
public:
   // Constructors
   ServerGameLogic();

   // Fields
   Team teams[2];
   std::queue<void*> requestedCommands; // TODO: This shouldn't be a void* - using as a placeholder

   // Functions
   void startGame();
   void receiveCreateUnitCommand(int playerId, UnitType type, Point location);
   void receiveMovePlayerCommand(int playerId, Direction direction);
   void receiveMoveUnitCommand(int unitId, Direction direction);
   void receiveAttackCommand(int playerId, Direction direction);
   void playerConnect();

private:
   // Fields
   GameState gameState_;

   // Functions
   void update();
};

#endif