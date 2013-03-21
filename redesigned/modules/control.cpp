#include "control.h"
#include "pthread.h"
#include <X11/Xlib.h>
#include <SFML/System.hpp>
/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
Control::Control(ClientGameLogic& clientGameLogicModule, Graphics& graphics)
	:clientGameLogicModule_(clientGameLogicModule), graphicsModule_(graphics)
{
	// TODO: create a thread
	//loadControlEvents(&clientGameLogicModule);
	//ControlRun();
	//XInitThreads();
	pthread_t thread;
	int result;
	
	loadControlEvents(&clientGameLogicModule, &graphicsModule_);
	//sf::Thread Thread(&ControlRun);
	//Thread.launch();
	
	result = pthread_create(&thread, NULL, ControlRun, NULL);
	//if(result)
	//{
	    
	    // error
	//}
	
	
}
