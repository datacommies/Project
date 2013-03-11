#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../resource.h"
#include "client_game_logic.h"

class Graphics
{
public:
   // Constructors
   Graphics(ClientGameLogic& clientGameLogic);
private:
   // Module references
   ClientGameLogic& clientGameLogic_;

   // Graphics internals
   sf::Font font;

   // Functions
   void drawHud(sf::RenderWindow& window);
   void drawLobby(sf::RenderWindow& window);
   void drawUnits(sf::RenderWindow& window);
   void drawMap(sf::RenderWindow& window);
   friend void * init (void *);
};

#endif