#include "Control.h"

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MenuInputMonitor
--
-- DATE: 2013/02/25
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int MenuInputMonitor()
--
-- RETURNS: Returns a predefined integer that tells the Manager which Monitor to next open up.
--
-- NOTES: This function monitors key and button input and calls the appropriate functions based on that input.
----------------------------------------------------------------------------------------------------------------------*/
int MenuInputMonitor()
{
	int playerMode = PLAYER_MODE;
	bool isTeamOne = true;
	
	while(true)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i position = sf::Mouse::getPosition();
			if(ExitMenuButton.contains(position))
			{
				if(ExitGameMenu())
				{
					return -10;
				}
			} else if(PlayerModeButton.contains(position))
			{
				playerMode = PLAYER_MODE;
			} else if(BUilderModeButton.contains(position))
			{
				playerMode = BUILDER_MODE;
			} else if(Team1Button.contains(position))
			{
				isTeamOne = true;
			} else if(Team2Button.contains(position))
			{
				isTeamOne = false;
			} else if(PlayButton.contains(position))
			{
				return playerMode;
			} 
		}
	}
	
	return 0;
}


