#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "button.h"

// Defines --------------------------------------------------------------------

#define MAPWIDTH  500 //TODO: change placeholder value
#define MAPHEIGHT 500 //TODO: change placeholder value

// Enums ----------------------------------------------------------------------

enum Direction
{
   UP,
   LEFT,
   RIGHT,
   DOWN
};

enum UnitType
{
   PLAYER,
   CREEP,
   TOWER,
   CASTLE
};


enum GameState
{
   MAIN_MENU,
   LOBBY,
   IN_GAME
};

// Structs --------------------------------------------------------------------

struct Point
{
   int x;
   int y;
};

struct CLIENT_UNIT // This struct applies only to the client side - server side units are stored differently
{
   int id;
   Point position;
   int health;
   int team;
   UnitType type;
};

// Typedefs -------------------------------------------------------------------

typedef std::vector<Point> PATH;

#endif
