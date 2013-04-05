#include "server.h"
#include <signal.h>
#include "../units/AiController.h"
/* Default ctor
 *
 * PRE:     
 * POST:    All appropriate modules are created and server is started
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
 * NOTES:    
 */
void Server::run()
{
    serverGameLogic_.startGame();
    signal(SIGPIPE, SIG_IGN); // Ignore sigpipe so server doesn't abort when a client disconnects.
    serverNetwork_.initSock();
    serverNetwork_.initNetwork();
}