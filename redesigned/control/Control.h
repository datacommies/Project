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
#include "BuildController.h"
#include "ControlState.h"
#include "ControlManager.h"
#include "ControlEvents.h"

#define LAST_STATE   1
#define MENU_ID      10 
#define LOBBY_ID     20
#define PLAYER_ID    30
#define BUILDER_ID   40
#define EXIT_MENU_ID 50
#define BUILDTOWER_1 300
#define BUILDTOWER_2 301
#define BUILDTOWER_3 302
#define BUILDCREEP_1 350
#define BUILDCREEP_2 351
#define BUILDCREEP_3 352
#define SELECTLOPATH 400
#define SELECTMIDPATH 401
#define SELECTHIPATH 402
#define ID_QUIT 101
#define BUTTON_WIDTH  100
#define BUTTON_HEIGHT 25
#define ROW1 620
#define ROW2 665

#define TERMINATE    10000

#define BUILD_TOWER 1337
#define SPAWN_CREEP 1338

class ControlManager;

void ControlRun(void* vp);

void AddStates(ControlManager &manager);
ControlState MakeMenuState();
ControlState MakeLobbyState();
ControlState MakePlayerState();
ControlState MakeBuilderState();
ControlState MakeExitGameState();

#endif
