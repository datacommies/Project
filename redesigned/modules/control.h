#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H

#include "../resource.h"
#include "client_game_logic.h"

class ClientGameLogic;

class Control
{
public:
   // Constructors
   Control(ClientGameLogic& clientGameLogicModule);
private:
   // Module references
   ClientGameLogic& clientGameLogicModule_;
};

#endif