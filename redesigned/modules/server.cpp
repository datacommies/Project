/*------------------------------------------------------------------------------
-- FILE:        server.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Dennis Ho, David Czech, Aaron Lee
--
-- FUNCTIONS:   Server constructor
--              run
--
-- DESCRIPTION: File contains implementation for the Server class.
------------------------------------------------------------------------------*/
#include "server.h"
#include <signal.h>
#include "../units/AiController.h"

Server::Server() 
   : serverGameLogic_(), serverNetwork_(serverGameLogic_), ai_(serverGameLogic_)
{
   run();
}

/*------------------------------------------------------------------------------
-- FUNCTION:    run
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Dennis Ho, David Czech
-- PROGRAMMER:  Dennis Ho, David Czech, Aaron Lee
--
-- INTERFACE:   void Client::run()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function starts the game on the server, and sets up all
--				networking via the initSock() and initNetwork() function calls.
------------------------------------------------------------------------------*/
void Server::run()
{
    serverGameLogic_.startGame();
    signal(SIGPIPE, SIG_IGN); // Ignore sigpipe so server doesn't abort when a client disconnects.
    serverNetwork_.initSock();
    serverNetwork_.initNetwork();
}