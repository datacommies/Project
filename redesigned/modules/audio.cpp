/*------------------------------------------------------------------------------
-- FILE:        audio.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Aaron Lee, Luke Tao
--
-- FUNCTIONS:   Audio constructor
--              playMusic
--              stopMusic
--              pauseMusic
--
-- DESCRIPTION: File contains implementation for the Audio class.
------------------------------------------------------------------------------*/
#include "audio.h"

Audio::Audio()
{ 

}

/*------------------------------------------------------------------------------
-- FUNCTION:    playMusic
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Luke Tao
-- PROGRAMMER:  Aaron Lee
--
-- INTERFACE:   void Audio::playMusic()
--
-- RETURNS:     int -- 1 if failed to open file
--
-- DESCRIPTION: load music file then play it
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


/*------------------------------------------------------------------------------
-- FUNCTION:    stopMusic
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Luke Tao
-- PROGRAMMER:  Aaron Lee
--
-- INTERFACE:   void Audio::stopMusic()
--
-- RETURNS:     void
--
-- DESCRIPTION: stop currently playing music file
------------------------------------------------------------------------------*/
void Audio::stopMusic()
{
    music_.stop();
}


/*------------------------------------------------------------------------------
-- FUNCTION:    pauseMusic
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Luke Tao
-- PROGRAMMER:  Aaron Lee
--
-- INTERFACE:   void Audio::pauseMusic()
--
-- RETURNS:     void
--
-- DESCRIPTION: pause currently playing music file
------------------------------------------------------------------------------*/
void Audio::pauseMusic()
{
    music_.pause();
}