#include "../resource.h"
#include "server.h"

/* Default ctor
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:    */
Server::Server() 
   : serverGameLogic_(), serverNetwork_(serverGameLogic_), ai_(serverGameLogic_)
{
   run();
}

/* Runs the server (basically the main function)
 *
 * PRE:     
 * POST:    
 * RETURNS: 
 * NOTES:    */
void Server::run()
{
}