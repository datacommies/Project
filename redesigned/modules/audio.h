#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>

class Audio
{
public:
   // Constructors
   Audio();

   // Functions
   int playMusic(const char*);
   int playSoundEffect( const char *);
   void stopMusic();
   void pauseMusic();

private:
	sf::SoundBuffer buffer_;
	sf::Music music_;
	sf::Sound sound_;
};

#endif