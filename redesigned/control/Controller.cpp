#include "Controller.h"
#include "Control.h"
#include <SFML/Graphics.hpp>

void Controller::LoadGui()
{
	// call Graphics function.
}

void Controller::UnloadGui()
{
	// call graphics function.
}

void Controller::RunCommand()
{
	// stuff happens.
}

int Controller::CheckController(int buttonID, sf::Window *window)
{
	Point p;
	switch(buttonID)
	{
		case BUILD_TOWER:
			// monitor for field click
			p = Controller::monitorMouseClick(window);
		break;
		case SPAWN_CREEP:
			// call spawn creep function		
		break;
	}
	// next next next
}
Point Controller::monitorMouseClick(sf::Window *window)
{
	sf::Event event;
	Point temp;
	while(window->pollEvent(event))
	{
		if(event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window));
			temp.x = mouse.x;
			temp.y = mouse.y;
			break;
		}
	}
	return temp;
}
