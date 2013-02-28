#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#define MENU_CONTEXT 10
#define BUILDER_CONTEXT 20
#define PLAYER_CONTEXT 30

#include <SFML/Graphics.hpp>

class InputManager
{
	public:
		explicit InputManager(int currentContext = 10);
		int getCurrentContext();
		int onClickContext(sf::Event event, sf::FloatRect rect1, sf::FloatRect rect2, sf::FloatRect rect3);
		void setCurrentContext(int context);
	private:
		int current_context;

};

#endif
