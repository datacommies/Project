#include "client.h"
#include <unistd.h>

/* Default ctor
 *
 * PRE:     
 * POST:    All appropriate modules are created and client is started
 * RETURNS: 
 * NOTES:    */
Client::Client()
   : clientNetwork_(), clientGameLogic_(clientNetwork_), graphics_(clientGameLogic_), control_(Control::get()) 
{ 
   control_->LoadGameLogic(&clientGameLogic_);
   control_->LoadGraphics(&graphics_);
   run();
}

/* Runs the client (basically the main function)
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:    */
void Client::run()
{
	while (clientGameLogic_.getCurrentState() != LOBBY) {
		sleep(1);
	}

	clientNetwork_.connectToServer();
}
