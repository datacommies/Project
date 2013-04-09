#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "button.h"
#include "units/Point.h"
// Defines --------------------------------------------------------------------

#define MAPWIDTH  500 //TODO: change placeholder value
#define MAPHEIGHT 500 //TODO: change placeholder value

// Button IDs
#define ID_JOIN 100
#define ID_QUIT 101
#define ID_TEST 999
#define BUILDTOWER_1 300
#define BUILDTOWER_2 301
#define BUILDTOWER_3 302
#define BUILDCREEP_1 350
#define BUILDCREEP_2 351
#define BUILDCREEP_3 352
#define SELECTLOPATH 400
#define SELECTMIDPATH 401
#define SELECTHIPATH 402

// Enums ----------------------------------------------------------------------
// Bit positional values
enum Direction
{
   STATIONARY = 0,
   UP    = 1,
   LEFT  = 2,
   RIGHT = 4,
   DOWN  = 8
};

enum UnitType
{
   PLAYER,
   CREEP,
   CREEP_ONE,
   CREEP_TWO,
   CREEP_THREE,
   TOWER,
   TOWER_ONE,
   TOWER_TWO,
   TOWER_THREE,
   CASTLE,
   PROJECTILE
};

enum GameState
{
   MAIN_MENU,
   LOBBY,
   IN_GAME,
   WON_GAME,
   LOST_GAME,
   GAME_END
};

enum PathId
{
   HIGHPATH,
   MIDPATH,
   LOWPATH
};

// Structs --------------------------------------------------------------------

struct CLIENT_UNIT // This struct applies only to the client side - server side units are stored differently
{
   int id;
   Point position;

   Point past_position; // Past position.
   Point inter_position;// interpolated position - for smooth client-side movement.
   float inter_value;   // interpolated value between 

   int health;
   int team;
   UnitType type;
};

// Typedefs -------------------------------------------------------------------

typedef std::vector<Point> PATH;

#endif
