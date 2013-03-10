#include "control.h"

/* Handles a UI request to create a unit.
 *
 * PRE:     Create Unit UI element is available to user.
 * POST:    Request for game logic to create unit has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Control::createUnit(UnitType type, Point location)
{
   clientGameLogicModule_.createUnit(type, location);
}

/* Handles a UI request to move a player.
 *
 * PRE:     move player UI element is available to user.
 * POST:    Request for game logic to move player has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Control::movePlayer(Direction direction)
{
   clientGameLogicModule_.movePlayer(direction);
}

/* Handles a UI request to attack.
 *
 * PRE:     Attack UI element is available to user.
 * POST:    Request for game logic to attack has been sent.
 * RETURNS: 
 * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Control::attack(Direction direction)
{
   clientGameLogicModule_.attack(direction);
}