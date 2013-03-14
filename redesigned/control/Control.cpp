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
--             Luke Tao
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
	sf::Font font;
	
	Button startButton(11, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Start Lobby");	
	Controller startLobby(LAST_STATE, (sf::Keyboard::Key)0, startButton, CallEnterLobbyEvent);
	menuState.AddController(startLobby);
	
	Button exitButton(12, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Exit Game");	
	Controller exitGame(LAST_STATE, (sf::Keyboard::Key)0, exitButton, CallExitGameEvent);
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
    sf::Font font;
	ControlState playerState(true, 30);
	
	Button emptyButton(0, sf::Vector2f(0, 0), sf::Vector2f(0, 0), font, "");	
	
	Controller moveLeft(0, sf::Keyboard::Left, emptyButton, CallMoveLeftEvent);
	playerState.AddController(moveLeft);
	
	Controller moveRight(0, sf::Keyboard::Right, emptyButton, CallMoveRightEvent);
	playerState.AddController(moveRight);
	
	Controller moveUp(0, sf::Keyboard::Up, emptyButton, CallMoveUpEvent);
	playerState.AddController(moveUp);
	
	Controller moveDown(0, sf::Keyboard::Down, emptyButton, CallMoveDownEvent);
	playerState.AddController(moveDown);
	
	Controller attackLeft(0, sf::Keyboard::Left, emptyButton, CallAttackLeftEvent);
	playerState.AddController(attackLeft);
		
	Controller attackRight(0, sf::Keyboard::Right, emptyButton, CallAttackRightEvent);
	playerState.AddController(attackRight);
	
	Controller attackUp(0, sf::Keyboard::Up, emptyButton, CallAttackUpEvent);
	playerState.AddController(attackUp);
	
	Controller attackDown(0, sf::Keyboard::Down, emptyButton, CallAttackDownEvent);
	playerState.AddController(attackDown);
	
	Button exitGameClick(31, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Exit Game");	
	Controller exitGame(EXIT_MENU_ID, (sf::Keyboard::Key) 0, exitGameClick, NULL);
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
--             Luke Tao
--
-- INTERFACE: ControlState MakeBuilderState()
--
-- RETURNS: The state for BuilderState
--
-- NOTES: This creates the builderState and loads it with all relevent Controllers
----------------------------------------------------------------------------------------------------------------------*/
ControlState MakeBuilderState()
{   
    sf::Font font;
    
	ControlState builderState(true, 40);
    
    Button buildTowerButton(41, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Build Tower");	
	Controller buildTower(0, sf::Keyboard::B, buildTowerButton, CallBuildTowerEvent);
	builderState.AddController(buildTower);
	
	Button buildCreepButton(42, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Build Creep");
	Controller buildCreep(0, sf::Keyboard::C, buildCreepButton, CallBuildCreepEvent);
	builderState.AddController(buildCreep);
	
	Button exitGameButton(43, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Exit Game");
	Controller exitGame(EXIT_MENU_ID, (sf::Keyboard::Key) 0, exitGameButton, NULL);
	builderState.AddController(exitGame);
	
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
--             Luke Tao
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
	
	sf::Font font;
	Button returnButton(51, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Resume Game");
	
	Controller returnToPreviousState(LAST_STATE, (sf::Keyboard::Key) 0, returnButton, NULL);
	exitState.AddController(returnToPreviousState);
	
	Button exitButton(52, sf::Vector2f(20,20), sf::Vector2f(40,40), font, "Exit");
	Controller exitGame(TERMINATE, (sf::Keyboard::Key) 0, exitButton, CallExitGameEvent);
	exitState.AddController(exitGame);
	
	return exitState;
}
