#ifndef CONTROL_EVENTS_H
#define CONTROL_EVENTS_H

#include "../resource.h"
#include "../modules/client_game_logic.h"

void loadControlEvents(ClientGameLogic* gameLogic);

void CallExitGameEvent(void* value);

void CallEnterLobbyEvent(void* value);

void CallMoveLeftEvent(void* value);
void CallMoveRightEvent(void* value);
void CallMoveUpEvent(void* value);
void CallMoveDownEvent(void* value);

void CallAttackLeftEvent(void* value);
void CallAttackRightEvent(void* value);
void CallAttackUpEvent(void* value);
void CallAttackDownEvent(void* value);

void CallBuildTowerEvent(void* value);
void CallBuildCreepEvent(void* value);

void AddNewCalledButton(int id);
bool getCalledButton(int id);

ClientGameLogic* _gameLogicPointer;

#endif
