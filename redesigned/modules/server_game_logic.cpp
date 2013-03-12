#include "server_game_logic.h"
//#include "semaphore.h"
//#include <sys/sem.h>

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
ServerGameLogic::ServerGameLogic()
   : gameState_(LOBBY) 
{ 
   // TODO: create a thread and begin processing


}

ServerGameLogic::~ServerGameLogic() 
{


}

/* Starts the game.
 *
 * PRE:     Game is in the lobby and players are ready.
 * POST:    Data structures and initialized and game is placed in an active state, with all appropriate modules processing.
 * RETURNS: 
 * NOTES:    */
void ServerGameLogic::startGame()
{
}

/* Receive and queue a create unit command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * RETURNS: 
 * NOTES:   No validation is performed here. */
void ServerGameLogic::receiveCreateUnitCommand(int playerId, UnitType type, Point location)
{
  CommandData newCommand;

  newCommand.cmd = Create;
  newCommand.playerId = playerId;
  newCommand.type = type;
  newCommand.location = location;

  requestedCommands.push(newCommand);
}

/* Receive and queue a move player command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * RETURNS: 
 * NOTES:   No validation is performed here. */
void ServerGameLogic::receiveMovePlayerCommand(int playerId, Direction direction)
{
  CommandData newCommand;

  newCommand.cmd = Move;
  newCommand.playerId = playerId;
  newCommand.direction = direction;

  requestedCommands.push(newCommand);
}

/* Receive and queue an attack command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * RETURNS: 
 * NOTES:   No validation is performed here. */
void ServerGameLogic::receiveAttackCommand(int playerId, Direction direction)
{
  CommandData newCommand;

  newCommand.cmd = Attack;
  newCommand.playerId = playerId;
  newCommand.direction = direction;
  
  requestedCommands.push(newCommand);
}

void ServerGameLogic::updateCreate(CommandData& command)
{

}

void ServerGameLogic::updateAttack(CommandData& command) 
{

}

void ServerGameLogic::updateMove(CommandData& command)
{

}

/* Processes all waiting commands.
 *
 * PRE:     
 * POST:    Command queue is cleared.
 * RETURNS: 
 * NOTES:   Perform validation here. 
 *          Nice to have: send a fail message if command is invalid */
void ServerGameLogic::update()
{

  if (requestedCommands.empty())
    return;

  CommandData newCommand = requestedCommands.front();
  requestedCommands.pop();

  switch (newCommand.cmd) {
    case Create:
      updateCreate(newCommand);
      break;
    case Attack:
      updateAttack(newCommand);
      break;
    case Move:
      updateMove(newCommand);
      break;
  }


  
}
/*
 * To test that this class compiles use  g++ -DTESTCOMPILE server_game_logic.cpp
 */
#ifdef TESTCOMPILE
int main() {}
#endif
