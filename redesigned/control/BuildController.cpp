#include "BuildController.h"
#include "ControlEvents.h"
#include "../modules/graphics.h"

BuildController::BuildController(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void *))
	:Controller(returnValue, key, buttonRect, move_fp)
{
	
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: RunCommand
--
-- DATE: 2013/03/14
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: Jesse Wright
--
-- INTERFACE: RunCommand()
--
-- RETURNS: N/A
--
-- NOTES: Polymorphic function used for giving coordinates to the event
----------------------------------------------------------------------------------------------------------------------*/
void 
BuildController::RunCommand()
{
	Graphics* graphics;
	int position[2];
	position[0] = 0; // X coordinate
	position[1] = 1; // Y coordinate
	graphics = getGraphicsObj(); // get the graphics object so we can get the window
	
	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition( *(graphics->window) );
			position[0] = localPosition.x;
			position[1] = localPosition.y;
			
			eventFunction((void*)position);
			break;
		}
	}
}
