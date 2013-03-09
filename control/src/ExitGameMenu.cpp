#include <iostream>
#include "ExitGameMenu.h"

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: ExitGameMenu
--
-- DATE: 2013/03/04
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: bool ExitGameMenu()
--
-- RETURNS: Returns true when the user wants to exit the game, false when the user wants to resume playing.
--
-- NOTES: This function monitors the click coordinates which will then determine if the user
--        clicked on a  button and call the appropriate exit function. Might add "Return to Lobby"
--        function later.
----------------------------------------------------------------------------------------------------------------------*/
bool ExitGameMenu()
{
	
	//set menu buttons up

	while(true)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i clickCoord = sf::Mouse::getPosition();
			if(ExitGame.contains(clickCoord) && ExitGame())
				return true;
			else if(ResumeGame.contains(clickCoord))
				return false;
			//may add "return to lobby" function later on 
		}
	}
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: ExitGame
--
-- DATE: 2013/03/04
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Luke Tao
--
-- PROGRAMMER: Luke Tao
--
-- INTERFACE: bool ExitGame()
--
-- RETURNS: Returns true when the user clicks "Yes" to exit the game, false when the user clicks "No".
--
-- NOTES: This function will get called by ExitGameMenu() in the event that the user wants to exit the game.
--        It will bring up a message box asking the user, "Are you sure you want to exit the game?" with two
--	  buttons, "Yes" and "No".
----------------------------------------------------------------------------------------------------------------------*/
bool ExitGame()
{
	while(true)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i clickCoord = sf::Mouse::getPosition();
			if(Yes_ExitGame.contains(clickCoord)) //if user clicks yes
				return true;
			else if(No_ExitGame.contains(clickCoord)) //if user clicks no
				return false;
		}
	}
}
