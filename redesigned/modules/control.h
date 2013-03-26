#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H
/*--------------------------------------------------------------------------------------------------------------------
-- CLASS: Control
--
-- FUNCTIONS: get()
--            Control()
--            void LoadGameLogic()
--            void LoadGraphics()
--            void AddNewCalledButton()
--            void AddNewCalledKey()
--            void RunAllButtons()
--            void RunAllKeys()
--
-- DATE: 2013/03/21
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- NOTES: This class is the central Control Module Singleton. It is called to generate lists of Control Events, check
--        each of those events against lists of valid events, and if a match is found run Wrapper functions. It also contains
--        those wrapper function.
--
--        Control Event Definition - Any time a Key or Button is pressed is a Control Event
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "../resource.h"
#include "client_game_logic.h"
#include "graphics.h"
#include <vector>

#define TERMINATE    10000



class ClientGameLogic;

class Control
{
private:
	// Constructors
	Control();
	
public:
	// Get Method for Singleton Class
	static Control* get();
	
	// Initialization for Game Logic
	void LoadGameLogic(ClientGameLogic* clientGameLogicModule);
	void LoadGraphics(Graphics* graphicsModule);
	
	// Call Functions for reporting Control Events
	void AddNewCalledButton(int id);
	void AddNewCalledKey(sf::Keyboard::Key key);
	
	// Functions for Running Control Events
	void RunAllButtons();
	void RunAllKeys();
	// Get For currentLane variable
	int GetCurrentLane(){return currentLane_;}
	Point GetTowerPlacement(){return towerPlacement_;}
	void SetTowerPlacement(Point p);
private:
	// Static Reference for Singleton Class
	static Control* _Control;
	
	// Collections for storing Control Events
	std::vector<int> _buttonIDs;
	std::vector<sf::Keyboard::Key> _keys;
	
	// Module references
	ClientGameLogic* _clientGameLogicModule;
	Graphics* _graphicsModule;
	
	// Wrapper Functions
	void CallExitGameEvent();
	void CallEnterLobbyEvent();

	void CallMoveEvent(Direction direction);

	void CallAttackEvent(Direction direction);

	void CallUnitTypeCreationEvent(UnitType ttype);
	
	
	int currentLane_;
	Point towerPlacement_;
};

#endif
