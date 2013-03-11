#include "client.h"

/* Default ctor
 *
 * PRE:     
 * POST:    All appropriate modules are created and client is started
 * RETURNS: 
 * NOTES:    */
Client::Client()
   : clientNetwork_(), clientGameLogic_(clientNetwork_), graphics_(clientGameLogic_), control_(clientGameLogic_) 
{ 
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
}