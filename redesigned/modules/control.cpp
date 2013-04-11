/*--------------------------------------------------------------------------------------------------------------------
-- FILE: control.cpp
--
-- FUNCTIONS: Control* get()
--            Control()
--            void LoadGameLogic()
--            void LoadGraphics()
--            void AddNewCalledButton()
--            void AddNewCalledKey()
--            void AddNewUnCalledKey()
--            void RunAllButtons()
--            void RunAllKeys()
--            voidCallExitGameEvent()
--            void CallEnterLobbyEvent()
--            void CallMoveEvent()
--            void CallUnitTypeCreationEvent()
--            int GetCurrentLane()
--            Point GetTowerPlacement()
--            void MouseCallback()
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment, Jesse Wright
--
-- PROGRAMMERS: John Payment
--              Jesse Wright
--
-- DESCRIPTION: File impliments all functions used by the control class, which is the primary structure of the Control
--              module. It manages registering keypress callbacks, handling button presses and mouse clicks, and all 
--              associated actions. Presses and mouse clicks, and all associated actions.
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "control.h"
#include <SFML/System.hpp>

using namespace std;

Control* Control::_Control = NULL;
int next_to_build = 0;


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
,_currentDirection(0)
,_clientGameLogicModule(NULL)
,_graphicsModule(NULL)
,_currentLane(0)
{
	// Constructor
	_towerPlacement.x = -1;
	_towerPlacement.y = -1;
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
	_keys.push_back(key);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AddNewUnCalledKey
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
--            sf::Keyboard::Key key - The key that was released
--
-- RETURNS: void
--
-- NOTES: adds a key to the list of keys that have been released
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::AddNewUnCalledKey(sf::Keyboard::Key key)
{
	_released_keys.push_back(key);
}
/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunAllButtons
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--          
--
-- DESIGNER: John Payment
--           Jesse Wright
--
-- PROGRAMMER: Jesse Wright
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
			case BUILDTOWER_1:
                next_to_build = TOWER_ONE;
			    cout << "Setting next to build tower one!" << endl;
			break;
			case BUILDTOWER_2:
                next_to_build = TOWER_TWO;
			    cout << "Setting next to build tower two!" << endl;
			break;    
			case BUILDTOWER_3:
                next_to_build = TOWER_THREE;
			    cout << "Setting next to build tower three!" << endl;
			break;    
			case BUILDCREEP_1:
			    _clientGameLogicModule->createCreep(CREEP, GetCurrentLane());
			 break;   
			case BUILDCREEP_2:
			    _clientGameLogicModule->createCreep(CREEP_TWO, GetCurrentLane());
			 break;  
			case BUILDCREEP_3:
			    _clientGameLogicModule->createCreep(CREEP_THREE, GetCurrentLane());
		    break;   
			case SELECTLOPATH:
   				_currentLane = LOWPATH;
   			break;
			case SELECTMIDPATH:
				_currentLane = MIDPATH;
   			break;
			case SELECTHIPATH:
			    _currentLane = HIGHPATH;
			break;
			case INFOBUTTON:
				_graphicsModule->toggleInfoButton();
			break;
			default:
			break;
				// Does nothing but gets rid of annoying warnings
		}
	}
	
	_buttonIDs.clear();
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunAllKeys
--
-- DATE: 2013/03/21
--
-- REVISIONS: Jesse Wright: Added attack after every movement.
--
-- DESIGNER: John Payment, Jesse Wright
--
-- PROGRAMMER: John Payment
--             Jesse Wright
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
	int old = _currentDirection;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_currentDirection |= UP;
	else
		_currentDirection &= (~UP);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_currentDirection |= LEFT;
	else
		_currentDirection &= (~LEFT);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_currentDirection |= DOWN;
	else
		_currentDirection &= (~DOWN);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_currentDirection |= RIGHT;
	else
		_currentDirection &= (~RIGHT);

	if (old != _currentDirection) {
		CallMoveEvent((Direction)_currentDirection);
	}
	
	_released_keys.clear();
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
-- FUNCTION: CallUnitTypeCreationEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: Jesse Wright: Changed fucntion to take a Unit type so we can have a more generic function for creating 
--                          units in the game. simply checks the unit type and calls the correct game logic function.
--
-- DESIGNER: John Payment
--           Jesse Wright
--
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE: Control::CallUnitTypeCreationEvent(UnitType unit_type)
--
-- RETURNS: void
--
-- NOTES: Calls the event correct event function for 
----------------------------------------------------------------------------------------------------------------------*/
void 
Control::CallUnitTypeCreationEvent(UnitType unit_type)
{
	// Need to define how to get tower build co-ordinates
	switch(unit_type)
	{
	    case TOWER_ONE:
	    case TOWER_TWO:
	    case TOWER_THREE:
	        _clientGameLogicModule->createTower(unit_type, GetTowerPlacement());
	    break;
		default:
		break;
	}
	
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: GetCurrentLane
--
-- DATE: 2013/03/20
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jesse Wright
--
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE: void GetCurrentLane()
--
-- RETURNS: Integer indicating whihc lane is the current building lane
--
-- NOTES: Returns the Current lane integer
----------------------------------------------------------------------------------------------------------------------*/
int 
Control::GetCurrentLane()
{
	return _currentLane;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: GetTowerPlacement
--
-- DATE: 2013/03/20
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jesse Wright
--
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE: void GetTowerPlacement()
--
-- RETURNS: Point indicating where a tower willbe placed
--
-- NOTES: Returns the TowerPlacement point
----------------------------------------------------------------------------------------------------------------------*/
Point 
Control::GetTowerPlacement()
{
	return _towerPlacement;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MouseCallback
--
-- DATE: 2013/03/20
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jesse Wright
--
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE: void MouseCallback(Point p)
--                 Point p - The point the tower is to be placed in
--
-- RETURNS: void
--
-- NOTES: This will be called after the player has clicked a tower button and is waiting for the field click. Sets the
-- towerPlacement variable in Control so we can pass it to game logic.
----------------------------------------------------------------------------------------------------------------------*/
void
Control::MouseCallback(Point p)
{
    p.x -= 25;
    p.y -= 25;
    _towerPlacement = p;

    if (next_to_build != 0)
        CallUnitTypeCreationEvent((UnitType)next_to_build);
    next_to_build = 0;
}
