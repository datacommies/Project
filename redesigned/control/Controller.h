#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../resource.h"

class Controller
{

private:
	int CheckController(int buttonID, sf::Window *window);
	void RunCommand();
	void LoadGui();
	void UnloadGui();
	Point monitorMouseClick(sf::Window *window);
};

#endif

