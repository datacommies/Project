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
,_clientGameLogicModule(NULL)
,_currentDirection(0)
,_graphicsModule(NULL)
,_currentLane(-1)
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
--          Jesse Wright: added button id's to the switch statements. 
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
                next_to_build = CREEP_ONE;
			    cout << "Setting next to build creep one!" << endl;
			 break;   
			case BUILDCREEP_2:
                next_to_build = CREEP_TWO;
			    cout << "Setting next to build creep two!" << endl;	
			 break;  
			case BUILDCREEP_3:
                next_to_build = CREEP_THREE;
			    cout << "Setting next to build creep three!" << endl;
		    break;   
			case SELECTLOPATH:	  
			case SELECTMIDPATH:
			case SELECTHIPATH:
			    _currentLane = _buttonIDs[i] - SELECTLOPATH;
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
			case sf::Keyboard::A :
				if (!(_currentDirection & LEFT))
					CallMoveEvent(LEFT);
				_currentDirection |= LEFT;
				break;
			case sf::Keyboard::W :
				if (!(_currentDirection & UP))
					CallMoveEvent(UP);
				_currentDirection |= UP;
				break;
			case sf::Keyboard::D :
				if (!(_currentDirection & RIGHT))
					CallMoveEvent(RIGHT);
				_currentDirection |= RIGHT;
				break;
			case sf::Keyboard::S :
				if (!(_currentDirection & DOWN))
					CallMoveEvent(DOWN);
				_currentDirection |= DOWN;
				break;
			// Attacking In Player Mode
	/*		case sf::Keyboard::A :
				CallAttackEvent(LEFT);
				break;
	/		case sf::Keyboard::W :
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
				*/
			default:
				break;
				// Does nothing but gets rid of annoying warnings
		}
	}

	for(vector<sf::Keyboard::Key>::size_type i = 0; i < _released_keys.size(); ++i)
	{
		bool update = true;
		// Case for each Key that is attached to a function
		switch(_released_keys[i])
		{
			// Moving in Player Mode
			case sf::Keyboard::A :
				_currentDirection &= (~LEFT);
				break;
			case sf::Keyboard::W :
				_currentDirection &= (~UP);
				break;
			case sf::Keyboard::D :
				_currentDirection &= (~RIGHT);
				break;
			case sf::Keyboard::S :
				_currentDirection &= (~DOWN);
				break;
			default:
				update = false;
				break;
		}
		if (update)
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
-- FUNCTION: CallUnitTypeCreationEvent
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--          Jesse Wright: Changed fucntion to take a Unit type so we can have a
--                        more generic function for creating units in the game.
--                        simply checks the unit type and calls the correct
--                        game logic function.
--
-- DESIGNER: Jesse Wright
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
	    case CREEP_ONE:
	    case CREEP_TWO:
	    case CREEP_THREE:
	        _clientGameLogicModule->createCreep(unit_type, GetCurrentLane());
	    break;
	    case PLAYER:
		case PROJECTILE:
		case CREEP:         // these aren't doing anything, but get rid of
		case TOWER:         // warnings
		case CASTLE:
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
-- FUNCTION: SetTowerPlacement
--
-- DATE: 2013/03/20
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jesse Wright
--
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE: void SetTowerPlacement(Point p)
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
