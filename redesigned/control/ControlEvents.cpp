
#include "ControlEvents.h"
using namespace std;

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
	int x = ((int)value)[0];
	int y = ((int)value)[1];
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
	
}

void AddNewCalledButton(int id)
{
	pressedButtonIds.pushBack(id);
}

bool getCalledButton(int id)
{
	for(vector<int>::iterator i = pressedButtonIds.front(); i != pressedButtonIds.back(); ++i)
	{
		if(*i == id)
		{
			pressedButtonIds.erase(i);
			return true;
		}
	}
	
	return false;
}
