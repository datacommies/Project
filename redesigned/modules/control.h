#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H

#include "../resource.h"
#include "../control/Control.h"
#include "client_game_logic.h"

class ClientGameLogic;

class Control
{
public:
   // Constructors
   Control(ClientGameLogic& clientGameLogicModule, Graphics& graphics);
private:
   // Module references
   ClientGameLogic& clientGameLogicModule_;
   Graphics& graphicsModule_;
};

#endif
