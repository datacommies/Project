#ifndef CONTROLLER_H
#define CONTROLLER_H
/*--------------------------------------------------------------------------------------------------------------------
-- CLASS: Controller
--
-- FUNCTIONS: Controller()
--
	
	
	int CheckController()
--
	
	
	void LoadGui()
--
	
	
	void UnloadGui()
--
	
	
	void RunCommand()
--
	
	 
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: Luke Tao
--
	
	
	 John Payment
--
-- NOTES: This class is used to modularate each control segment. THis represents 1 action that can be taken by a button
--
	
	press or key stroke.
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "../resource.h"
#include <vector>
#include <SFML/Window.hpp>

class Controller
{
public:

	

	Controller(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void));

	int CheckController();

	void LoadGui();
	void UnloadGui();
	
private:
	
	void RunCommand();
	
	int _returnValue;
	int _key;
	Button _buttonRECT;
	
	void (*eventFunction)(void);
	
};

#endif

