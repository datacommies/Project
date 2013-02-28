#include <iostream>
#include <SFML/Graphics.hpp>
#include "InputManager.h"

InputManager::InputManager(int currentContext) : current_context(currentContext) {}

int InputManager::getCurrentContext() { return current_context; }

int InputManager::onClickContext(sf::Event event, sf::FloatRect rect1, sf::FloatRect rect2, sf::FloatRect rect3)
{
	int x = event.mouseButton.x;
	int y = event.mouseButton.y;

	std::cout << "x :" << x << " y: " << y << std::endl;
	if(rect1.contains(x, y))
	{
		//call menu function
		std::cout << "Context changed to menu" << std::endl;
		setCurrentContext(MENU_CONTEXT);
		return MENU_CONTEXT;
	}
	else if(rect2.contains(x, y))
	{
		//call builder function
		std::cout << "Context changed to builder" << std::endl;
		setCurrentContext(BUILDER_CONTEXT);
		return BUILDER_CONTEXT;
	}	
	else if(rect3.contains(x, y))
	{
		//call player function
		std::cout << "Context changed to player" << std::endl;
		setCurrentContext(PLAYER_CONTEXT);
		return PLAYER_CONTEXT;
	}
	return getCurrentContext();
}

void InputManager::setCurrentContext(int context) { 
	current_context = context; 
}



