/*------------------------------------------------------------------------------
-- FILE:        audio.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: 
--
-- FUNCTIONS:   Client constructor
--              run
--
-- DESCRIPTION: File contains implementation for the Client class.
------------------------------------------------------------------------------*/
#include "audio.h"

Audio::Audio()
{ 

}

/*------------------------------------------------------------------------------
-- FUNCTION:    run
--
-- DATE:        2013/03/11
--
-- DESIGNER:    
-- PROGRAMMER:  
--
-- INTERFACE:   void Client::run()
--
-- RETURNS:     void
--
-- DESCRIPTION: This function will continually attempt to connect to the server.
------------------------------------------------------------------------------*/
int Audio::playMusic(const char* filename)
{
    //if (!buffer_.loadFromFile(filename))
    if (!music_.openFromFile(filename))
        return EXIT_FAILURE;

    //sound_ = sf::Sound(buffer_);
    //sound_.play();
    music_.play();


    return EXIT_SUCCESS;
}

void Audio::stopMusic()
{
    music_.stop();
}

void Audio::pauseMusic()
{
    music_.pause();
}