/*------------------------------------------------------------------------------
-- FILE:        client.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Dennis Ho, David Czech
--
-- FUNCTIONS:   Client constructor
--              run
--
-- DESCRIPTION: File contains implementation for the Client class.
------------------------------------------------------------------------------*/
#include "client.h"
#include <unistd.h>

Client::Client()
   : clientNetwork_(), clientGameLogic_(clientNetwork_), graphics_(clientGameLogic_), control_(Control::get()) 
{ 
    control_->LoadGameLogic(&clientGameLogic_);
    control_->LoadGraphics(&graphics_);
    run();
}

/*------------------------------------------------------------------------------
-- FUNCTION:    run
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Dennis Ho, David Czech
-- PROGRAMMER:  Dennis Ho, David Czech
--
-- INTERFACE:   void Client::run()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function will continually attempt to connect to the server.
------------------------------------------------------------------------------*/
void Client::run()
{
    while (true) {
        while (clientGameLogic_.getCurrentState() != LOBBY)
            usleep(10);
        clientNetwork_.connectToServer();
        sleep(1);
    }
}
