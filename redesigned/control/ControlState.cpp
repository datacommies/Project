#include "ControlState.h"
using namespace std;

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: ControlState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: ControlState()
--
-- RETURNS: n/a
--
-- NOTES: Initiallizes the ControlState class, including the _Override and _Identifier variables.
----------------------------------------------------------------------------------------------------------------------*/
ControlState::ControlState(bool override, int identifier)
:_Override(override)
,_Identifier(identifier)
{
	
}
	
/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: LoadGUIs
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void LoadGUIs()
--
-- RETURNS: void
--
-- NOTES: To be called when the State becomes active. Loads all Controllers into RenderManager.
----------------------------------------------------------------------------------------------------------------------*/
void 
ControlState::LoadGUIs()
{
	for(vector<Controller>::size_t i = 0; i < Controllers.size(); ++i)
	{
		Controllers[i].LoadGui();
	}
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: UnloadGUIs
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void UnloadGUIs()
--
-- RETURNS: void
--
-- NOTES: To be called when the State becomes inactive. Unloads all Controllers from the Render Manager.
----------------------------------------------------------------------------------------------------------------------*/
void 
ControlState::UnloadGUIs()
{
	for(vector<Controller>::size_t i = 0; i < Controllers.size(); ++i)
	{
		Controllers[i].UnloadGui();
	}
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AddController
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void AddController(Controlller control)
--            Controller control - The new controller to add to the State
--
-- RETURNS: void
--
-- NOTES: Adds a new controller to the controller colection.
----------------------------------------------------------------------------------------------------------------------*/
void
ControlState::AddController(Controller control)
{
	Controllers.push_back(control);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CheckControllers
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int CheckControllers()
--
-- RETURNS: The return value from the first confirmed hit in Controller.CheckController(). Returns 0 on no hits.
--
-- NOTES: Loops through each Controller, calling CheckController. If there are any hits it returns that CheckController's
--        return value. Otherwise it returns 0.
----------------------------------------------------------------------------------------------------------------------*/
int 
ControlState::CheckControllers()
{
	int returnValue = 0;
	
	for(vector<Controller>::size_t i = 0; i < Controllers.size(); ++i)
	{
		returnValue = Controllers[i].CheckController();
		if(returnValue > 0)
		{
			break;
		}
	}
	
	return returnValue;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: getOverride
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: bool getOverride()
--
-- RETURNS: The _Override variable
--
-- NOTES: Gets the State's _Override value
----------------------------------------------------------------------------------------------------------------------*/
bool 
ControlState::getOverride()
{
	return _Override;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: getIdentifier
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int getIdentifier()
--
-- RETURNS: The _Identifier variable
--
-- NOTES: Gets the State's _Identifier value
----------------------------------------------------------------------------------------------------------------------*/
int
ControlState::getIdentifier()
{
	return _Identifier;
}

