/*------------------------------------------------------------------------------
-- FILE:        ai.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: 
--
-- FUNCTIONS:
--              
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
#include "ai.h"
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
Ai::Ai(ServerGameLogic& serverGameLogicModule)
   : serverGameLogicModule_(serverGameLogicModule)
{
   // TODO: create a thread and begin processing
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Ai::createUnit(int unitId, UnitType type, Point location, Point destination)
{
   //serverGameLogicModule_.receiveCreateUnitCommand(unitId, type, location);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Ai::moveUnit(int unitId, Direction direction)
{
   //serverGameLogicModule_.receiveMoveUnitCommand(unitId, direction);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void Ai::attack(int unitId, Direction direction)
{
   serverGameLogicModule_.receiveAttackCommand(unitId, direction);
}
/*------------------------------------------------------------------------------
-- FUNCTION:   
--
-- DATE:        2013/03/22
--
-- DESIGNER:   
-- PROGRAMMER: 
--
-- INTERFACE:   
--
-- RETURNS:     
--
-- DESCRIPTION: 
------------------------------------------------------------------------------*/
void UpdateAI(Team &team1, Team &team2)
{
 
}
