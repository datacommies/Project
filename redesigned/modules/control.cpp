#include "control.h"
#include "pthread.h"
#include <X11/Xlib.h>
#include <SFML/System.hpp>

using namespace std;

Control* Control::_Control = NULL;

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: get
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: Control* get()
--
-- RETURNS: A pointed to the Control Instance
--
-- NOTES: Returns a pointer to the control instance. If the instance has not yet been initialized, it does so.
----------------------------------------------------------------------------------------------------------------------*/
Control*
Control::get()
{
	if(_Control == NULL)
	{
		_Control = new Control();
	}
	
	return _Control;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: Control
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: Control()
--
-- RETURNS: N/A
--
-- NOTES: Constructor for Control Class
----------------------------------------------------------------------------------------------------------------------*/
Control::Control()
:_buttonIDs()
,_keys()
,_clientGameLogicModule(NULL)
,_graphicsModule(NULL)
{
	// Constructor
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: LoadGameLogic
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void LoadGameLogic(ClientGameLogic& clientGameLogicModule)
--                 ClientGameLogic* clientGameLogicModule - Pointer to the GameLogicModule
--
-- RETURNS: void
--
-- NOTES: Gets a reference to the GameLogic for Wrapper Functions
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::LoadGameLogic(ClientGameLogic* clientGameLogicModule)
{
	_clientGameLogicModule = clientGameLogicModule;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: LoadGraphics
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void LoadGraphics(Graphics* graphicsModule)
--                 Graphics& graphicsModule - Pointer to the Graphics
--
-- RETURNS: void
--
-- NOTES: Gets a reference to the Graphics for a few Wrapper Functions
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::LoadGraphics(Graphics* graphicsModule)
{
	_graphicsModule = graphicsModule;
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
-- NOTES: adds a new id to the list of butons that have been pressed
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::AddNewCalledButton(int id)
{
	std::cout << "Added new button call back" << std::endl;
	_buttonIDs.push_back(id);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AddNewCalledKey
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void AddNewCalledKey(sf::Keyboard::Key key)
--            sf::Keyboard::Key key - The key that was pressed
--
-- RETURNS: void
--
-- NOTES: adds a key to the list of keys that have been pressed
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::AddNewCalledKey(sf::Keyboard::Key key)
{
	std::cout << "Added new key call back" << std::endl;
	_keys.push_back(key);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunAllButtons
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void RunAllButtons()
--
-- RETURNS: void
--
-- NOTES: Checks every ID stored in the buttonID collection against a list of IDs. Calls a Wrapper function for each hit.
--        Then it empties the collection.
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::RunAllButtons()
{
	for(vector<int>::size_type i = 0; i < _buttonIDs.size(); ++i)
	{
		// Case for each Button ID
		switch(_buttonIDs[i])
		{
			case 0:
				break;
			// Need to define cases for Buttons
			default:
			break;
				// Does nothing but gets rid of annoying warnings
		}
	}
	
	_keys.clear();
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunAllKeys
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void RunAllKeys()
--
-- RETURNS: void
--
-- NOTES: Checks every key stored in the keys collection against a list of relevant keys. Calls a Wrapper function for each hit.
--        Then empties array the collection.
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::RunAllKeys()
{
	for(vector<sf::Keyboard::Key>::size_type i = 0; i < _keys.size(); ++i)
	{
		// Case for each Key that is attached to a function
		switch(_keys[i])
		{
			// Moving in Player Mode
			case sf::Keyboard::Left :
				CallMoveEvent(LEFT);
				break;
			case sf::Keyboard::Up :
				CallMoveEvent(UP);
				break;
			case sf::Keyboard::Right :
				CallMoveEvent(RIGHT);
				break;
			case sf::Keyboard::Down :
				CallMoveEvent(DOWN);
				break;
			// Attacking In Player Mode
			case sf::Keyboard::A :
				CallAttackEvent(LEFT);
				break;
			case sf::Keyboard::W :
				CallAttackEvent(UP);
				break;
			case sf::Keyboard::D :
				CallAttackEvent(RIGHT);
				break;
			case sf::Keyboard::S :
				CallAttackEvent(DOWN);
				break;
			case sf::Keyboard::Escape :
				CallExitGameEvent();
				break;
			default:
				break;
				// Does nothing but gets rid of annoying warnings
		}
	}
	
	_keys.clear();
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
-- INTERFACE: void CallExitGameEvent()
--
-- RETURNS: void
--
-- NOTES: Calls the event for Exiting the Game.
----------------------------------------------------------------------------------------------------------------------*/
void
Control::CallExitGameEvent()
{
	// Needs to be defined
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
-- INTERFACE: void CallEnterLobbyEvent()
--
-- RETURNS: void
--
-- NOTES: Calls the event for Entering the lobby form the startup menu.
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::CallEnterLobbyEvent()
{
	// Needs to be defined
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallMoveEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallMoveDownEvent(Direction direction)
--            Direction direction - The direction that you want to move in.
--
-- RETURNS: void
--
-- NOTES: Calls the event for Moving when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::CallMoveEvent(Direction direction)
{
	_clientGameLogicModule->movePlayer(direction);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CallAttackEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: void CallAttackLeftEvent(Direction direction)
--            Direction direction - The direction that you want to attack in.
--
-- RETURNS: void
--
-- NOTES: Calls the event for attacking when in player mode.
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::CallAttackEvent(Direction direction)
{
	_clientGameLogicModule->attack(direction);
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
-- INTERFACE: void CallBuildTowerEvent()
--
-- RETURNS: void
--
-- NOTES: Calls the event building a tower after finding the desired position.
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::CallBuildTowerEvent()
{
	// Need to define how to get tower build co-ordinates
	Point location;
	location.x = 0;
	location.y = 0;
	
	_clientGameLogicModule->createUnit(TOWER, location);
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
-- INTERFACE: void CallBuildCreepEvent()
--
-- RETURNS: void
--
-- NOTES: Calls the event for building a Creep
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::CallBuildCreepEvent()
{
	Point location;
	location.x = 0;
	location.y = 0;
	
	_clientGameLogicModule->createUnit(CREEP, location);
}
