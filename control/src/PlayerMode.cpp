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
			}
		} else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				AttackWithPlayer(DIRECTION_LEFT);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				AttackWithPlayer(DIRECTION_UP);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				AttackWithPlayer(DIRECTION_DOWN);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				AttackWithPlayer(DIRECTION_RIGHT);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LEFT))
			{
				MovePlayer(DIRECTION_LEFT);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::UP))
			{
				MovePlayer(DIRECTION_UP);
			} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::RIGHT))
			{
				MovePlayer(DIRECTION_RIGHT);
			}  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::DOWN))
			{
				MovePlayer(DIRECTION_DOWN);
			}
		}
	}
	
	return 0;
}

/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: MovePlayer
--
-- DATE: 2013/02/25
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int MovePlayer(int direction)
--                int direction - The direction that the player is moving in. See DIRECTION_ definitions.
--
-- RETURNS: Returns 0 on success; otherwise returns negative value.
--
-- NOTES: This function takes a direction and reports to game logic that the character should move in that direction.
----------------------------------------------------------------------------------------------------------------------*/
int MovePlayer(int direction)
{
	switch(direction)
	{
		case DIRECTION_UP:
			// Call Move, pass in direction
		break;
		
		case DIRECTION_RIGHT:
			// Call Move, pass in direction
		break;
		
		case DIRECTION_DOWN:
			// Call Move, pass in direction
		break;
		
		case DIRECTION_LEFT:
			// Call Move, pass in direction
		break;
		
		default:
			return -1
	}
	
	return 0;
}


/*-------------------------------------------------------------------------------------------------------------------- 
-- FUNCTION: AttackWithPlayer
--
-- DATE: 2013/02/25
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- INTERFACE: int AttackWithPlayer(int direction)
--                int direction - The direction that the player is moving in. See DIRECTION_ definitions.
--
-- RETURNS: Returns 0 on success; otherwise returns negative value.
--
-- NOTES: This function takes a direction and reports to game logic that the character should attack in that direction.
----------------------------------------------------------------------------------------------------------------------*/
int AttackWithPlayer(int direction)
{
	switch(direction)
	{
		case DIRECTION_UP:
			// Call attack, pass in direction
		break;
		
		case DIRECTION_RIGHT:
			// Call attack, pass in direction
		break;
		
		case DIRECTION_DOWN:
			// Call attack, pass in direction
		break;
		
		case DIRECTION_LEFT:
			// Call attack, pass in direction
		break;
		
		default:
			return -1
	}
	
	return 0;
}

