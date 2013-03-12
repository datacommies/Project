#include "ControlManager.h"
using namespace std;

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: ControlManager
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: ControlManager()
--
-- RETURNS: n/a
--
-- NOTES: Initializes the ControlManager class. The members does most of the functionality.
----------------------------------------------------------------------------------------------------------------------*/
ControlManager::ControlManager() {}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AddNewState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void AddNewState(Control state)
--
-- RETURNS: void
--
-- NOTES: Adds a new control state. It will set the first state added to the list as the active state.
----------------------------------------------------------------------------------------------------------------------*/
void ControlManager::AddNewState(ControlState state)
{
	StateCollection.push_back(state);
	if(StateCollection.size() == 1)
	{
		activeState = &StateCollection[0];
	}
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CheckState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--           John Payment
--
-- PROGRAMMER: Luke Tao
--             John Payment
--
-- INTERFACE: int CheckState()
--
-- RETURNS: 0 on termination
--
-- NOTES: This function will check each state in the collection to match with the active state identifier. If it
--        finds a match, it will call the SetNewActiveState() function to set the current active state.
----------------------------------------------------------------------------------------------------------------------*/
int ControlManager::CheckState()
{
    
	int checkValue = 0;
	if((checkValue = activeState->CheckControllers()) > 0)
	{
	    if(checkValue == LAST_STATE)
	    {
	        checkValue = lastState;
	    } else if(checkValue == TERMINATE) 
	    {
	        return TERMINATE;
	    }
		for(vector<ControlState>::size_type i = 0; i < StateCollection.size(); i++)
		{
			if(checkValue == StateCollection[i].getIdentifier())
			{
			    lastState = StateCollection[i].getIdentifier();
				SetNewActiveState(&StateCollection[i]);
				return 0;
			}
		}	
	}
	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: SetNewActiveState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: void SetNewActiveState(ControlState * state)
--
-- RETURNS: n/a
--
-- NOTES: This function sets the state passed in as the new active state. If the new state override is set to true OR
--        the current active state is set to false, the active state will call UnloadGUIs. Afterwards, the new state
--	  will set the active state and reload the GUIs.
----------------------------------------------------------------------------------------------------------------------*/
void ControlManager::SetNewActiveState(ControlState * state)
{
	if(state->getOverride() || !activeState->getOverride())
	{
		activeState->UnloadGUIs();
		lastState = LAST_STATE;
	} 
	activeState = state;
	activeState->LoadGUIs();
}
