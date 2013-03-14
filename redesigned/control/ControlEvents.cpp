
#include "ControlEvents.h"
using namespace std;

std::vector<int> pressedButtonIds;
ClientGameLogic* _gameLogicPointer;

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: loadControlEvents
--
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void loadControlEvents(ClientGameLogic &gameLogic)
--            ClientGameLogic &gameLogic - Stores a 'local' instance of GameLogic for referencing in /modules/Control.h
--
-- RETURNS: void
--
-- NOTES: Gets a pointer to gameLogic
----------------------------------------------------------------------------------------------------------------------*/
void loadControlEvents(ClientGameLogic* gameLogic)
{
	_gameLogicPointer = gameLogic;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallExitGameEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallExitGameEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for Exiting the Game.
----------------------------------------------------------------------------------------------------------------------*/
void CallExitGameEvent(void* value)
{
	
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallEnterLobbyEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallEnterLobbyEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for Entering the lobby form the startup menu.
----------------------------------------------------------------------------------------------------------------------*/
void CallEnterLobbyEvent(void* value)
{
	
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallMoveLeftEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallMoveLeftEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for Moving left when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallMoveLeftEvent(void* value)
{
	_gameLogicPointer->movePlayer(LEFT);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallMoveRightEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallMoveRightEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for Moving right when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallMoveRightEvent(void* value)
{
	_gameLogicPointer->movePlayer(RIGHT);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallMoveUpEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallMoveUpEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for Moving Up when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallMoveUpEvent(void* value)
{
	_gameLogicPointer->movePlayer(UP);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallMoveDownEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallMoveDownEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for Moving Down when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallMoveDownEvent(void* value)
{
	_gameLogicPointer->movePlayer(DOWN);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallAttackLeftEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallAttackLeftEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for attacking Left when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallAttackLeftEvent(void* value)
{
	_gameLogicPointer->attack(LEFT);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallAttackRightEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallAttackRightEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for attacking Right when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallAttackRightEvent(void* value)
{
	_gameLogicPointer->attack(RIGHT);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallAttackUpEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallAttackUpEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for attacking Up when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallAttackUpEvent(void* value)
{
	_gameLogicPointer->attack(UP);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallAttackDownEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallAttackDownEvent(void* value)
--            void* value - This is not used but must be present for the purpose of function pointers
--
-- RETURNS: void
--
-- NOTES: Calls the event for attacking Down when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void CallAttackDownEvent(void* value)
{
	_gameLogicPointer->attack(DOWN);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallBuildTowerEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallBuildTowerEvent(void* value)
--            void* value - This contains 2 integers, the X and Y values for where the tower is wanted to be built, in that order
--
-- RETURNS: void
--
-- NOTES: Calls the event building a tower and passes in the desired position.
----------------------------------------------------------------------------------------------------------------------*/
void CallBuildTowerEvent(void* value)
{
	int x = ((int *)value)[0];
	int y = ((int *)value)[1];
	Point location;
	location.x = x;
	location.y = y;
	
	_gameLogicPointer->createUnit(TOWER, location);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallBuildCreepEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallBuildCreepEvent(void* value)
--
-- RETURNS: void
--
-- NOTES: Calls the event for building a Creep
----------------------------------------------------------------------------------------------------------------------*/
void CallBuildCreepEvent(void* value)
{
	Point location;
	location.x = 0;
	location.y = 0;
	
	_gameLogicPointer->createUnit(CREEP, location);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AddNewCalledButton
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void AddNewCalledButton(int id)
--            int id - The id for the button that was pressed
--
-- RETURNS: void
--
-- NOTES: adds a new id to the list of butons that have been presed
----------------------------------------------------------------------------------------------------------------------*/
void AddNewCalledButton(int id)
{
	pressedButtonIds.push_back(id);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: getCalledButton
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: bool getCalledButton(int id)
--            int id - The id for the button that was pressed
--
-- RETURNS: Returns true on found button press, otherwise false
--
-- NOTES: Checks through the pressedButton list for a matching ID to id. If it is found it returns true and removes that
--        ID from the list. Otherwise it returns false.
----------------------------------------------------------------------------------------------------------------------*/
bool getCalledButton(int id)
{
	for(vector<int>::iterator i = pressedButtonIds.begin(); i != pressedButtonIds.end(); ++i)
	{
		if(*i == id)
		{
			pressedButtonIds.erase(i);
			return true;
		}
	}
	
	return false;
}
