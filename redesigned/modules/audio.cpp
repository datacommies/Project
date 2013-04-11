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
#include <iostream>
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
    if (!music_.openFromFile(filename))
        return EXIT_FAILURE;

	music_.setVolume(20);
    //music_.play();


    return EXIT_SUCCESS;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    playSoundEffect
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Luke Tao, Steve Lo
-- PROGRAMMER:  Aaron Lee
--
-- INTERFACE:   void Audio::playSoundEffect()
--
-- RETURNS:     int -- 1 if failed to open file
--
-- DESCRIPTION: load  short sound file then play it
------------------------------------------------------------------------------*/
int Audio::playSoundEffect(const char* filename)
{
    sf::SoundBuffer Buffer;
    if (!Buffer.loadFromFile(filename))
        return EXIT_FAILURE;
    
    sf::Sound Sound;
    Sound.setBuffer(Buffer);
    Sound.play();
    
    /*sound_ = sf::Sound(buffer_);
    sound_.play();
    std::cout << "play sound effect" << std::endl;*/
    while(Sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::seconds(0.1f));
    }
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
