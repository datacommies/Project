#ifndef CONTROL_EVENTS_H
#define CONTROL_EVENTS_H

#include "../resources.h"
#include "../modules/control.h"

void CallExitGameEvent();

void CallEnterLobbyEvent();

void CallMoveLeftEvent();
void CallMoveRightEvent();
void CallMoveUpEvent();
void CallMoveDownEvent();

void CallAttackLeftEvent();
void CallAttackRightEvent();
void CallAttackUpEvent();
void CallAttackDownEvent();

void CallBuildTowerEvent(int x, int y);
void CallBuildCreepEvent();

void AddNewCalledButton(int id);
bool getCalledButton(int id);

#endif
