#include "server.h"

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
    serverNetwork_.initSock();
    serverNetwork_.initNetwork();
    while (true) {
        sleep(1);
    }

}