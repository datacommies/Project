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
- *
- * PRE:     Create Unit UI element is available to user (AI).
- * POST:    Request for game logic to create unit has been sent.
- * RETURNS: 
- * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::createUnit(int unitId, UnitType type, Point location, Point destination)
{
   serverGameLogicModule_.receiveCreateUnitCommand(unitId, type, location);
}

/* Handles an AI request to move a unit.
- *
- * PRE:     move unit UI element is available to user (AI).
- * POST:    Request for game logic to move unit has been sent.
- * RETURNS: 
- * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::moveUnit(int unitId, Direction direction)
{
   //serverGameLogicModule_.receiveMoveUnitCommand(unitId, direction);
}

/* Handles an AI request to attack.
- *
- * PRE:     Attack UI element is available to user (AI).
- * POST:    Request for game logic to attack has been sent.
- * RETURNS: 
- * NOTES:   Performs no validation. Validation is handled by game logic module. */
void Ai::attack(int unitId, Direction direction)
{
   serverGameLogicModule_.receiveAttackCommand(unitId, direction);
}

 /*
  * Updates all of the AI.
  */
