#include "ai.h"

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running Ai module */
Ai::Ai(ServerGameLogic& serverGameLogicModule)
   : serverGameLogicModule_(serverGameLogicModule)
{
   // TODO: create a thread and begin processing
}

/* Handles an AI request to create a unit.
 *
 * PRE:     Create Unit UI element is available to user (AI).
 * POST:    Request for game logic to create unit has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::createUnit(int playerId, UnitType type, Point location)
{
   serverGameLogicModule_.receiveCreateUnitCommand(playerId, type, location);
}

/* Handles an AI request to move a player.
 *
 * PRE:     move player UI element is available to user (AI).
 * POST:    Request for game logic to move player has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::movePlayer(int playerId, Direction direction)
{
   serverGameLogicModule_.receiveMovePlayerCommand(playerId, direction);
}

/* Handles an AI request to attack.
 *
 * PRE:     Attack UI element is available to user (AI).
 * POST:    Request for game logic to attack has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::attack(int playerId, Direction direction)
{
   serverGameLogicModule_.receiveAttackCommand(playerId, direction);
}