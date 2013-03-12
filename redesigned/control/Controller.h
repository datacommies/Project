#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../resource.h"
#include <vector>
#include <SFML/Window.hpp>

class Controller
{

public:
    
    Controller(int returnValue, sf::Keyboard::Key key, Button buttonRect, void (*move_fp)(void)); 
    int CheckController();
    void LoadGui();
	void UnloadGui();
	
private:
	
	void RunCommand();
	int _returnValue;
	sf::Keyboard::Key _key;
	Button _buttonRECT;
	
	
};

#endif

