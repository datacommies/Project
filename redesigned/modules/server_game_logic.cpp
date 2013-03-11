#include "server_game_logic.h"

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
}

/* Receive and queue a move player command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * RETURNS: 
 * NOTES:   No validation is performed here. */
void ServerGameLogic::receiveMovePlayerCommand(int playerId, Direction direction)
{
}

/* Receive and queue an attack command from a client.
 *
 * PRE:     Game is active.
 * POST:    Command has been queued.
 * RETURNS: 
 * NOTES:   No validation is performed here. */
void ServerGameLogic::receiveAttackCommand(int playerId, Direction direction)
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
}