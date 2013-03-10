#include "ai.h"

/* Handles an AI request to create a unit.
 *
 * PRE:     Create Unit UI element is available to user (AI).
 * POST:    Request for game logic to create unit has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::createUnit(UnitType type, Point location)
{
   clientGameLogicModule_.createUnit(type, location);
}

/* Handles an AI request to move a player.
 *
 * PRE:     move player UI element is available to user (AI).
 * POST:    Request for game logic to move player has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::movePlayer(Direction direction)
{
   clientGameLogicModule_.movePlayer(direction);
}

/* Handles an AI request to attack.
 *
 * PRE:     Attack UI element is available to user (AI).
 * POST:    Request for game logic to attack has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::attack(Direction direction)
{
   clientGameLogicModule_.attack(direction);
}