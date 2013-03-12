#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../resource.h"

#define BUILD_TOWER 1337
#define SPAWN_CREEP 1338
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

