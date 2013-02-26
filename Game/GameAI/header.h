#ifndef HEADER_H
#define HEADER_H


#include "Attacker.h"
#include "Creep.h"
#include "Tower.h"
#include "Game.h"
#include "Square.h"
#include "Attackable.h"
#include "Point.h"


#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>


/*PROTOTYPES */

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI GameRoutine( LPVOID );
DWORD WINAPI AI (LPVOID lp );




/*Timer for Update*/
#define TIME 20

/*  DEFINES */

#define SQUARE_SIZE 20
#define GAME_ROW 26
#define GAME_COL 41


/*Windows Specific */





#endif