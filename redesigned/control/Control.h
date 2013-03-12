#ifndef CONTROL_H
#define CONTROL_H
/*--------------------------------------------------------------------------------------------------------------------
-- PROGRAM: ControlState
--
-- CLASSES: Controller
--          ControlState
--          ControlManager
--
-- FUNCTIONS: int Control()
--            void AddStates()
--            ControlState MakeMenuState()
--            ControlState MakeLobbyState()
--            ControlState MakePlayerState()
--            ControlState MakeBuilderState()
--            ControlState MakeExitGameState()
--
--
-- DATE: 2013/03/11
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: John Payment
--
-- PROGRAMMER: John Payment
--
-- NOTES: This program manages Control (user input) for the Game Program
-- 
----------------------------------------------------------------------------------------------------------------------*/

#include "../resource.h"
#include "Controller.h"
#include "ControlState.h"
#include "ControlManager.h"

#define MENU_ID      10 
#define LOBBY_ID     20
#define PLAYER_ID    30
#define BUILDER_ID   40
#define EXIT_MENU_ID 50

#define BUILD_TOWER 1337
#define SPAWN_CREEP 1338

int ControlRun();

void AddStates(ControlManager &manager);
ControlState MakeMenuState();
ControlState MakeLobbyState();
ControlState MakePlayerState();
ControlState MakeBuilderState();
ControlState MakeExitGameState();

#endif

