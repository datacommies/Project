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

   // Functions
   void drawHud();
   void drawLobby();
   void drawUnits();
   void drawMap();
   friend void * init (void *);
};

#endif