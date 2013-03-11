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

#include "Controller.h"
#include "ControlState.h"
#include "ControlManager.h"

int Control();

void AddStates(ControlManager &manager);
ControlState MakeMenuState();
ControlState MakeLobbyState();
ControlState MakePlayerState();
ControlState MakeBuilderState();
ControlState MakeExitGameState();

#endif

