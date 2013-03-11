#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>

// Defines --------------------------------------------------------------------

#define MAPWIDTH  500 //TODO: change placeholder value
#define MAPHEIGHT 500 //TODO: change placeholder value

// Structs --------------------------------------------------------------------

struct Point
{
   int x;
   int y;
};

struct CLIENT_UNIT // This struct applies only to the client side - server side units are stored differently
{
   int id;
   int position;
   int health;
   int team;
   int type;
};

// Enums ----------------------------------------------------------------------

enum Role
{
   CLIENT,
   SERVER
};

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
   LOBBY,
   IN_GAME
};

// Typedefs -------------------------------------------------------------------

typedef std::vector<Point> PATH;

#endif