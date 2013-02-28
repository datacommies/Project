#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputManager.h"


InputManager::InputManager(int currentContext) : current_context(currentContext) {}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: getCurrentContext
--
-- DATE: 2013/02/28
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: int InputManager::getCurrentContext()
--
-- RETURNS: The current context value.
--
-- NOTES: This function returns the current context value that the player is on.
----------------------------------------------------------------------------------------------------------------------*/
int InputManager::getCurrentContext() { return current_context; }


/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: onClickContext
--
-- DATE: 2013/02/28
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: int InputManager::onClickContext(sf::Event mouseEvent, sf::FloatRect menuContext, 
--						sf::FloatRect buildContext, sf::FloatRect playContext)
--					       
--					       sf::Event mouseEvent - the mouse event
--					       sf::FloatRect menuContext - the menu context
--					       sf::FloatRect buildContext - the builder context
--					       sf::Float Rect playContext - the player context
--
-- RETURNS: Context defined values.
--
-- NOTES: This function handles the events of the mouse clicks. It will print out the coordinates of where the
--	  mouse click happens and determines if it is within one of the context buttons. If the mouse click is within
--        the buttons, it will set the current context value and return that value.
----------------------------------------------------------------------------------------------------------------------*/
int InputManager::onClickContext(sf::Event mouseEvent, sf::FloatRect menuContext, sf::FloatRect buildContext, sf::FloatRect playContext)
{
	int x = mouseEvent.mouseButton.x;
	int y = mouseEvent.mouseButton.y;

	std::cout << "x :" << x << " y: " << y << std::endl;
	if(menuContext.contains(x, y))
	{
		//call menu function
		std::cout << "Context changed to menu" << std::endl;
		setCurrentContext(MENU_CONTEXT);
		return MENU_CONTEXT;
	}
	else if(buildContext.contains(x, y))
	{
		//call builder function
		std::cout << "Context changed to builder" << std::endl;
		setCurrentContext(BUILDER_CONTEXT);
		return BUILDER_CONTEXT;
	}	
	else if(playContext.contains(x, y))
	{
		//call player function
		std::cout << "Context changed to player" << std::endl;
		setCurrentContext(PLAYER_CONTEXT);
		return PLAYER_CONTEXT;
	}
	return getCurrentContext();
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: setCurrentContext
--
-- DATE: 2013/02/28
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: int InputManager::setCurrentContext(int context)
--						  int context - the new context value
--
-- RETURNS: void.
--
-- NOTES: This function sets the new context value. ----------------------------------------------------------------------------------------------------------------------*/
void InputManager::setCurrentContext(int context) { 
	current_context = context; 
}



