#ifndef SERVERGAMELOGIC_H
#define SERVERGAMELOGIC_H

#include "../resource.h"
#include <string>
#include <queue>
#include "../team.h"

enum Command { Create, Move, Attack };

struct CommandData {
  Command cmd;
  int playerId;
  UnitType type;
  Point location;
  Direction direction;
};
  
class ServerGameLogic
{
public:
   // Constructors
   ServerGameLogic();

   ~ServerGameLogic();

   // Fields
   Team teams[2];

   std::queue<CommandData> requestedCommands;

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
   void updateCreate(CommandData& command);
   void updateAttack(CommandData& command);
   void updateMove(CommandData& command);

};

#endif
