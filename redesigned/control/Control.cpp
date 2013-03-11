#include "Control.h"

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: Control
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int Control()
--
-- RETURNS: Returns 0 on normal termination
--
-- NOTES: This is the main Control function that powers the Control Module
----------------------------------------------------------------------------------------------------------------------*/
int Control()
{
	ControlManager manager;
	
	while(manager.CheckState());
	
	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AddStates
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void AddStates(ControlManager &manager)
--            ControlManager &manager - This is a reference to the ControlManager for the purpose of loading it with States
--
-- RETURNS: void
--
-- NOTES: This adds a list of states to the ControlManager passed in
----------------------------------------------------------------------------------------------------------------------*/
void AddStates(ControlManager &manager)
{
	manager.AddNewState(MakeMenuState());
	manager.AddNewState(MakeLobbyState());
	manager.AddNewState(MakeBuilderState());
	manager.AddNewState(MakePlayerState());
	manager.AddNewState(MakeExitGameState());
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MakeMenuState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: ControlState MakeMenuState()
--
-- RETURNS: the State for MenuState
--
-- NOTES: This creates the menuState and loads it with all relevent Controllers
----------------------------------------------------------------------------------------------------------------------*/
ControlState MakeMenuState()
{
	ControlState menuState(true, 10);
	
	return menuState;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MakeLobbyState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: ControlState MakeLobbyState()
--
-- RETURNS: The state for LobbyState
--
-- NOTES: This creates the lobbyState and loads it with all relevent Controllers
----------------------------------------------------------------------------------------------------------------------*/
ControlState MakeLobbyState()
{
	ControlState lobbyState(true, 20);
	
	return lobbyState;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MakePlayerState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: ControlState MakePlayerState()
--
-- RETURNS: The state for PlayerState
--
-- NOTES: This creates the playerState and loads it with all relevent Controllers
----------------------------------------------------------------------------------------------------------------------*/
ControlState MakePlayerState()
{
	ControlState playerState(true, 30);
	
	return playerState;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MakeBuilderState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: ControlState MakeBuilderState()
--
-- RETURNS: The state for BuilderState
--
-- NOTES: This creates the builderState and loads it with all relevent Controllers
----------------------------------------------------------------------------------------------------------------------*/
ControlState MakeBuilderState()
{
	ControlState builderState(true, 40);
	
	return builderState;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MakeExitGameState
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: ControlState MakeExitGameState()
--
-- RETURNS: The state for ExitGameState
--
-- NOTES: This creates the exitGameState and loads it with all relevent Controllers
----------------------------------------------------------------------------------------------------------------------*/
ControlState MakeExitGameState()
{
	ControlState exitState(true, 50);
	
	return exitState;
}
