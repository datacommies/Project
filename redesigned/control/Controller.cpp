#include "Controller.h"
#include "Control.h"
#include <SFML/Graphics.hpp>

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: Controller
--
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--             Luke Tao
--
-- INTERFACE: Controller(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void))
--            int returnValue - The value that theCheckController() function returns on success
--            Key key - The Key that is being listen to for input
--            Button buttonRect - The Button that is being listen to for input
--            void (*move_fp)(void) - A function pointer to the function that should be called by RunCommand
--
-- RETURNS: N/A
--
-- NOTES: Constructor for Controller Class
----------------------------------------------------------------------------------------------------------------------*/
Controller::Controller(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void *)) 
	:_returnValue(returnValue)
	,_key(key)
	,_buttonRECT(buttonRect)
{

	eventFunction = move_fp;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: LoadGui
--
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: LoadGui()
--
-- RETURNS: void
--
-- NOTES: Loads the contained Button into the Graphics
----------------------------------------------------------------------------------------------------------------------*/
void 
Controller::LoadGui()
{
	gameLogicPointer->UIElements.insert(_buttonRECT);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: UnloadGui
--
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: UnloadGui()
--
-- RETURNS: void
--
-- NOTES: Unloads the contained Button from the Graphics
----------------------------------------------------------------------------------------------------------------------*/
void Controller::UnloadGui()
{
	gameLogicPointer->UIElements.erase(_buttonRECT);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunCommand
--
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: RunCommand()
--
-- RETURNS: N/A
--
-- NOTES: Calls the function pointer that the Controller was initialized with
----------------------------------------------------------------------------------------------------------------------*/
void 
Controller::RunCommand()
{
	//eventFunction(void *);
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: CheckController
--
-- DATE: 2013/03/12
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--             Luke Tao
--
-- INTERFACE: CheckController()
-- 
-- RETURNS: N/A
-- 
-- NOTES: Checks if the Watched button or Key has ben pressed
----------------------------------------------------------------------------------------------------------------------*/
int 
Controller::CheckController()
{
	/*if(_buttonRECT.id != 0)
	{
		if(getCalledButton(_buttonRECT.id))
		{
			return _returnValue;
		}
	}
	
	if(_key != 0)
	{
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key))
		//{
			//return _returnValue;
		//}
	  
	}*/

	return 0;
}

