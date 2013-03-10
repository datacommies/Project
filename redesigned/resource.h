#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>

#define MAPWIDTH   500 //TODO: change placeholder value
#define MAPHEIGHT   500 //TODO: change placeholder value

struct Point
{
   int x;
   int y;
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

typedef std::vector<Point> PATH;

#endif