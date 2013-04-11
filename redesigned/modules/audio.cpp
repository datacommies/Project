/*------------------------------------------------------------------------------
-- FILE:        audio.cpp
--
-- DATE:        2013/03/11
--
-- MAINTAINERS: Aaron Lee, Luke Tao, Steve Lo
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
-- DESIGNER:    Luke Tao, Steve Lo
-- PROGRAMMER:  Aaron Lee
--
-- INTERFACE:   void Audio::playMusic()
--
-- RETURNS:     int -- 1 if failed to open file
--
-- DESCRIPTION: Begin playing the music file if it's loaded sucessfully
------------------------------------------------------------------------------*/
int Audio::playMusic(const char* filename)
{
    if (!music_.openFromFile(filename)) //if problem opening the file
        return EXIT_FAILURE;    //return an error

	music_.setVolume(30);   //set the volume
    music_.play();          //begin playback the music


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
-- DESCRIPTION: load and play the sound effect file
------------------------------------------------------------------------------*/
int Audio::playSoundEffect(const char* filename)
{
    sf::SoundBuffer Buffer;     //buffer holding the filename
    if (!Buffer.loadFromFile(filename)) //try opening the audio file
        return EXIT_FAILURE;
    
    sf::Sound Sound;
    Sound.setBuffer(Buffer);
    Sound.play();
    
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
-- DESIGNER:    Luke Tao, Steve Lo
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
    music_.stop();  //stop the playback
}


/*------------------------------------------------------------------------------
-- FUNCTION:    pauseMusic
--
-- DATE:        2013/03/11
--
-- DESIGNER:    Luke Tao, Steve Lo
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
    music_.pause(); //pause the playback
}
