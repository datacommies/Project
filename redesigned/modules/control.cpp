#include "control.h"

/* Constructor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:   Creates a thread and starts running the module */
Control::Control(ClientGameLogic& clientGameLogicModule)
	:clientGameLogicModule_(clientGameLogicModule)
{
	// TODO: create a thread
	loadControlEvents(&clientGameLogicModule);
	//ControlRun();
}
