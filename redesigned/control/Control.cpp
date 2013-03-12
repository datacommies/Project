#include "Control.h"

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: ControlRun
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int ControlRun()
--
-- RETURNS: Returns 0 on normal termination
--
-- NOTES: This is the main Control function that powers the Control Module
----------------------------------------------------------------------------------------------------------------------*/
int ControlRun()
{
	ControlManager manager;
	
	AddStates(manager);
	
	while(manager.CheckState() != 0);
	
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
	
	Controller startLobby(startButton, startLobbyFunction);
	menuState.AddController(startLobby);
	
	Controller exitGame(exitButton, exitGameFunction);
	menuState.AddController(exitGame);
	
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
	
	Controller moveLeft(0, sf::Keyboard::Left, NULL, CallMoveLeftEvent);
	playerState.AddController(moveLeft);
	
	Controller moveRight(0, sf::Keyboard::Right, NULL, CallMoveRightEvent);
	playerState.AddController(moveRight);
	
	Controller moveUp(0, sf::Keyboard::Up, NULL, CallMoveUpEvent);
	playerState.AddController(moveUp);
	
	Controller moveDown(0, sf::Keyboard::Down, NULL, CallMoveDownEvent);
	playerState.AddController(moveDown);
	
	Controller attackLeft(0, sf::Keyboard::Left, NULL, CallAttackLeftEvent);
	playerState.AddController(attackLeft);
	
	Controller attackRight(0, sf::Keyboard::Right, NULL, CallAttackRightEvent);
	playerState.AddController(attackRight);
	
	Controller attackUp(0, sf::Keyboard::Up, NULL, CallAttackUpEvent);
	playerState.AddController(attackUp);
	
	Controller attackDown(0, sf::Keyboard::Down, NULL, CallAttackDownEvent);
	playerState.AddController(attackDown);
	
	Controller exitGame(EXIT_MENU_ID, NULL, exitGameButton(), NULL);
	playerState.AddController(exitGame);
	
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
	
	Controller buildTower(0, sf::Keyboard::B, buildTowerButton(), CallBuildTowerEvent);
	builderState.AddController(buildTower);
	
	Controller buildCreep(0, sf::Keyboard::C, buildCreepButton(), CallBuildCreepEvent);
	builderState.AddController(buildCreep);
	
	Controller exitGame(EXIT_MENU_ID, NULL, exitGameButton(), NULL);
	playerState.AddController(exitGame);
	
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
	ControlState exitState(false, 50);
	
	Controller returnToPreviousState(LAST_STATE, NULL, returnButton(), NULL);
	exitState.AddController(returnToPreviousState);
	
	Controller exitGame(TERMINATE, NULL, exitButton(), CallExitGameEvent);
	exitState.AddController(exitGame);
	
	return exitState;
}
