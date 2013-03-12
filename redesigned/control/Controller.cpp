#include "Controller.h"
#include "Control.h"
#include <SFML/Graphics.hpp>


Controller::Controller(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void)) 
                        : _returnValue(returnValue), _key(key), _buttonRECT(buttonRect)
{
    
}
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

int Controller::CheckController()
{
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && _buttonRECT != NULL)
    {
        return _returnValue;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key) && _key != NULL)
    {
        return _returnValue;
    }
      
    
	return 0;
}

